#include "pwm.h"
/***
*@description:电荷泵两相驱动
*/
void pwm_init(void)
{
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQUENCY,  // 
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // A相初始化
    ledc_channel_config_t ledc_channel_a = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL_A,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IOA,
        .duty           = LEDC_DUTY, // Set duty to 50%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel_a));

    // B相初始化
    ledc_channel_config_t ledc_channel_b = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL_B,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IOB,
        .duty           = LEDC_DUTY, // Set duty to 50%
        .hpoint         = LEDC_DUTY
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel_b));

    ledc_stop(LEDC_MODE, LEDC_CHANNEL_A, 0);  // 
    ledc_stop(LEDC_MODE, LEDC_CHANNEL_B, 0);  // 
}

/*** 
 * @description: 启动PWM输出
 * @param channel: LEDC_CHANNEL_A for A相, LEDC_CHANNEL_B for B相
 */
void pwm_start(uint8_t channel)
{
    ledc_set_duty(LEDC_MODE, channel, LEDC_DUTY);
    ledc_update_duty(LEDC_MODE, channel);
}

/*** 
 * @description: 关闭PWM输出
 * @param channel: LEDC_CHANNEL_A for A相, LEDC_CHANNEL_B for B相
 */
void pwm_stop(uint8_t channel)
{
    ledc_stop(LEDC_MODE, channel, 0);  // 
}