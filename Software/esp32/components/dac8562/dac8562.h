#ifndef _dac8562_h_
#define _dac8562_h_


#include "driver/spi_master.h"
#include "driver/gpio.h"
#include <esp_log.h>
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define DAC_SPI_HOST    VSPI_HOST
#define DAC_CS_GPIO     5
#define DAC_LDAC_GPIO   13  // 可选
// DAC8562寄存器定义
#define DAC_RESET         0x28
#define DAC_SETUP         0x38
#define DAC_HARDWARE_LDAC 0x30
#define DAC_WRITE_REG_A   0x18
#define DAC_WRITE_REG_B   0x19


void dac8562_set_voltage(uint8_t channel, float voltage);
esp_err_t dac8562_init(void);
void dac8562_write_command(uint8_t command, uint16_t data);
#endif