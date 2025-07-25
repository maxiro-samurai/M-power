idf_component_register(SRCS  "st7789.c"  "disp_driver.c" "disp_spi.c" "lvgl_helpers.c"                      
                       INCLUDE_DIRS "."
                       REQUIRES  driver lvgl)