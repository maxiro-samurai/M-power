#include "control.h"


bool output_enable = true; 


void output_ramp(uint16_t set_voltage)
{

    uint16_t dac_value = 0;
    static uint8_t percent_u = 100;

    static uint16_t u_now ,u_tar;
    static short u_gap;
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
    
    printf("Current Voltage: %d\n", u_now);
    dac_value = 63549-13.504*u_now;
    dac8562_write_command(DAC_WRITE_REG_A, dac_value);
}



void control_output_task(void *arg)
{
   

    while (1)
    {   
        //如果输出使能能
        if(output_enable){
            gpio_set_level(LM5175_EN_GPIO, 1); //开启LM5175 
            
            out_value_refresh();
            output_ramp(set_voltage);
            // dac_value = 63549-13.504*set_voltage;
            // dac8562_write_command(DAC_WRITE_REG_A, dac_value);

        }

        else {

            //
           
            gpio_set_level(LM5175_EN_GPIO, 0); //关闭LM5175 

        }

        vTaskDelay(pdMS_TO_TICKS(50)); // 延时100ms
    }
    
}