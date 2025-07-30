idf_component_register(SRCS "M-power.c"
                       INCLUDE_DIRS "."
                       
                       REQUIRES pwm beep dac8562 adc lcd rotary_encoder lvgl_porting ui control ble)