/*

   根据官方continuous_read_main.c示例代码修改的ADC连续采样示例代码
 * 该代码使用ADC连续采样功能，读取ADC数据并打印到控制台。
 * 该代码使用了FreeRTOS任务和信号量来处理ADC数据的读取和打印。
 * 该代码使用了ESP-IDF框架中的ADC数字接口和其他相关库。
 */
#ifndef ADC_H
#define ADC_H

#include <math.h>
#include <string.h>
#include <stdio.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_adc/adc_continuous.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "freertos/semphr.h"


#define EXAMPLE_ADC_UNIT                    ADC_UNIT_1
#define _EXAMPLE_ADC_UNIT_STR(unit)         #unit
#define EXAMPLE_ADC_UNIT_STR(unit)          _EXAMPLE_ADC_UNIT_STR(unit)
#define EXAMPLE_ADC_CONV_MODE               ADC_CONV_SINGLE_UNIT_1
#define EXAMPLE_ADC_ATTEN                   ADC_ATTEN_DB_11
#define EXAMPLE_ADC_BIT_WIDTH               SOC_ADC_DIGI_MAX_BITWIDTH

#if CONFIG_IDF_TARGET_ESP32 || CONFIG_IDF_TARGET_ESP32S2
#define EXAMPLE_ADC_OUTPUT_TYPE             ADC_DIGI_OUTPUT_FORMAT_TYPE1
#define EXAMPLE_ADC_GET_CHANNEL(p_data)     ((p_data)->type1.channel)
#define EXAMPLE_ADC_GET_DATA(p_data)        ((p_data)->type1.data)
#else
#define EXAMPLE_ADC_OUTPUT_TYPE             ADC_DIGI_OUTPUT_FORMAT_TYPE2
#define EXAMPLE_ADC_GET_CHANNEL(p_data)     ((p_data)->type2.channel)
#define EXAMPLE_ADC_GET_DATA(p_data)        ((p_data)->type2.data)
#endif

#define EXAMPLE_READ_LEN                    256


typedef struct adc_continuous_struct
{
    
    uint32_t adc_buffer_temp[5];// 温度、电流环输出、输出电压、输入电压、电流
    uint32_t adc_count[5];
    uint16_t temp;
    uint32_t cc_loop;
    uint16_t output_vol[2];
    uint16_t outV;
    uint16_t input_vol[2];
    // uint16_t inV;
    uint16_t output_current[2]; 
    uint16_t outI;
    SemaphoreHandle_t adc_semaphore; // ADC信号量

}adc_continuous_item;
extern float system_vol;
extern adc_continuous_item ADC; //ADC数据结构体
void adc_continuous_read_task(void *arg);
void adc_oneshot_read_task(void *arg);
void continuous_adc_read(void* arg);
#endif