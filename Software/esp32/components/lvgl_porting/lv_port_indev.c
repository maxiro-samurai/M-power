/**
 * @file lv_port_indev_templ.c
 *
 */

/*Copy this file as "lv_port_indev.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_indev.h"
// #include "../../lvgl.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

// static void touchpad_init(void);
// static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
// static bool touchpad_is_pressed(void);
// static void touchpad_get_xy(lv_coord_t * x, lv_coord_t * y);

// static void mouse_init(void);
// static void mouse_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
// static bool mouse_is_pressed(void);
// static void mouse_get_xy(lv_coord_t * x, lv_coord_t * y);

// static void keypad_init(void);
// static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
// static uint32_t keypad_get_key(void);
static void keypad_read(lv_indev_drv_t *drv, lv_indev_data_t *data);

static void encoder_init(void);
static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static void encoder_handler(void);

static void button_init(void);
static void button_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static int8_t button_get_pressed_id(void);
static bool button_is_pressed(uint8_t id);

/**********************
 *  STATIC VARIABLES
 **********************/
// lv_indev_t * indev_touchpad;
// lv_indev_t * indev_mouse;
// lv_indev_t * indev_keypad;
lv_indev_t * indev_encoder;
// lv_indev_t * indev_button;
lv_group_t * g ;
static int32_t encoder_diff;
static lv_indev_state_t encoder_state;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{
    /**
     * Here you will find example implementation of input devices supported by LittelvGL:
     *  - Touchpad
     *  - Mouse (with cursor support)
     *  - Keypad (supports GUI usage only with key)
     *  - Encoder (supports GUI usage only with: left, right, push)
     *  - Button (external buttons to press points on the screen)
     *
     *  The `..._read()` function are only examples.
     *  You should shape them according to your hardware
     */

    static lv_indev_drv_t indev_drv;


    /*------------------
     * Encoder
     * -----------------*/

    /*Initialize your encoder if you have*/
    encoder_init();

    /*Register a encoder input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = encoder_read;
    indev_encoder = lv_indev_drv_register(&indev_drv);
    
    //注册组
    g = lv_group_create();
    lv_group_set_default(g);
    lv_indev_set_group(indev_encoder, g);
    /*Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
     *add objects to the group with `lv_group_add_obj(group, obj)`
     *and assign this input device to group to navigate in it:
     *`lv_indev_set_group(indev_encoder, group);`*/

    // /*Register a keypad input device*/
    // lv_indev_drv_init(&indev_drv_button);
    // indev_drv_button.type = LV_INDEV_TYPE_KEYPAD;
    // indev_drv_button.read_cb = keypad_read;
    // indev_keypad = lv_indev_drv_register(&indev_drv_button);
    // lv_indev_set_group(indev_keypad, g);
    // /*------------------
    //  * Button
    //  * -----------------*/

    // /*Initialize your button if you have*/
    // button_init();

    // /*Register a button input device*/
    // lv_indev_drv_init(&indev_drv_button);
    // indev_drv_button.type = LV_INDEV_TYPE_BUTTON;
    // indev_drv_button.read_cb = button_read;
    // indev_button = lv_indev_drv_register(&indev_drv_button);
    // lv_indev_set_group(indev_button, g);
    // /*Assign buttons to points on the screen*/
    // static const lv_point_t btn_points[2] = {
    //     {10, 10},   /*Button 0 -> x:10; y:10*/
    //     {40, 100},  /*Button 1 -> x:40; y:100*/
    // };
    // lv_indev_set_button_points(indev_button, btn_points);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
// static void keypad_read(lv_indev_drv_t *drv, lv_indev_data_t *data) {
//    int GPIO_LEVEL ; //读取GPIO电平

//     GPIO_LEVEL = gpio_get_level(BTN_GPIO);

//     if (GPIO_LEVEL == 0) {
//         data->key = LV_KEY_ENTER;     // 获取键值（如LV_KEY_ENTER）
//         data->state = LV_INDEV_STATE_PR; // 获取状态（LV_INDEV_STATE_PRESSED/RELEASED）
//         printf("按键按下\n");
//     } else {
//         data->state = LV_INDEV_STATE_REL; // 松开状态
//     }

   
// }
/*------------------
 * Encoder
 * -----------------*/

/*Initialize your keypad*/
static void encoder_init(void)
{
    /*Your code comes here*/

    rotary_encoder_init();
    encoder_diff = 0;
    encoder_state = LV_INDEV_STATE_REL;
}

/*Will be called by the library to read the encoder*/
static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    int GPIO_LEVEL ; //读取GPIO电平
    GPIO_LEVEL = gpio_get_level(EXAMPLE_KEY_GPIO);
    

    if (GPIO_LEVEL == 0) {
       
        encoder_state = LV_INDEV_STATE_PR;
    } else {
       
        encoder_state = LV_INDEV_STATE_REL;
    }
    
    data->state = encoder_state;
    encoder_diff = encoder_state_detection();
    data->enc_diff = encoder_diff;
}

/*Call this function in an interrupt to process encoder events (turn, press)*/
static void encoder_handler(void)
{
    /*Your code comes here*/

    encoder_diff += 0;
    encoder_state = LV_INDEV_STATE_REL;
}

// /*------------------
//  * Button
//  * -----------------*/

// /*Initialize your buttons*/
// static void button_init(void)
// {
//     /*Your code comes here*/
// }

// /*Will be called by the library to read the button*/
// static void button_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
// {

//     static uint8_t last_btn = 0;
//     int GPIO_LEVEL ; //读取GPIO电平

//     GPIO_LEVEL = gpio_get_level(BTN_GPIO);
//     // /*Get the pressed button's ID*/
//     // int8_t btn_act = button_get_pressed_id();

//     // if(btn_act >= 0) {
//     //     data->state = LV_INDEV_STATE_PR;
//     //     last_btn = btn_act;
//     // }
//     // else {
//     //     data->state = LV_INDEV_STATE_REL;
//     // }
//     if (GPIO_LEVEL == 0) {
//         data->state = LV_INDEV_STATE_PR;
//         data->key  = LV_KEY_HOME;
//         last_btn = 1; // 按钮被按下
//         printf("按键按下\n");
//     } else {
//         data->state = LV_INDEV_STATE_REL;
//         last_btn = -1; // 按钮未按下
//     }
//     /*Save the last pressed button's ID*/
//     data->btn_id = last_btn;
// }

// // /*Get ID  (0, 1, 2 ..) of the pressed button*/
// static int8_t button_get_pressed_id(void)
// {
//     // uint8_t i;

//     /*Check to buttons see which is being pressed (assume there are 2 buttons)*/
//     // for(i = 0; i < 2; i++) {
//         /*Return the pressed button's ID*/
//         if(button_is_pressed(i)) {
//             return i;
//         }
//     // }

//     /*No button pressed*/
//     return -1;
// }

// // /*Test if `id` button is pressed or not*/
// static bool button_is_pressed(uint8_t id)
// {


//     /*Your code comes here*/

//     return false;
// }

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
