#include "adc.h"

float system_vol ;
static adc_channel_t channel[5] = {ADC_CHANNEL_0,ADC_CHANNEL_2,ADC_CHANNEL_3,ADC_CHANNEL_6, ADC_CHANNEL_7};// 温度、电流环输出、输出电压、输入电压、电流
adc_continuous_item ADC = {

    .adc_buffer_temp = {0},
};
// static adc_continuous_handle_t handle = NULL;
static TaskHandle_t s_task_handle;
static const char *TAG = "EXAMPLE";
adc_cali_handle_t adc1_cali_handle ;
static bool example_adc_calibration_init(adc_unit_t unit, adc_channel_t channel, adc_atten_t atten, adc_cali_handle_t *out_handle);
static void example_adc_calibration_deinit(adc_cali_handle_t handle);



static bool IRAM_ATTR s_conv_done_cb(adc_continuous_handle_t handle, const adc_continuous_evt_data_t *edata, void *user_data)
{
    BaseType_t mustYield = pdFALSE;
    //Notify that ADC continuous driver has done enough number of conversions
    vTaskNotifyGiveFromISR(s_task_handle, &mustYield);

    return (mustYield == pdTRUE);
}

static void continuous_adc_init(adc_channel_t *channel, uint8_t channel_num, adc_continuous_handle_t *out_handle)
{
    adc_continuous_handle_t handle = NULL;

    adc_continuous_handle_cfg_t adc_config = {
        .max_store_buf_size = 1024,
        .conv_frame_size = EXAMPLE_READ_LEN,
    };
    ESP_ERROR_CHECK(adc_continuous_new_handle(&adc_config, &handle));

    adc_continuous_config_t dig_cfg = {
        .sample_freq_hz = 20 * 1000,
        .conv_mode = EXAMPLE_ADC_CONV_MODE,
        .format = EXAMPLE_ADC_OUTPUT_TYPE,
    }; 
    adc_digi_pattern_config_t adc_pattern[SOC_ADC_PATT_LEN_MAX] = {0};
    dig_cfg.pattern_num = channel_num;
    for (int i = 0; i < channel_num; i++) {
        adc_pattern[i].channel = channel[i] & 0x7;
        adc_pattern[i].atten = EXAMPLE_ADC_ATTEN;
        adc_pattern[i].unit = EXAMPLE_ADC_UNIT;
        adc_pattern[i].bit_width = EXAMPLE_ADC_BIT_WIDTH;

        ESP_LOGI(TAG, "adc_pattern[%d].atten is :%"PRIx8, i, adc_pattern[i].atten);
        ESP_LOGI(TAG, "adc_pattern[%d].channel is :%"PRIx8, i, adc_pattern[i].channel);
        ESP_LOGI(TAG, "adc_pattern[%d].unit is :%"PRIx8, i, adc_pattern[i].unit);
    }
    dig_cfg.adc_pattern = adc_pattern;
    ESP_ERROR_CHECK(adc_continuous_config(handle, &dig_cfg));

    *out_handle = handle;
}

// 初始化ADC结构体

void adc_data_init(){

    memset(&ADC, 0, sizeof(adc_continuous_item));

    ADC.adc_semaphore = xSemaphoreCreateMutex();
    if (ADC.adc_semaphore == NULL) {
        ESP_LOGE(TAG, "Failed to create ADC semaphore");

    }
}


int get_channel_index(uint32_t chan_num){
    switch(chan_num){

        case ADC_CHANNEL_0:
            return 0;
        case ADC_CHANNEL_2:
            return 1;
        case ADC_CHANNEL_3:
            return 2;
        case ADC_CHANNEL_6:
            return 3;
        case ADC_CHANNEL_7:
            return 4;
        default:
            return -1;
    }
}
void adc_caculate_all_data(void){

    uint16_t average;
    uint32_t mV;
    int rt ;
    
    //温度
    average = (ADC.adc_buffer_temp[0] + ADC.adc_count[0] / 2) / ADC.adc_count[0]; // 四舍五入的整数除法
    ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc1_cali_handle, average, &mV));
    // ESP_LOGI(TAG, "Cali Voltage: %lu mV",mV);

    rt = mV * 1000 / (3300 - mV);  
    ADC.temp = (100 / (log(rt / 10000.0) / 3950 + 1 / 298.15) - 27315) / 100; //转换为温度值
    // ESP_LOGI(TAG, "温度: %u°C",ADC.temp);

    // //电流环输出
    // average = (ADC.adc_buffer_temp[1] + ADC.adc_count[1] / 2) / ADC.adc_count[1]; // 四舍五入的整数除法
    // ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc1_cali_handle, average, &ADC.cc_loop));
    // ESP_LOGI(TAG, "Cali Voltage: %lu mV",ADC.cc_loop);

    //输出电压
    average = (ADC.adc_buffer_temp[2] + ADC.adc_count[2] / 2) / ADC.adc_count[2]; // 四舍五入的整数除法
    // ESP_LOGI(TAG, "Cali Voltage: %d mV",average*11865/10000);
    ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc1_cali_handle, average, &mV));
    // ESP_LOGI(TAG, "Cali Voltage: %lu mV",mV);
    ADC.outV = mV * 1471 / 1000; // 扩大了100倍 避免浮点运算
    ADC.output_vol[0] = mV*1471/100000;
    ADC.output_vol[1] =(mV*1471/1000)%100;
    // ESP_LOGI(TAG, "out Voltage: %d",ADC.outV);
    // ESP_LOGI(TAG, "output Voltage: %02d.%02dV",ADC.output_vol[0],ADC.output_vol[1]);


    //输入电压
    average = (ADC.adc_buffer_temp[3] + ADC.adc_count[3] / 2) / ADC.adc_count[3]; // 四舍五入的整数除法
    ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc1_cali_handle, average, &mV));
    // ESP_LOGI(TAG, "Cali Voltage: %lu mV",mV);

    ADC.input_vol[0] = mV*1571/100000; // 扩大了100倍 避免浮点运算
    ADC.input_vol[1] = (mV * 1571 / 1000) % 100;
    // ESP_LOGI(TAG, "input Voltage: %02d.%02dV",ADC.input_vol[0],ADC.input_vol[1]);





    //电流
    // average = (ADC.adc_buffer_temp[4] + ADC.adc_count[4] / 2) / ADC.adc_count[4]; // 四舍五入的整数除法
    // ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc1_cali_handle, average, &ADC.current));
    // ESP_LOGI(TAG, "Cali Voltage: %lu mV",ADC.current);
   
  


}


void continuous_adc_read(void* arg){

    esp_err_t ret;
    uint32_t ret_num = 0;
    uint8_t result[EXAMPLE_READ_LEN] = {0};
    memset(result, 0xcc, EXAMPLE_READ_LEN);

    s_task_handle = xTaskGetCurrentTaskHandle();

    adc_continuous_handle_t handle = NULL;
    continuous_adc_init(channel, sizeof(channel) / sizeof(adc_channel_t), &handle);

    adc_continuous_evt_cbs_t cbs = {
        .on_conv_done = s_conv_done_cb,
    };

    ESP_ERROR_CHECK(adc_continuous_register_event_callbacks(handle, &cbs, NULL));
    ESP_ERROR_CHECK(adc_continuous_start(handle));
    
    bool do_calibration1_chan2 = example_adc_calibration_init(ADC_UNIT_1, ADC_CHANNEL_6, ADC_ATTEN_DB_11, &adc1_cali_handle);

    while(1){

        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        char unit[] = EXAMPLE_ADC_UNIT_STR(EXAMPLE_ADC_UNIT);

        while (1)
        {
            ret = adc_continuous_read(handle, result, EXAMPLE_READ_LEN, &ret_num, 0);
            if (ret == ESP_OK) {
                // ESP_LOGI("TASK", "ret is %x, ret_num is %"PRIu32" bytes", ret, ret_num);
                for (int i = 0; i < ret_num; i += SOC_ADC_DIGI_RESULT_BYTES) {
                    adc_digi_output_data_t *p = (void*)&result[i];
                    uint32_t chan_num = EXAMPLE_ADC_GET_CHANNEL(p);
                    uint32_t data = EXAMPLE_ADC_GET_DATA(p);
                    /* Check the channel number validation, the data is invalid if the channel num exceed the maximum channel */
                    if (chan_num < SOC_ADC_CHANNEL_NUM(EXAMPLE_ADC_UNIT)) {
                        // ESP_LOGI(TAG, "Unit: %s, Channel: %"PRIu32", Value: %"PRIx32, unit, chan_num, data);
                        
                        int index = get_channel_index(chan_num);

                        ADC.adc_buffer_temp[index] += data;
                        ADC.adc_count[index]++;

                        
                        
                    } else {
                        ESP_LOGW(TAG, "Invalid data [%s_%"PRIu32"_%"PRIx32"]", unit, chan_num, data);
                    }
                }
                
                adc_caculate_all_data();
                //清空数据和计数器
                for (int i = 0; i <5; i++) {
                    ADC.adc_buffer_temp[i] = 0;
                    ADC.adc_count[i] = 0;
                }
                vTaskDelay(1);
            } else if (ret == ESP_ERR_TIMEOUT) {
                //We try to read `EXAMPLE_READ_LEN` until API returns timeout, which means there's no available data
                break;
            }
        }

    }
    ESP_ERROR_CHECK(adc_continuous_stop(handle));
    ESP_ERROR_CHECK(adc_continuous_deinit(handle));


}




// /*

// 获取电压值

// */
// static void adc_oneshot_get_voltage(adc_oneshot_unit_handle_t adc1_handle,adc_cali_handle_t adc1_cali_chan0_handle ,adc_cali_handle_t adc1_cali_chan1_handle){
//     uint8_t i;
//     uint32_t adc_temp1 = 0;
//     uint32_t adc_temp2 = 0;
//     for (i = 0; i < 8; i++) //读8次ADC值 求平均
//     {
        
        
//         adc_oneshot_read(adc1_handle, ADC_CHANNEL_6, &ADC.adc_buffer_1[i]); //存储ADC值
//         // ESP_LOGI(TAG, "ADC%d Channel[%d] Raw Data: %d", ADC_UNIT_1 + 1, EXAMPLE_ADC1_CHAN0, ADC.adc_buffer_1[i]);
//         adc_oneshot_read(adc1_handle, ADC_CHANNEL_7, &ADC.adc_buffer_2[i]); //存储ADC值
//         // ESP_LOGI(TAG, "ADC%d Channel[%d] Raw Data: %d", ADC_UNIT_1 + 1, EXAMPLE_ADC1_CHAN1, adc_raw[0][1]);
//         adc_temp1 += ADC.adc_buffer_1[i]; //低电平ADC值
//         adc_temp2 += ADC.adc_buffer_2[i]; //高电平ADC值
//     }
    
//     adc_temp1 >>= 3; //平均值滤波
//     adc_temp2 >>= 3; //
    
    
//     ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc1_cali_chan0_handle, adc_temp1, &ADC.vol_low));
//     ESP_LOGI(TAG, "ADC%d Channel[%d] Cali Voltage: %lu mV", ADC_UNIT_1 + 1, ADC_CHANNEL_6, ADC.vol_low);


//     ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc1_cali_chan1_handle, adc_temp2, &ADC.vol_high));
//     ESP_LOGI(TAG, "ADC%d Channel[%d] Cali Voltage: %lu mV", ADC_UNIT_1 + 1, ADC_CHANNEL_7, ADC.vol_high);

    
    
// }

static void adc_get_sys_vol(adc_oneshot_unit_handle_t adc1_handle,adc_cali_handle_t adc1_cali_chan0_handle )
{
    uint32_t adc_temp;
    uint32_t vol_temp;
    adc_oneshot_read(adc1_handle, ADC_CHANNEL_6, &adc_temp); //存储ADC值

    ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc1_cali_chan0_handle, adc_temp, &vol_temp));
    ESP_LOGI(TAG, "Cali Voltage: %lu mV",vol_temp);
    system_vol = (float)(vol_temp*15.70f/1000.0f);

    ESP_LOGI(TAG, "System Voltage: %.2f V", system_vol);
    
}











void adc_oneshot_read_task(void *arg)
{
    //-------------ADC1 Init---------------//
    adc_oneshot_unit_handle_t adc1_handle;
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));

    //-------------ADC1 Config---------------//
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_0,
    };
    // 系统电压检测
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_6, &config));
    // config.atten = EXAMPLE_ADC_ATTEN;
    // 热敏电阻
    // ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_6, &config));
    // ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_7, &config));

    //-------------ADC1 Calibration Init---------------//
    // adc_cali_handle_t adc1_cali_chan0_handle = NULL;
    // adc_cali_handle_t adc1_cali_chan1_handle = NULL;
    adc_cali_handle_t adc1_cali_chan2_handle = NULL;
    
    // bool do_calibration1_chan0 = example_adc_calibration_init(ADC_UNIT_1, ADC_CHANNEL_6, EXAMPLE_ADC_ATTEN, &adc1_cali_chan0_handle);
    // bool do_calibration1_chan1 = example_adc_calibration_init(ADC_UNIT_1, ADC_CHANNEL_7, EXAMPLE_ADC_ATTEN, &adc1_cali_chan1_handle);
    bool do_calibration1_chan2 = example_adc_calibration_init(ADC_UNIT_1, ADC_CHANNEL_6, ADC_ATTEN_DB_0, &adc1_cali_chan2_handle);



    while (1)
    {
        // adc_oneshot_get_voltage(adc1_handle,adc1_cali_chan0_handle,adc1_cali_chan1_handle); //获取电压值
        adc_get_sys_vol(adc1_handle,adc1_cali_chan2_handle);
        // adc_temp(&ADC); //获取温度值
        vTaskDelay(1000); //延时1ms
    }



}


/*---------------------------------------------------------------
        ADC Calibration
---------------------------------------------------------------*/
static bool example_adc_calibration_init(adc_unit_t unit, adc_channel_t channel, adc_atten_t atten, adc_cali_handle_t *out_handle)
{
    adc_cali_handle_t handle = NULL;
    esp_err_t ret = ESP_FAIL;
    bool calibrated = false;

if (!calibrated) {
        ESP_LOGI(TAG, "calibration scheme version is %s", "Line Fitting");
        adc_cali_line_fitting_config_t cali_config = {
            .unit_id = unit,
            .atten = atten,
            .bitwidth = EXAMPLE_ADC_BIT_WIDTH,
        };
        ret = adc_cali_create_scheme_line_fitting(&cali_config, &handle);
        if (ret == ESP_OK) {
            calibrated = true;
        }
}


    *out_handle = handle;
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Calibration Success");
    } else if (ret == ESP_ERR_NOT_SUPPORTED || !calibrated) {
        ESP_LOGW(TAG, "eFuse not burnt, skip software calibration");
    } else {
        ESP_LOGE(TAG, "Invalid arg or no memory");
    }

    return calibrated;
}

static void example_adc_calibration_deinit(adc_cali_handle_t handle)
{
    ESP_LOGI(TAG, "deregister %s calibration scheme", "Line Fitting");
    ESP_ERROR_CHECK(adc_cali_delete_scheme_line_fitting(handle));

}
