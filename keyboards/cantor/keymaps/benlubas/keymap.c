#include QMK_KEYBOARD_H

#define _HOME 0
#define _NAV 1
#define _FN 2
#define _SYM 3
#define _GAME 4
#define _RGB 5
#define _MOUSE 6
#define _AUTO_MOUSE 7

layer_state_t layer_state_set_user(layer_state_t state) {
    uint16_t highest_layer = get_highest_layer(state);
    switch (highest_layer) {
    case _MOUSE:
    case _GAME:
    case _NAV:
    case _SYM:
      setPinInputLow(C13);
      break;
    default:
      setPinInputHigh(C13);
      break;
    }
    if (highest_layer == _GAME || highest_layer == _MOUSE) {
      combo_disable();
    } else {
      combo_enable();
    }
  return state;
}

// this is how I do it in ximi, but this ^ does the lights too
// bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
//     /* Disable combos on the game layer */
//     if (layer_state_is(_GAME)) {
//         return false;
//     }
//     return true;
// }

enum combos {
    JKLQUOTE_MOUSE,
    PQUOTE_DEL,
    QWER_GAME,
    XCVB_BOOT,
    RFTG_RESET,
    CLR_EPROM,
    L_SUPER,
    L_CTRL,
    L_ALT,
    R_SUPER,
    R_CTRL,
    R_ALT,
};

const uint16_t PROGMEM mouse_combo[] = {KC_J, KC_K, KC_L, KC_QUOT, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_P, KC_QUOT, COMBO_END};
const uint16_t PROGMEM gl_combo[] = {KC_Q, KC_W, KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM boot_combo[] = {KC_X, KC_C, KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM reset_combo[] = {KC_R, KC_T, KC_F, KC_G, COMBO_END};
const uint16_t PROGMEM eprom_combo[] = {KC_E, KC_D, KC_R, KC_F, COMBO_END};

// combo mods
const uint16_t PROGMEM lctrl_combo[] = {KC_F, KC_D, COMBO_END};
const uint16_t PROGMEM lsuper_combo[] = {KC_F, KC_S, COMBO_END};
const uint16_t PROGMEM lalt_combo[] = {KC_F, KC_A, COMBO_END};
const uint16_t PROGMEM rctrl_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM rsuper_combo[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM ralt_combo[] = {KC_J, KC_QUOT, COMBO_END};

combo_t key_combos[] = {
    [JKLQUOTE_MOUSE] = COMBO(mouse_combo, TO(_MOUSE)),
    [PQUOTE_DEL] = COMBO(del_combo, KC_DEL),
    [QWER_GAME] = COMBO(gl_combo, TO(_GAME)),
    [XCVB_BOOT] = COMBO(boot_combo, QK_BOOT),
    [RFTG_RESET] = COMBO(reset_combo, QK_RBT),
    [CLR_EPROM] = COMBO(eprom_combo, EE_CLR),
    [R_SUPER] = COMBO(rsuper_combo, OSM(MOD_RGUI)),
    [R_CTRL] = COMBO(rctrl_combo, OSM(MOD_RCTL)),
    [R_ALT] = COMBO(ralt_combo, OSM(MOD_RALT)),
    [L_SUPER] = COMBO(lsuper_combo, OSM(MOD_LGUI)),
    [L_CTRL] = COMBO(lctrl_combo, OSM(MOD_LCTL)),
    [L_ALT] = COMBO(lalt_combo, OSM(MOD_LALT)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    * ┌─────┬─────┬─────┬─────┬─────┐       ┌─────┬─────┬─────┬─────┬─────┐
    * │  Q  │  W  │  E  │  R  │  T  │       │  Y  │  U  │  I  │  O  │  P  │
    * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
    * │  A  │  S  │  D  │  F  │  G  │       │  H  │  J  │  K  │  L  │  '  │
    * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
    * │ Z/⇧ │  X  │  C  │  V  │  B  │       │  N  │  M  │  ,  │  .  │ENT/⇧│
    * └─────┴─────┴─────┴─────┴─────┘       └─────┴─────┴─────┴─────┴─────┘
    *   ┌─────┐    ┌─────┐                           ┌─────┐   ┌─────┐
    *   │Mute │    │ ESC ├─────┐               ┌─────┤ CAPS│   │Mute │
    *   └─────┘    └─────┤ NAV ├─────┐   ┌─────┤ SPC ├─────┘   └─────┘
    *                    └─────┤ REP │   │ SYM ├─────┘
    *                          └─────┘   └─────┘
    */
    [_HOME] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q,    KC_W,     KC_E,    KC_R,       KC_T,                         KC_Y, KC_U,    KC_I,    KC_O,    KC_P,        KC_BSPC,
        KC_LCTL, KC_A,    KC_S,     KC_D,    KC_F,       KC_G,                         KC_H, KC_J,    KC_K,    KC_L,    KC_QUOT,     KC_NO,
        KC_LSFT, MT(MOD_LSFT, KC_Z),KC_X,    KC_C,       KC_V,   KC_B,         KC_N,   KC_M, KC_COMM, KC_DOT,  MT(MOD_RSFT, KC_ENT), KC_RSFT,
                                  KC_ESC, OSL(_NAV), QK_REP,              OSL(_SYM),   KC_SPC,  CW_TOGG
    ),
    /*
    * ┌─────┬─────┬─────┬─────┬─────┐       ┌─────┬─────┬─────┬─────┬─────┐
    * │ TAB │  7  │  8  │  9  │  -  │       │ TAB←│     │     │ TAB→│ BSP │
    * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
    * │  0  │  4  │  5  │  6  │ ENTR│       │  ←  │  ↓  │  ↑  │  →  │ HOME│
    * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
    * │  .  │  1  │  2  │  3  │  +  │       │ FN  │ FN  │     │     │     │
    * └─────┴─────┴─────┴─────┴─────┘       └─────┴─────┴─────┴─────┴─────┘
    *    ┌─────┐    ┌─────┐                           ┌─────┐   ┌─────┐
    *    │Mute │    │ GUI ├─────┐               ┌─────┤ ALT │   │Mute │
    *    └─────┘    └─────┤ NAV ├─────┐   ┌─────┤ SPC ├─────┘   └─────┘
    *                     └─────┤ CTL │   │ SYM ├─────┘
    *                           └─────┘   └─────┘
    */

    [_NAV] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_TAB,   KC_7,    KC_8,    KC_9,    KC_MINUS,                           C(S(KC_TAB)), KC_TRNS, KC_TRNS, C(KC_TAB),KC_BSPC,  KC_TRNS,
        KC_LCTL, KC_0,     KC_4,    KC_5,    KC_6,    KC_ENT,                             KC_LEFT,   KC_DOWN,   KC_UP,   KC_RIGHT, TO(_HOME), KC_TRNS,
        KC_LSFT, MT(MOD_LSFT, KC_DOT),  KC_1,    KC_2,    KC_3,    S(KC_EQL),                             MO(_FN),   MO(_FN),   KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    /*
    * ┌─────┬─────┬─────┬─────┬─────┐       ┌─────┬─────┬─────┬─────┬─────┐
    * │ TAB │ F7  │ F8  │ F9  │     │       │ F11 │ F12 │ F13 │ F14 │ F15 │
    * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
    * │ F10 │ F4  │ F5  │ F6  │     │       │ F16 │ F17 │ F18 │ F19 │ F20 │
    * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
    * │     │ F1  │ F2  │ F3  │     │       │-----│-----│     │     │     │
    * └─────┴─────┴─────┴─────┴─────┘       └─────┴─────┴─────┴─────┴─────┘
    *    ┌─────┐    ┌─────┐                           ┌─────┐   ┌─────┐
    *    │Mute │    │ GUI ├─────┐               ┌─────┤ ALT │   │Mute │
    *    └─────┘    └─────┤ NAV ├─────┐   ┌─────┤ SPC ├─────┘   └─────┘
    *                     └─────┤ CTL │   │ SYM ├─────┘
    *                           └─────┘   └─────┘
    */
    [_FN] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_TAB,   KC_F7,    KC_F8,    KC_F9,    _______,                             KC_F11,    KC_F12,  KC_F13,     KC_F14,     KC_F15,     _______,
        _______, KC_F10,   KC_F4,    KC_F5,    KC_F6,    _______,                             KC_F16,    KC_F17,  KC_F18,     KC_F19,     KC_F20,     _______,
        KC_LSFT, KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    _______,                             _______,   _______, _______,    _______,    _______,    _______,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    /*
    * ┌─────┬─────┬─────┬─────┬─────┐       ┌─────┬─────┬─────┬─────┬─────┐
    * │  !  │  @  │  +  │  =  │  -  │       │  %  │  &  │  *  │  (  │  )  │
    * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
    * │  #  │  `  │  |  │  [  │  ]  │       │  }  │  {  │  :  │  ;  │  /  │
    * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
    * │     │  ~  │  \  │  $  │     │       │     │  _  │  ^  │  ?  │     │
    * └─────┴─────┴─────┴─────┴─────┘       └─────┴─────┴─────┴─────┴─────┘
    *    ┌─────┐    ┌─────┐                           ┌─────┐   ┌─────┐
    *    │Mute │    │ GUI ├─────┐               ┌─────┤ ALT │   │Mute │
    *    └─────┘    └─────┤ NAV ├─────┐   ┌─────┤ SPC ├─────┘   └─────┘
    *                     └─────┤ CTL │   │ SYM ├─────┘
    *                           └─────┘   └─────┘
    */

    [_SYM] = LAYOUT_split_3x6_3(
        KC_TRNS, S(KC_1),  S(KC_2),   S(KC_EQL),  KC_EQL,   KC_MINUS,                          S(KC_5),    S(KC_7),     S(KC_8),    S(KC_9),    S(KC_0), KC_TRNS,
        KC_LCTL, S(KC_3),  KC_GRAVE,  S(KC_BSLS), KC_LBRC,  KC_RBRC,                           S(KC_RBRC), S(KC_LBRC),  S(KC_SCLN), KC_SCLN,    KC_SLSH, KC_TRNS,
        KC_LSFT, KC_TRNS,  S(KC_GRV), KC_BSLS,    S(KC_4),  KC_TRNS,                           KC_TRNS,    S(KC_MINUS), S(KC_6),    S(KC_SLSH), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    /*
    * ┌─────┬─────┬─────┬─────┬─────┐
    * │ ESC │  Q  │  W  │  E  │  R  │
    * ├─────┼─────┼─────┼─────┼─────┤
    * │ SFT │  A  │  S  │  D  │  F  │
    * ├─────┼─────┼─────┼─────┼─────┤
    * │ CTL │  Z  │  X  │  C  │  V  │
    * └─────┴─────┴─────┴─────┴─────┘
    *    ┌─────┐    ┌─────┐
    *    │Mute │    │ GUI ├─────┐
    *    └─────┘    └─────┤ NAV ├─────┐
    *                     └─────┤ CTL │
    *                           └─────┘
    */
    [_GAME] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_ESC,  KC_Q, KC_W,  KC_E,   KC_R,                          KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_LCTL, KC_LSFT, KC_A, KC_S,   KC_D,  KC_F,                          KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_LSFT, KC_LCTL, KC_Z, KC_X,   KC_C,  KC_V,                          KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_LALT, KC_SPC, KC_G,              TO(_HOME),   TO(_HOME),  TO(_HOME)
    ),

    /*
    * ┌─────┬─────┬─────┬─────┬─────┐       ┌─────┬─────┬─────┬─────┬─────┐
    * │     │     │  📜 │     │     │       │     │  ↓  │  ↑  │     │     │
    * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
    * │     │ 🖱️1 │ 🖱️3 │ 🖱️2 │     │       │ 🖰 ← │ 🖰↓  │ 🖰↑  │ 🖰→  │ HOME│
    * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
    * │     │     │     │     │     │       │     │     │     │     │     │
    * └─────┴─────┴─────┴─────┴─────┘       └─────┴─────┴─────┴─────┴─────┘
    *    ┌─────┐    ┌─────┐                           ┌─────┐   ┌─────┐
    *    │Mute │    │ GUI ├─────┐               ┌─────┤ ALT │   │Mute │
    *    └─────┘    └─────┤ NAV ├─────┐   ┌─────┤ SPC ├─────┘   └─────┘
    *                     └─────┤ CTL │   │ SYM ├─────┘
    *                           └─────┘   └─────┘
    */

    [_MOUSE] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,           KC_TRNS,   KC_WH_U,   KC_WH_D, KC_TRNS,  KC_TRNS,    KC_TRNS,
        KC_LCTL, KC_TRNS,  KC_BTN1,    KC_BTN3,    KC_BTN2,    KC_TRNS,           KC_MS_L,   KC_MS_D,   KC_MS_U, KC_MS_R,  TO(_HOME), KC_TRNS,
        KC_LSFT, KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,           KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,
                                             KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS
  ),
};
