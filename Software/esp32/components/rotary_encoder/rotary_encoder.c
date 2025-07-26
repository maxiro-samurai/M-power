/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "rotary_encoder.h"
 
static const char *TAG = "example";
QueueHandle_t encoder_queue = NULL;
QueueHandle_t buton_queue = NULL;
pcnt_unit_handle_t pcnt_unit = NULL;

static rotary_encoder_item_t rotatry_encoder = {
    .key_state = IDLE,
    .last_encoder_value = 0,
    .encoder_value = 0,
    .diff = 0,
  
};


static bool example_pcnt_on_reach(pcnt_unit_handle_t unit, const pcnt_watch_event_data_t *edata, void *user_ctx)
 {
     BaseType_t high_task_wakeup;
     QueueHandle_t queue = (QueueHandle_t)user_ctx;
     // send event data to queue, from this interrupt callback
     // ESP_LOGI(TAG, "Watch point event, count: %d", edata->watch_point_value);
     xQueueSendFromISR(queue, &(edata->watch_point_value), &high_task_wakeup);
     pcnt_unit_clear_count(pcnt_unit); //达到计数最大/小值清零
     return (high_task_wakeup == pdTRUE);
 }
 
 // 按键中断处理（可选）
 static void IRAM_ATTR Key_isr(void* arg) {
     BaseType_t high_task_wakeup;

    // 发送按键事件到队列
    int8_t btn_event = 1;
    xQueueSendFromISR(buton_queue, &btn_event, &high_task_wakeup);
    return (high_task_wakeup == pdTRUE);
}



static void pcnt_init(void)
{
    ESP_LOGI(TAG, "install pcnt unit");
     pcnt_unit_config_t unit_config = {
         .high_limit = EXAMPLE_PCNT_HIGH_LIMIT,
         .low_limit = EXAMPLE_PCNT_LOW_LIMIT,
     };
     
     ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &pcnt_unit)); //新建pcnt单元
 
     ESP_LOGI(TAG, "set glitch filter");
     pcnt_glitch_filter_config_t filter_config = {
         .max_glitch_ns = 10000,
     };
     ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(pcnt_unit, &filter_config)); //滤波器配置
 
     ESP_LOGI(TAG, "install pcnt channels");
     pcnt_chan_config_t chan_a_config = {
         .edge_gpio_num = EXAMPLE_EC11_GPIO_A,
         .level_gpio_num = EXAMPLE_EC11_GPIO_B,
     };
     pcnt_channel_handle_t pcnt_chan_a = NULL;
     ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &chan_a_config, &pcnt_chan_a));//A通道配置
    //  pcnt_chan_config_t chan_b_config = {
    //      .edge_gpio_num = EXAMPLE_EC11_GPIO_B,
    //      .level_gpio_num = EXAMPLE_EC11_GPIO_A,
    //  };
    //  pcnt_channel_handle_t pcnt_chan_b = NULL;
    //  ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &chan_b_config, &pcnt_chan_b));//B通道配置
 
     ESP_LOGI(TAG, "set edge and level actions for pcnt channels");
     ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_a, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE));
     ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_a, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));
    //  ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_b, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_DECREASE));
    //  ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_b, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));
 
     ESP_LOGI(TAG, "add watch points and register callbacks");
     int watch_points[] = {EXAMPLE_PCNT_LOW_LIMIT, EXAMPLE_PCNT_HIGH_LIMIT};
     for (size_t i = 0; i < sizeof(watch_points) / sizeof(watch_points[0]); i++) {
         ESP_ERROR_CHECK(pcnt_unit_add_watch_point(pcnt_unit, watch_points[i]));
     }
     pcnt_event_callbacks_t cbs = {
         .on_reach = example_pcnt_on_reach,
     };


     encoder_queue = xQueueCreate(10, sizeof(int16_t));
    

     ESP_ERROR_CHECK(pcnt_unit_register_event_callbacks(pcnt_unit, &cbs, encoder_queue));
 
     ESP_LOGI(TAG, "enable pcnt unit");
     ESP_ERROR_CHECK(pcnt_unit_enable(pcnt_unit));
     ESP_LOGI(TAG, "clear pcnt unit");
     ESP_ERROR_CHECK(pcnt_unit_clear_count(pcnt_unit));
     ESP_LOGI(TAG, "start pcnt unit");
     ESP_ERROR_CHECK(pcnt_unit_start(pcnt_unit));
}

static void Key_init(void)
{
    ESP_LOGI(TAG, " Init GPIO  ");
    gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL <<EXAMPLE_KEY_GPIO| 1ULL <<BTN_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_ANYEDGE
    };
    ESP_ERROR_CHECK(gpio_config(&io_conf));
    
    ESP_LOGI(TAG, "install GPIO interrupt");
    buton_queue = xQueueCreate(10, sizeof(int8_t));
    ESP_ERROR_CHECK(gpio_install_isr_service(0));
    ESP_ERROR_CHECK(gpio_isr_handler_add(BTN_GPIO, Key_isr, (void*)EXAMPLE_KEY_GPIO));
    

}

void rotary_encoder_init(void)
{
    pcnt_init();
    Key_init();
}

/*

@ 编码器状态扫描

*/

int16_t encoder_state_detection(void) {

    pcnt_unit_get_count(pcnt_unit,&rotatry_encoder.encoder_value); //读取编码器值
    


    if (rotatry_encoder.encoder_value != rotatry_encoder.last_encoder_value) {

        rotatry_encoder.diff = rotatry_encoder.encoder_value - rotatry_encoder.last_encoder_value; //计算差值

        ESP_LOGI(TAG, " Diff: %d",  rotatry_encoder.diff);
        rotatry_encoder.last_encoder_value = rotatry_encoder.encoder_value; 
        
    } 

    else {
        rotatry_encoder.diff = 0; //如果没有变化，差值为0
    }

    
    return rotatry_encoder.diff ; //如果差值小于4，返回0
    
   
}

void encoder_key_detection(rotary_encoder_item_t *encoder){

}

void encoder_task(void *arg) {
    
    while (1) {
        
       
        
        encoder_state_detection();
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

 