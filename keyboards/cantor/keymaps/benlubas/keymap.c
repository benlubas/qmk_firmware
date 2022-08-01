
#include QMK_KEYBOARD_H


#define HOME_L 0
#define NAV_L 1
#define MOUSE_L 2
#define FN_L 3
#define SYM_L 4
#define GAME_L 5

enum custom_keycodes {
    HOMEESC = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case HOMEESC:
        if (record->event.pressed) {
          layer_clear();
          layer_on(HOME_L);
          tap_code16(KC_ESC);
        } else {
          // when it's released 
        }
        break; 
    }
    return true;
}; 

layer_state_t layer_state_set_user(layer_state_t state) {
    uint16_t highest_layer = get_highest_layer(state);
    switch (highest_layer) {
    case MOUSE_L:
    case GAME_L:
    case NAV_L:
      setPinInputLow(C13);
      break;
    default: 
      setPinInputHigh(C13);
      break;
    }
    if (highest_layer == GAME_L || highest_layer == MOUSE_L) { 
      combo_disable();
    } else {
      combo_enable();
    }
  return state;
}


const uint16_t PROGMEM esc_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM boot_combo[] = {KC_X, KC_C, KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_P, KC_QUOT, COMBO_END};
const uint16_t PROGMEM gl_combo[] = {KC_Q, KC_W, KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM mouse_combo[] = {KC_J, KC_K, KC_L, KC_QUOT, COMBO_END};
const uint16_t PROGMEM bkspc_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_S, KC_F, COMBO_END};
const uint16_t PROGMEM home_combo[] = {KC_E, KC_R, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
  COMBO(esc_combo, HOMEESC),
  COMBO(bkspc_combo, KC_BSPC), 
  COMBO(tab_combo, KC_TAB), 
  COMBO(home_combo, TO(HOME_L)),
  COMBO(mouse_combo, TO(MOUSE_L)), 
  COMBO(del_combo, KC_DEL),
  COMBO(gl_combo, TO(GAME_L)), 
  COMBO(boot_combo, QK_BOOT)
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
    *               ┌─────┐                           ┌─────┐
    *               │ GUI ├─────┐               ┌─────┤ ALT │
    *               └─────┤ NAV ├─────┐   ┌─────┤ SPC ├─────┘
    *                     └─────┤ CTL │   │ SYM ├─────┘
    *                           └─────┘   └─────┘
    */
  [0] = LAYOUT_split_3x6_3(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_NO,
    KC_LSFT, MT(MOD_LSFT, KC_Z),KC_X,   KC_C,    KC_V,    KC_B,                KC_N,   KC_M,  KC_COMM, KC_DOT,  MT(MOD_RSFT, KC_ENT), KC_RSFT,
                                        KC_LGUI, TO(NAV_L), KC_LCTL,          OSL(SYM_L), KC_SPC, KC_RALT
  ), 
   /*
    * ┌─────┬─────┬─────┬─────┬─────┐       ┌─────┬─────┬─────┬─────┬─────┐
    * │ TAB │  7  │  8  │  9  │  -  │       │ TAB←│     │     │ TAB→│ BSP │
    * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
    * │  0  │  4  │  5  │  6  │ ENTR│       │  ←  │  ↓  │  ↑  │  →  │ HOME│
    * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
    * │     │  1  │  2  │  3  │ ALT │       │ FN  │ FN  │     │     │     │
    * └─────┴─────┴─────┴─────┴─────┘       └─────┴─────┴─────┴─────┴─────┘
    *               ┌─────┐                           ┌─────┐
    *               │ GUI ├─────┐               ┌─────┤ ALT │
    *               └─────┤ NAV ├─────┐   ┌─────┤ SPC ├─────┘
    *                     └─────┤ CTL │   │ SYM ├─────┘
    *                           └─────┘   └─────┘
    */

  [1] = LAYOUT_split_3x6_3(
    KC_TAB,  KC_TAB,   KC_7,    KC_8,    KC_9,    KC_MINUS,                           C(S(KC_TAB)), KC_TRNS, KC_TRNS, C(KC_TAB),KC_BSPC, KC_TRNS,
    KC_LCTL, KC_0,     KC_4,    KC_5,    KC_6,    KC_ENT,                             KC_LEFT,   KC_DOWN,   KC_UP,   KC_RIGHT, TO(HOME_L), KC_TRNS,
    KC_LSFT, KC_TRNS,  KC_1,    KC_2,    KC_3,    KC_LALT,                             MO(FN_L),  MO(FN_L),  KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,
                                         KC_LGUI, TO(NAV_L), KC_LCTL,          OSL(SYM_L), KC_SPC, KC_RALT
  ), 
   /*
    * ┌─────┬─────┬─────┬─────┬─────┐       ┌─────┬─────┬─────┬─────┬─────┐
    * │     │     │     │     │     │       │     │  ↓  │  ↑  │     │     │
    * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
    * │     │ 🖱️1 │     │ 🖱️2 │     │       │ 🖰← │ 🖰↓  │ 🖰↑ │ 🖰→  │ HOME│
    * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
    * │     │     │     │     │     │       │     │     │     │     │     │
    * └─────┴─────┴─────┴─────┴─────┘       └─────┴─────┴─────┴─────┴─────┘
    *               ┌─────┐                           ┌─────┐
    *               │ GUI ├─────┐               ┌─────┤ ALT │
    *               └─────┤ NAV ├─────┐   ┌─────┤ SPC ├─────┘
    *                     └─────┤ CTL │   │ SYM ├─────┘
    *                           └─────┘   └─────┘
    */

  [2] = LAYOUT_split_3x6_3(
    KC_TAB,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                    KC_TRNS,   KC_WH_U,   KC_WH_D, KC_TRNS,  KC_TRNS,    KC_TRNS, 
    KC_LCTL, KC_TRNS,  KC_BTN1,    KC_BTN3,    KC_BTN2,    KC_TRNS,                    KC_MS_L,   KC_MS_D,   KC_MS_U, KC_MS_R,  TO(HOME_L), KC_TRNS,
    KC_LSFT, KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                    KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,
                                         KC_LGUI, TO(NAV_L), KC_LCTL,          OSL(SYM_L), KC_SPC, KC_RALT
  ), 
   /*
    * ┌─────┬─────┬─────┬─────┬─────┐       ┌─────┬─────┬─────┬─────┬─────┐
    * │ TAB │ F7  │ F8  │ F9  │  -  │       │ TAB←│     │     │ TAB→│ BSP │
    * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
    * │ F10 │ F4  │ F5  │ F6  │ ENTR│       │  ←  │  ↓  │  ↑  │  →  │ HOME│
    * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
    * │     │ F1  │ F2  │ F3  │     │       │     │     │     │     │     │
    * └─────┴─────┴─────┴─────┴─────┘       └─────┴─────┴─────┴─────┴─────┘
    *               ┌─────┐                           ┌─────┐
    *               │ GUI ├─────┐               ┌─────┤ ALT │
    *               └─────┤ NAV ├─────┐   ┌─────┤ SPC ├─────┘
    *                     └─────┤ CTL │   │ SYM ├─────┘
    *                           └─────┘   └─────┘
    */

  [3] = LAYOUT_split_3x6_3(
    KC_TAB,  KC_TAB,   KC_F7,    KC_F8,    KC_F9,    KC_MINUS,                           C(S(KC_TAB)), KC_TRNS, KC_TRNS, C(KC_TAB),KC_BSPC, KC_TRNS,
    KC_LCTL, KC_F10,   KC_F4,    KC_F5,    KC_F6,    KC_ENT,                             KC_LEFT,   KC_DOWN, KC_UP,   KC_RIGHT, TO(HOME_L), KC_TRNS,
    KC_LSFT, KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_TRNS,                            KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,
                                         KC_LGUI, TO(NAV_L), KC_LCTL,          OSL(SYM_L), KC_SPC, KC_RALT
  ), 
   /*
    * ┌─────┬─────┬─────┬─────┬─────┐       ┌─────┬─────┬─────┬─────┬─────┐
    * │  !  │  @  │  +  │  =  │  -  │       │  %  │  &  │  *  │  (  │  )  │
    * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
    * │  #  │  `  │  \  │  [  │  ]  │       │  }  │  {  │  :  │  ;  │  /  │
    * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
    * │     │  ~  │  |  │  $  │     │       │     │  _  │  ^  │  ?  │     │
    * └─────┴─────┴─────┴─────┴─────┘       └─────┴─────┴─────┴─────┴─────┘
    *               ┌─────┐                           ┌─────┐
    *               │ GUI ├─────┐               ┌─────┤ ALT │
    *               └─────┤ NAV ├─────┐   ┌─────┤ SPC ├─────┘
    *                     └─────┤ CTL │   │ SYM ├─────┘
    *                           └─────┘   └─────┘
    */

  [4] = LAYOUT_split_3x6_3(
    KC_TRNS, S(KC_1), S(KC_2), S(KC_EQL),  KC_EQL,   KC_MINUS,                           S(KC_5),    S(KC_7), S(KC_8), S(KC_9),  S(KC_0),  KC_TRNS,
    KC_LCTL, S(KC_3), KC_GRAVE, KC_BSLS,   KC_LBRC,    KC_RBRC,                          S(KC_RBRC), S(KC_LBRC), S(KC_SCLN), KC_SCLN,   KC_SLSH,    KC_TRNS,
    KC_LSFT, KC_TRNS,  S(KC_GRV), S(KC_BSLS),   S(KC_4),    KC_TRNS,                     KC_TRNS,    S(KC_MINUS), S(KC_6), S(KC_SLSH), KC_TRNS, KC_TRNS,
                                         KC_LGUI, TO(NAV_L), KC_LCTL,           OSL(SYM_L), KC_SPC, KC_RALT
  ),
   /*
    * ┌─────┬─────┬─────┬─────┬─────┐
    * │ ESC │  Q  │  W  │  E  │  R  │
    * ├─────┼─────┼─────┼─────┼─────┤
    * │ SFT │  A  │  S  │  D  │  F  │
    * ├─────┼─────┼─────┼─────┼─────┤
    * │ CTL │  Z  │  X  │  C  │  V  │
    * └─────┴─────┴─────┴─────┴─────┘
    *               ┌─────┐              
    *               │ TAB ├─────┐        
    *               └─────┤ SPC ├─────┐  
    *                     └─────┤ ALT │  
    *                           └─────┘  
    */
  [5] = LAYOUT_split_3x6_3(
    KC_TRNS, KC_ESC,  KC_Q, KC_W,  KC_E,   KC_R,                          TO(HOME_L), TO(HOME_L), TO(HOME_L), TO(HOME_L), TO(HOME_L), TO(HOME_L),
    KC_LCTL, KC_LSFT, KC_A, KC_S,   KC_D,  KC_F,                          TO(HOME_L), TO(HOME_L), TO(HOME_L), TO(HOME_L), TO(HOME_L), TO(HOME_L),
    KC_LSFT, KC_LCTL, KC_Z, KC_X,   KC_C,  KC_V,                          TO(HOME_L), TO(HOME_L), TO(HOME_L), TO(HOME_L), TO(HOME_L), TO(HOME_L),
                                        KC_TAB, KC_SPC, KC_LALT,      TO(HOME_L), TO(HOME_L), TO(HOME_L) 
  )
};