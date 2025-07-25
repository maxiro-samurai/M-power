/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --font C:/Users/yushilong/SquareLine/assets/consolab.ttf -o C:/Users/yushilong/SquareLine/assets\ui_font_consola14.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_CONSOLA14
#define UI_FONT_CONSOLA14 1
#endif

#if UI_FONT_CONSOLA14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xfc, 0xf0,

    /* U+0022 "\"" */
    0xde, 0xf6,

    /* U+0023 "#" */
    0x24, 0xcb, 0xfb, 0x66, 0xcd, 0xbf, 0xa6, 0x48,

    /* U+0024 "$" */
    0x18, 0xfb, 0xd6, 0x8f, 0xf, 0x87, 0x1b, 0xed,
    0xf0, 0x81, 0x0,

    /* U+0025 "%" */
    0x63, 0x2a, 0x73, 0x41, 0x2, 0xb, 0xb5, 0x4b,
    0x1c,

    /* U+0026 "&" */
    0x78, 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0xf2, 0xde,
    0xcc, 0x7e,

    /* U+0027 "'" */
    0xfc,

    /* U+0028 "(" */
    0x11, 0x98, 0xcc, 0x63, 0x18, 0xc3, 0x18, 0x61,
    0x0,

    /* U+0029 ")" */
    0x43, 0xc, 0x61, 0x8c, 0x63, 0x19, 0x8c, 0xc4,
    0x0,

    /* U+002A "*" */
    0x32, 0xa7, 0x9e, 0xa8, 0xc0,

    /* U+002B "+" */
    0x30, 0x63, 0xf9, 0x83, 0x6, 0x0,

    /* U+002C "," */
    0x66, 0x22, 0xc0,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x6, 0x8, 0x30, 0x41, 0x83, 0xc, 0x18, 0x20,
    0xc1, 0x0,

    /* U+0030 "0" */
    0x38, 0xdb, 0x1e, 0x7f, 0xfe, 0xf1, 0xb6, 0x38,

    /* U+0031 "1" */
    0x33, 0xcb, 0xc, 0x30, 0xc3, 0xc, 0xfc,

    /* U+0032 "2" */
    0x7a, 0x30, 0xc3, 0x1c, 0xe3, 0x18, 0xfc,

    /* U+0033 "3" */
    0xf8, 0x30, 0xc3, 0x78, 0x30, 0xc3, 0xf8,

    /* U+0034 "4" */
    0x1c, 0x38, 0xf3, 0x64, 0xd9, 0xbf, 0x86, 0xc,

    /* U+0035 "5" */
    0xfb, 0xc, 0x30, 0xf8, 0x30, 0xc3, 0xf8,

    /* U+0036 "6" */
    0x3c, 0xc3, 0x6, 0xf, 0xd8, 0xf1, 0xe3, 0x7c,

    /* U+0037 "7" */
    0xfc, 0x31, 0x86, 0x10, 0xc3, 0x18, 0x60,

    /* U+0038 "8" */
    0x7b, 0x3c, 0xfe, 0x3b, 0xbc, 0x71, 0x78,

    /* U+0039 "9" */
    0x7d, 0x9b, 0x1e, 0x37, 0xe0, 0xc1, 0x86, 0x78,

    /* U+003A ":" */
    0xf0, 0x3c,

    /* U+003B ";" */
    0x66, 0x0, 0x26, 0x62, 0x6c,

    /* U+003C "<" */
    0x0, 0xcc, 0xcc, 0x30, 0xe1,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0x3, 0x87, 0x6, 0xc, 0xe6, 0x10,

    /* U+003F "?" */
    0xe1, 0x86, 0x31, 0xb9, 0x80, 0xc6, 0x0,

    /* U+0040 "@" */
    0x1c, 0x36, 0x63, 0x63, 0xdf, 0xf7, 0xf7, 0xfb,
    0xfb, 0xfe, 0xc0, 0x64, 0x3c,

    /* U+0041 "A" */
    0x18, 0x38, 0x3c, 0x2c, 0x64, 0x66, 0x7e, 0xc6,
    0xc3,

    /* U+0042 "B" */
    0xfb, 0x2c, 0xf2, 0xfb, 0x3c, 0xf3, 0xf8,

    /* U+0043 "C" */
    0x3e, 0xc7, 0x6, 0xc, 0x18, 0x30, 0x31, 0x3e,

    /* U+0044 "D" */
    0xf9, 0x9b, 0x1e, 0x3c, 0x78, 0xf1, 0xe6, 0xf8,

    /* U+0045 "E" */
    0xff, 0xc, 0x30, 0xff, 0xc, 0x30, 0xfc,

    /* U+0046 "F" */
    0xff, 0xc, 0x30, 0xfb, 0xc, 0x30, 0xc0,

    /* U+0047 "G" */
    0x3e, 0xc3, 0x6, 0xc, 0xf8, 0xf1, 0xb3, 0x3e,

    /* U+0048 "H" */
    0xc7, 0x8f, 0x1e, 0x3f, 0xf8, 0xf1, 0xe3, 0xc6,

    /* U+0049 "I" */
    0xfc, 0xc3, 0xc, 0x30, 0xc3, 0xc, 0xfc,

    /* U+004A "J" */
    0x7c, 0x30, 0xc3, 0xc, 0x30, 0xe3, 0xf8,

    /* U+004B "K" */
    0xcd, 0x9b, 0x67, 0x8f, 0x1a, 0x36, 0x66, 0xce,

    /* U+004C "L" */
    0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xfc,

    /* U+004D "M" */
    0xef, 0xdf, 0xbf, 0x7d, 0x7a, 0xf1, 0xe3, 0xc6,

    /* U+004E "N" */
    0xe7, 0xcf, 0x9f, 0xbd, 0x7b, 0xf3, 0xe7, 0xce,

    /* U+004F "O" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xb6, 0x38,

    /* U+0050 "P" */
    0xfb, 0x3c, 0xf3, 0xcf, 0xec, 0x30, 0xc0,

    /* U+0051 "Q" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xe7, 0x7c,
    0x70, 0x48, 0x70,

    /* U+0052 "R" */
    0xf9, 0x9b, 0x36, 0x6f, 0x1b, 0x32, 0x66, 0xcc,

    /* U+0053 "S" */
    0x7d, 0x83, 0x7, 0x87, 0xc3, 0x83, 0x6, 0xf8,

    /* U+0054 "T" */
    0xfe, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18, 0x30,

    /* U+0055 "U" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0x7c,

    /* U+0056 "V" */
    0xc3, 0xc6, 0x66, 0x66, 0x64, 0x2c, 0x3c, 0x38,
    0x18,

    /* U+0057 "W" */
    0xc7, 0x8f, 0x1e, 0xbd, 0x7d, 0xfb, 0xf7, 0xee,

    /* U+0058 "X" */
    0xc6, 0x66, 0x3c, 0x38, 0x18, 0x3c, 0x6c, 0x66,
    0xc6,

    /* U+0059 "Y" */
    0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x18, 0x18,
    0x18,

    /* U+005A "Z" */
    0xfc, 0x31, 0x86, 0x31, 0x86, 0x30, 0xfc,

    /* U+005B "[" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xf0,

    /* U+005C "\\" */
    0xc3, 0x6, 0x18, 0x20, 0xc1, 0x6, 0x18, 0x30,
    0xc0,

    /* U+005D "]" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0xf0,

    /* U+005E "^" */
    0x20, 0xc5, 0xb2, 0x8c,

    /* U+005F "_" */
    0xff,

    /* U+0060 "`" */
    0x61, 0x80,

    /* U+0061 "a" */
    0x78, 0x30, 0xdf, 0xcf, 0x37, 0xc0,

    /* U+0062 "b" */
    0xc3, 0xc, 0x3e, 0xef, 0x3c, 0xf3, 0xcb, 0xe0,

    /* U+0063 "c" */
    0x3d, 0x9c, 0x30, 0xc3, 0x87, 0xc0,

    /* U+0064 "d" */
    0xc, 0x30, 0xdf, 0xcf, 0x3c, 0xf3, 0xdd, 0xf0,

    /* U+0065 "e" */
    0x38, 0x9b, 0x17, 0xfc, 0x18, 0x1f, 0x0,

    /* U+0066 "f" */
    0xe, 0x30, 0x60, 0xc7, 0xe3, 0x6, 0xc, 0x18,
    0x30,

    /* U+0067 "g" */
    0x3f, 0x66, 0x66, 0x66, 0x3c, 0x60, 0x7e, 0x62,
    0x62, 0x7c,

    /* U+0068 "h" */
    0xc3, 0xc, 0x3e, 0xef, 0x3c, 0xf3, 0xcf, 0x30,

    /* U+0069 "i" */
    0x30, 0xc0, 0x3c, 0x30, 0xc3, 0xc, 0x33, 0xf0,

    /* U+006A "j" */
    0xc, 0x30, 0x1f, 0xc, 0x30, 0xc3, 0xc, 0x30,
    0xe3, 0xf8,

    /* U+006B "k" */
    0xc1, 0x83, 0x6, 0x6d, 0x9e, 0x3c, 0x6c, 0xdd,
    0x98,

    /* U+006C "l" */
    0xf0, 0xc3, 0xc, 0x30, 0xc3, 0xc, 0x33, 0xf0,

    /* U+006D "m" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xc0,

    /* U+006E "n" */
    0xfb, 0xbc, 0xf3, 0xcf, 0x3c, 0xc0,

    /* U+006F "o" */
    0x3c, 0xdf, 0x1e, 0x3c, 0x7d, 0x9e, 0x0,

    /* U+0070 "p" */
    0xfb, 0xbc, 0xf3, 0xcf, 0x3f, 0xb0, 0xc3, 0x0,

    /* U+0071 "q" */
    0x7f, 0x3c, 0xf3, 0xcf, 0x77, 0xc3, 0xc, 0x30,

    /* U+0072 "r" */
    0xfb, 0xbc, 0xf0, 0xc3, 0xc, 0x0,

    /* U+0073 "s" */
    0x7b, 0xe, 0x1e, 0x18, 0x2f, 0x80,

    /* U+0074 "t" */
    0x30, 0xcf, 0xcc, 0x30, 0xc3, 0xc, 0x1c,

    /* U+0075 "u" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x77, 0xc0,

    /* U+0076 "v" */
    0xc2, 0x66, 0x66, 0x2c, 0x3c, 0x38, 0x18,

    /* U+0077 "w" */
    0xc3, 0xc2, 0xda, 0x5a, 0x7a, 0x6e, 0x66,

    /* U+0078 "x" */
    0x66, 0x6c, 0x3c, 0x18, 0x3c, 0x6c, 0x66,

    /* U+0079 "y" */
    0xc7, 0x8d, 0x13, 0x66, 0x85, 0xe, 0x18, 0x31,
    0xc0,

    /* U+007A "z" */
    0xfc, 0x71, 0x8c, 0x63, 0x8f, 0xc0,

    /* U+007B "{" */
    0x1c, 0xc3, 0xc, 0x30, 0xcc, 0xc, 0x30, 0xc3,
    0xc, 0x1c,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xf0,

    /* U+007D "}" */
    0xe0, 0xc3, 0xc, 0x30, 0xc0, 0xcc, 0x30, 0xc3,
    0xc, 0xe0,

    /* U+007E "~" */
    0x63, 0xae, 0x30
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 123, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 123, .box_w = 2, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 123, .box_w = 5, .box_h = 3, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 6, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 14, .adv_w = 123, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 25, .adv_w = 123, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 34, .adv_w = 123, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 44, .adv_w = 123, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 45, .adv_w = 123, .box_w = 5, .box_h = 13, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 54, .adv_w = 123, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 63, .adv_w = 123, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 68, .adv_w = 123, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 74, .adv_w = 123, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 77, .adv_w = 123, .box_w = 4, .box_h = 1, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 78, .adv_w = 123, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 123, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 89, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 123, .box_w = 2, .box_h = 7, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 123, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 170, .adv_w = 123, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 123, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 178, .adv_w = 123, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 123, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 123, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 204, .adv_w = 123, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 236, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 311, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 123, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 337, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 345, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 353, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 361, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 369, .adv_w = 123, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 123, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 123, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 123, .box_w = 4, .box_h = 13, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 418, .adv_w = 123, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 427, .adv_w = 123, .box_w = 4, .box_h = 13, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 434, .adv_w = 123, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 438, .adv_w = 123, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 439, .adv_w = 123, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 441, .adv_w = 123, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 447, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 455, .adv_w = 123, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 461, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 469, .adv_w = 123, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 476, .adv_w = 123, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 123, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 495, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 511, .adv_w = 123, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 521, .adv_w = 123, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 530, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 538, .adv_w = 123, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 123, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 550, .adv_w = 123, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 565, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 573, .adv_w = 123, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 579, .adv_w = 123, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 585, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 592, .adv_w = 123, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 598, .adv_w = 123, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 605, .adv_w = 123, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 612, .adv_w = 123, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 619, .adv_w = 123, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 628, .adv_w = 123, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 634, .adv_w = 123, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 644, .adv_w = 123, .box_w = 2, .box_h = 14, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 648, .adv_w = 123, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 658, .adv_w = 123, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_consola14 = {
#else
lv_font_t ui_font_consola14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 14,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_CONSOLA14*/

