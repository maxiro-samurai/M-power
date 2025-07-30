#ifndef _control_h
#define _control_h

#include "dac8562.h"
#include "adc.h"
#include "ui.h"
#include "M-power.h"
#include "rotary_encoder.h"
#include "driver/gptimer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "bluetooth.h"
#include "beep.h"

#define RED_LED_PIN         10
#define GREEN_LED_PIN       9
void control_output_task(void *arg);
#endif