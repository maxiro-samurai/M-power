#include "dac8562.h"


static spi_device_handle_t dac_spi;

static const char *TAG = "DAC8562";

void dac8562_write_command(uint8_t command, uint16_t data)
{
    spi_transaction_t t = {
        .length = 24,
        .flags = SPI_TRANS_USE_TXDATA
    };
    t.tx_data[0] = command;
    t.tx_data[1] = (data >> 8) & 0xFF;
    t.tx_data[2] = data & 0xFF;
    ESP_ERROR_CHECK(spi_device_polling_transmit(dac_spi, &t));
}

void dac8562_set_voltage(uint8_t channel, float voltage)
{
    uint16_t dac_value = (uint16_t)((voltage / 3.3) * 65535.0);
    uint8_t cmd = (channel == 0) ? DAC_WRITE_REG_A : DAC_WRITE_REG_B;
    dac8562_write_command(cmd, dac_value);

    // 触发LDAC更新
    gpio_set_level(DAC_LDAC_GPIO, 0);
    vTaskDelay(1 / portTICK_PERIOD_MS);
    gpio_set_level(DAC_LDAC_GPIO, 1);
}

esp_err_t dac8562_init(void) {
   
    spi_device_interface_config_t devcfg = {
        .command_bits = 0,
        .address_bits = 0,
        .dummy_bits = 0,
        .mode = 1,  // SPI模式1 (CPOL=0, CPHA=1)
        .duty_cycle_pos = 128,
        .cs_ena_pretrans = 1,
        .cs_ena_posttrans = 1,
        .clock_speed_hz = 20 * 1000 * 1000,  // 20 MHz 与SPI一样
        .spics_io_num = DAC_CS_GPIO,
        .queue_size = 3,
    };
    
    // 初始化SPI总线  总线只初始化一次
    // ESP_ERROR_CHECK(spi_bus_initialize(DAC_SPI_HOST, &buscfg, SPI_DMA_DISABLED));
    
    // 添加SPI设备
    esp_err_t ret = spi_bus_add_device(DAC_SPI_HOST, &devcfg, &dac_spi);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to add SPI device: %s", esp_err_to_name(ret));
        return ret;
    }
    
    ESP_LOGI(TAG, "SPI device added on CS pin %d", DAC_CS_GPIO);
    return ESP_OK;
    // 初始化LDAC引脚（可选）
    gpio_set_direction(DAC_LDAC_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(DAC_LDAC_GPIO, 1);  // 默认为高


    
     // DAC初始化
    dac8562_write_command(DAC_RESET, 0x0001); // 重启
    vTaskDelay(10 / portTICK_PERIOD_MS);

    dac8562_write_command(DAC_SETUP, 0x0000); // 使用外部参考 gain 1
    dac8562_write_command(DAC_HARDWARE_LDAC, 0x0003); // 先调试禁用LDAC
}



