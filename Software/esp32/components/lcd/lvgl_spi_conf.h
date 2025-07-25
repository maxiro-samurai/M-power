/**
 * @file lvgl_spi_conf.h
 *
 */

#ifndef LVGL_SPI_CONF_H
#define LVGL_SPI_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/
// DISPLAY PINS
#define DISP_SPI_IO2 (-1)
#define DISP_SPI_IO3 (-1)
#define DISP_SPI_MISO (-1)
#define DISP_SPI_INPUT_DELAY_NS (0)

#define DISP_SPI_MOSI ST7789_MOSI_GPIO
#define DISP_SPI_CLK ST7789_SCLK_GPIO

#define DISP_SPI_CS ST7789_CS_GPIO


#define TFT_SPI_HOST ST7789_SPI_HOST
#define CONFIG_LV_TFT_DISPLAY_CONTROLLER_ST7789 1


#define DISP_SPI_FULL_DUPLEX



#define DISP_SPI_TRANS_MODE_SIO



#define CONFIG_LV_TFT_DISPLAY_PROTOCOL_SPI 1
/**********************
 *      TYPEDEFS
 **********************/


#if defined (CONFIG_LV_TFT_DISPLAY_CONTROLLER_ST7789)   
     




#define SPI_BUS_MAX_TRANSFER_SZ (DISP_BUF_SIZE * 2)
#endif



#if defined (CONFIG_LV_TFT_DISPLAY_CONTROLLER_ST7789)
#define SPI_TFT_CLOCK_SPEED_HZ  (40*1000*1000)


#endif


#if defined (CONFIG_LV_TFT_DISPLAY_CONTROLLER_ST7789)

#define SPI_TFT_SPI_MODE    (0)
#endif


/**********************
 * GLOBAL PROTOTYPES
 **********************/


/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LVGL_SPI_CONF_H*/
