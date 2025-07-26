idf_component_register(SRCS "control.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp_adc dac8562 ui driver main)