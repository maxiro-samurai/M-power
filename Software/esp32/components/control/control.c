#include "control.h"


bool output_enable = true; //输出使能状态
static uint16_t out_time ;
gptimer_handle_t gptimer = NULL;  
QueueHandle_t queue = NULL;

/**
 * * @brief 定时器中断回调函数
 * * * @param timer 定时器句柄
 * * * @param edata 定时器事件数据
 * * * @param user_data 用户数据(一般用作传递队列句柄)
 * * * @return true: 需要在ISR结束时切换上下文，false: 不需要
 */
static bool IRAM_ATTR timer_on_alarm_cb(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_data)

{
    BaseType_t high_task_awoken = pdFALSE;
    QueueHandle_t queue = (QueueHandle_t)user_data;
    bool on_reach = true; // 100MS计时器。

    xQueueSendFromISR(queue, &on_reach, &high_task_awoken);
    // return whether we need to yield at the end of ISR
    return (high_task_awoken == pdTRUE);
}


//定时器初始化 用于计时任务（画图、输出计时）
void timer_init(void)
{
    queue = xQueueCreate(5, sizeof(void*)); // 创建队列，用于接收定时器事件
    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1000000, // 1MHz, 1 tick=1us
    };

    ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &gptimer));

    gptimer_event_callbacks_t cbs = {
        .on_alarm = timer_on_alarm_cb,
    };

    ESP_ERROR_CHECK(gptimer_register_event_callbacks(gptimer, &cbs, queue));

    gptimer_alarm_config_t alarm_config = {
        .alarm_count =100000, // period = 1ms
        .reload_count = 0,
        .flags.auto_reload_on_alarm = true,
    };

    ESP_ERROR_CHECK(gptimer_set_alarm_action(gptimer, &alarm_config));
    ESP_ERROR_CHECK(gptimer_enable(gptimer));
    ESP_ERROR_CHECK(gptimer_start(gptimer));


}

void output_ramp(uint16_t set_voltage)  //输出缓慢变化
{

    uint16_t dac_value_u ,dac_value_i;
    static uint8_t percent_u = 100,percent_i = 100;

    static uint16_t u_now ,u_tar,i_now,i_tar;
    static short u_gap,i_gap;

    if (output_enable){

        if (set_voltage!= u_tar){  // 电压缓变至设定电压
            u_tar = set_voltage;
            u_gap = u_tar - u_now;
            percent_u = 100;

        }

        if (percent_u){
            percent_u -=1;
            u_now  = u_tar - (u_gap * percent_u / 100);
        }
        else {
            u_now = u_tar;
        }
        


        //////////////////
         if (set_current!= i_tar){  // 电压缓变至设定电压
            i_tar = set_current;
            i_gap = i_tar - i_now;
            percent_i = 100;

        }

        if (percent_i){
            percent_i -=1;
            i_now  = i_tar - (u_gap * percent_i / 100);
        }
        else {
            i_now = i_tar;
        }

        
        printf("Current Voltage: %d\n", u_now);
        dac_value_u = 64452-13.504*u_now;
        dac_value_i = i_now *50;
        dac8562_write_command(DAC_WRITE_REG_A, dac_value_u);//设置输出电压
        // dac8562_write_command(DAC_WRITE_REG_B, dac_value_i);//设置输出电流

     }
     else{

        percent_u  =percent_i = 100; 
        u_now  = u_gap = u_tar =i_now = i_gap= i_tar= 0;
     }
}

void bluetooth_switch_handler(lv_event_t *e){
    lv_obj_t *sw = lv_event_get_target(e);
    bool state = lv_obj_has_state(sw, LV_STATE_CHECKED);


    if(state){
       
        // ble_init();
        // ble_start();
        bluethooth = true;
        lv_label_set_text(ui_Label16, LV_SYMBOL_BLUETOOTH);
        printf("蓝牙已成功开启\n");

    }
    else {

        // ble_close();
        bluethooth = false;
        lv_label_set_text(ui_Label16, "");
        printf("蓝牙已成功关闭\n");
    }


}


void button_scan(void ){

if (!gpio_get_level(BTN_GPIO)) {
            // 按键被按下，处理事件
            vTaskDelay(pdMS_TO_TICKS(40));
             // 再次检测确认按键状态
            if (!gpio_get_level(BTN_GPIO)) {
                // 确认按键被按下，处理事件
                printf("Button pressed!\n");
                output_enable = !output_enable; // 切换输出使能状态
                // 等待按键释放（防止长按重复触发）
                while (!gpio_get_level(BTN_GPIO)) {
                    vTaskDelay(pdMS_TO_TICKS(10));
                }
            }
            // output_enable = !output_enable; // 切换输出使能状态
            // vTaskDelay(pdMS_TO_TICKS(200));
        }

}
void slider_set_value_handler(lv_event_t *e){
    
    lv_obj_t * slider = lv_event_get_target(e);
    uint8_t code =  lv_event_get_user_data(e);
    if (code)
    {
        sound_duty = lv_slider_get_value(slider);

        if(sound_duty  == 0){
        
            lv_label_set_text(ui_Labelsound,LV_SYMBOL_MUTE);

        }
        else if (sound_duty  > 30)
         lv_label_set_text(ui_Labelsound,LV_SYMBOL_VOLUME_MID);
        else if (sound_duty  > 60)
        lv_label_set_text(ui_Labelsound,LV_SYMBOL_VOLUME_MAX);
        // buzzer_set_duty(sound_duty);
    }
    
    

}


// void longpress_exit_handler(lv_event_t *e){
//    lv_event_code_t code =  lv_event_get_code(e);

//     if (code == LV_EVENT_LONG_PRESSED)
//     {
//          beep_test(&Beep3);
//     }
    
// }
void control_output_task(void *arg)
{
    bool on_reach;
    timer_init();


    lv_obj_add_event_cb(ui_Switch1, bluetooth_switch_handler, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_add_event_cb(ui_Slider1,slider_set_value_handler,LV_EVENT_VALUE_CHANGED,1);
    lv_obj_add_event_cb(ui_Slider2,slider_set_value_handler,LV_EVENT_VALUE_CHANGED,0);

    lv_slider_set_value(ui_Slider1,sound_duty,LV_ANIM_OFF);

    // lv_obj_add_event_cb(ui_Spinbox4,longpress_exit_handler,LV_EVENT_LONG_PRESSED,NULL);

    while (1)
    {   
         button_scan();

        //如果输出使能能
        if(output_enable){
            gpio_set_level(LM5175_EN_GPIO, 1); //开启LM5175 
            // gpio_set_level(RED_LED_PIN, 0); // 关闭红色LED
            // gpio_set_level(GREEN_LED_PIN, 1);
            output_ramp(set_voltage);
        }

        else {

            //
            // gpio_set_level(RED_LED_PIN, 1); // 关闭红色LED
            // gpio_set_level(GREEN_LED_PIN, 0);
            gpio_set_level(LM5175_EN_GPIO, 0); //关闭LM5175 
            
        }

        
          
        if (xQueueReceive(queue, &on_reach, portMAX_DELAY) == pdTRUE) {
            // 处理定时器事件
            // ESP_LOGI("Control", "Timer event received");

            update_power_chart(ADC.output_vol[0],ADC.output_current[0]);

            out_time = output_enable ? out_time + 1 : 0;
            // 可以在这里添加其他处理逻辑

             lv_label_set_text_fmt(ui_Label3,"%02d:%02d", out_time/600,(out_time/10)%60);
             out_value_refresh();

             if(!paused)
             update_power_chart(ADC.output_vol[0],ADC.output_current[0]);
        }

        vTaskDelay(pdMS_TO_TICKS(50)); // 延时100ms
    }
    
}