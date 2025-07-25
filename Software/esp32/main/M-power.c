#include "M-power.h"
#include <math.h>

#define LM5175_EN_GPIO 0 // GPIO number for the key input

static const char *TAG = "test";

static esp_timer_handle_t lvgl_tick_timer = NULL;
 
// 定时回调函数，每 1ms 触发
static void lv_tick_task(void *arg) {
    lv_tick_inc(1);
}
 
// 初始化 LVGL Tick 定时器
void lvgl_tick_timer_init(void) {
    const esp_timer_create_args_t timer_args = {
        .callback = &lv_tick_task,
        .arg = NULL,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "lv_tick_timer"
    };
 
    esp_timer_create(&timer_args, &lvgl_tick_timer);
    esp_timer_start_periodic(lvgl_tick_timer, 1000); // 1ms 触发

  }

void lvgl_task(void *arg) {

    ui_init();
    while (1) {   
        out_value_refresh();
        // LVGL 任务处理
        lv_task_handler();
        vTaskDelay(pdMS_TO_TICKS(20)); // 每 5ms 调用一次
    }
}

void app_main(void) {

  lvgl_tick_timer_init();
  lv_init();              /* 初始化LVGL图形库 */
  lv_port_disp_init();    /* lvgl显示接口初始化,放在lv_init()的后面 */
  lv_port_indev_init();   /* lvgl输入接口初始化,放在lv_init()的后面 */
  dac8562_init();
  dac8562_set_voltage(0,2.05);
  dac8562_set_voltage(1,0.3);
  // Initialize components here
  // For example, you might want to initialize Wi-Fi, BLE, or other peripherals
  ESP_LOGI("M-power", "Application main started");

  pwm_init(); //电荷泵初始化
  pwm_start(LEDC_CHANNEL_A);
  pwm_start(LEDC_CHANNEL_B); // 启动A相PWM输出

  gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL <<LM5175_EN_GPIO,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    ESP_ERROR_CHECK(gpio_config(&io_conf));

  io_conf.pin_bit_mask = 1ULL << DAC_LDAC_GPIO;
  io_conf.mode = GPIO_MODE_OUTPUT;
  io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
  ESP_ERROR_CHECK(gpio_config(&io_conf));



  gpio_set_level(LM5175_EN_GPIO, 0); // 启动LM5175

  
  
  vTaskDelay(pdMS_TO_TICKS(100));
  gpio_set_level(LM5175_EN_GPIO, 1); // 启动LM5175
//   beep_test(&testSound);
//   st7789_init();
  

  BaseType_t xReturned;
  xReturned = xTaskCreate(lvgl_task, "lvgl", 4096, NULL, 2, NULL);
  
  xReturned = xTaskCreate(continuous_adc_read, "adctest", 4096, NULL, 2, NULL);
  
  // xReturned = xTaskCreate(DACtest, "dactest", 2048, NULL, 2, NULL);

  
}