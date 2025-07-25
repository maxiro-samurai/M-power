#ifndef _PWM_H_
#define _PWM_H_

#include <stdio.h>
#include "driver/ledc.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "math.h" 
#include "esp_log.h"

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_HIGH_SPEED_MODE
#define LEDC_OUTPUT_IOA          (33) // Define the output GPIO
#define LEDC_OUTPUT_IOB          (32) // Define the output GPIO
#define LEDC_CHANNEL_A          LEDC_CHANNEL_0
#define LEDC_CHANNEL_B          LEDC_CHANNEL_1
#define LEDC_DUTY_RES           LEDC_TIMER_5_BIT // 
#define LEDC_DUTY               (16) // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define LEDC_FREQUENCY          (1000000) // Frequency in Hertz. Set frequency at 1M Hz

void pwm_init(void);
void pwm_start(uint8_t channel);
void pwm_stop(uint8_t channel);
# endif