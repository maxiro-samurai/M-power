idf_component_register(SRCS  "lv_port_disp.c"  "lv_port_indev.c" "lv_port_fs.c"            
                       INCLUDE_DIRS "."
                       REQUIRES  driver lvgl rotary_encoder
                       PRIV_REQUIRES lcd )