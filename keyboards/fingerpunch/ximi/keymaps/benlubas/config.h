#define NO_ALT_REPEAT_KEY

#define COMBO_ONLY_FROM_LAYER 0
#define COMBO_COUNT 10

#define COMBO_TERM 30        // how quickly all combo keys must be pressed in succession to trigger
#define COMBO_MUST_HOLD_MODS // if a combo triggers a modifier, only trigger when the combo is held
#define COMBO_HOLD_TERM 150  // how long at least one of the combo keys must be held to trigger
#define TAPPING_TERM 200

#define HOLD_ON_OTHER_KEY_PRESS

#define FP_ENC_1_LAYER_VOLUME         0
#define FP_ENC_1_LAYER_DPI_POINTING   1
#define FP_ENC_1_LAYER_SUPER_TAB      4
#define FP_ENC_1_LAYER_PGUP_PGDN      6
#define FP_ENC_1_LAYER_ZOOM           3
#define FP_ENC_1_LAYER_SUPER_CTRL_TAB 5
#define FP_ENC_1_LAYER_SCROLL_WHEEL   2
#define FP_ENC_1_LAYER_RGB_MODE       7
#define FP_ENC_1_LAYER_RGB_HUE        8
#define FP_ENC_1_LAYER_RGB_SAT        9
#define FP_ENC_1_LAYER_RGB_VAL        10
#define ENCODERS_B_REVERSE


#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define FP_AUTO_MOUSE_TRACKBALL_SENSITIVITY 1
#define AUTO_MOUSE_DEFAULT_LAYER 7
#define AUTO_MOUSE_TIME 800 // default 650

#define POINTING_DEVICE_INVERT_X
#define FP_POINTING_SCROLLING_DPI 1 // can't go lower than 1 (100 dpi)
#define FP_POINTING_DEFAULT_DPI 8 // default 10

// higher = slower scrolling
#define SCROLL_DIVISOR_H 10.0
#define SCROLL_DIVISOR_V 10.0
