#ifndef M_POWER_H
#define M_POWER_H

#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include "pwm.h"
#include "beep.h"
#include "dac8562.h"
#include "adc.h"
#include "st7789.h"
#include "lvgl_helpers.h"
#include "lvgl.h"
#include "rotary_encoder.h"
#include "esp_err.h"
#include "esp_timer.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "ui.h"
#include "control.h"
#include "bluetooth.h"
#define LM5175_EN_GPIO 0 // GPIO number for the key input

#endif