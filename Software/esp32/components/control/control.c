#include "control.h"


bool output_enable = true; 


// void output_ramp()
// {
//     static uint32_t current_voltage = 0;
    
// }



void control_output_task(void *arg)
{
   uint16_t dac_value = 0;

    while (1)
    {   
        //如果输出使能能
        if(output_enable){
            gpio_set_level(LM5175_EN_GPIO, 1); //开启LM5175 
            out_value_refresh();
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