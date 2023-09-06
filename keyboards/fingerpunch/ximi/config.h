/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "keyboards/fingerpunch/src/config.h"

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

// For shift register (and optionally trackball)
#define SPI_SCK_PIN GP22
#define SPI_MOSI_PIN GP23
#define SPI_MISO_PIN GP20

// wiring of each half
#define MATRIX_ROW_PINS { GP29, GP28, GP27, GP24 }
#define MATRIX_COL_PINS { GP10, GP11, GP26, GP12, GP13, GP14, GP15, GP16 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A { GP7 }
#define ENCODERS_PAD_B { GP8 }

// Got help from https://www.eisbahn.jp/yoichiro/2022/08/luankey_pico_qmk_firmware.html
#define MASTER_LEFT
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_POINTING_ENABLE
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_HAPTIC_ENABLE
#define SERIAL_PIO_USE_PIO1
#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN GP0     // USART TX pin
#define SERIAL_USART_RX_PIN GP1     // USART RX pin

#define RGB_DI_PIN GP25
#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_SPLIT
    #define RGBLED_SPLIT { 21, 21 }
    #define RGBLED_NUM 42
    #define RGBLIGHT_HUE_STEP 16
    #define RGBLIGHT_SAT_STEP 16
    #define RGBLIGHT_VAL_STEP 16
    #define RGBLIGHT_LIMIT_VAL 130 /* The maximum brightness level for RGBLIGHT_ENABLE */
    #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
    #define RGBLIGHT_EFFECT_ALTERNATING
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_CHRISTMAS
    #define RGBLIGHT_EFFECT_KNIGHT
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_SNAKE
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_TWINKLE
#endif

#ifdef RGB_MATRIX_ENABLE
    #define SPLIT_TRANSPORT_MIRROR
    #define RGB_MATRIX_LED_COUNT 36 // Number of LEDs
    #define RGB_MATRIX_SPLIT { 18, 18 }
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 130
    #define RGB_MATRIX_STARTUP_HUE 35
    #define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #define RGB_DISABLE_WHEN_USB_SUSPENDED
    #define RGB_MATRIX_KEYPRESSES
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGB_MATRIX_KEYREACTIVE_ENABLED
    #define ENABLE_RGB_MATRIX_ALPHAS_MODS
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#ifdef AUDIO_ENABLE
    #define AUDIO_VOICES
    #define AUDIO_PIN GP18
    #define AUDIO_PWM_DRIVER PWMD1
    #define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_A
    #define AUDIO_ENABLE_TONE_MULTIPLEXING
    #define AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT 10
    #define FP_AUDIO_MOUSE_BUTTONS
    #define FP_AUDIO_CUT_COPY_PASTE
    #define FP_AUDIO_SAVE
    #define FP_STARTUP_FLOW_DOWN WHOLE_NOTE(_E6), HALF_NOTE(_REST), HALF_NOTE(_C6), WHOLE_NOTE(_G5), HALF_NOTE(_A5), WHOLE_NOTE(_D5), WHOLE_NOTE(_E5), WHOLE_NOTE(_C5),
    #define STARTUP_SONG SONG(FP_STARTUP_FLOW_DOWN)
    #define DEFAULT_LAYER_SONGS \
        { SONG(QWERTY_SOUND), SONG(COLEMAK_SOUND) }
#endif

#ifdef HAPTIC_ENABLE
    #define FB_ERM_LRA 1
    #define FB_BRAKEFACTOR 3 // For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7
    #define FB_LOOPGAIN 1 // For  Low:0, Medium:1, High:2, Very High:3
    #define RATED_VOLTAGE 2
    #define V_PEAK 2.8
    #define V_RMS 2.0
    #define F_LRA 150 // resonance freq
    #define DRV_GREETING  alert_750ms
    #define FP_HAPTIC_MOUSE_BUTTONS
    #define FP_HAPTIC_CUT_COPY_PASTE
    #define FP_HAPTIC_SAVE
#endif

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#ifdef CIRQUE_ENABLE
    // cirque trackpad config
    #define CIRQUE_PINNACLE_ADDR 0x2A
    // Uncomment 2 lines below to switch to relative mode and enable right click
    // Note that tap to click doesn't work on the slave side unless you enable relative mode
    // #define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_RELATIVE_MODE
    // #define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE
    #define CIRQUE_PINNACLE_TAP_ENABLE
    #define POINTING_DEVICE_TASK_THROTTLE_MS 5
#endif

#ifdef FP_TRACKBALL_ENABLE
    // Trackball config
    #define PMW33XX_CS_PIN GP9
    #define PMW33XX_CPI 1000
    #define PMW33XX_CS_DIVISOR 8

    /* SPI config for pmw3360 sensor. */
    #define SPI_DRIVER SPID0
    // #define SPI_SCK_PAL_MODE 5 // already defined in chibios
    // #define SPI_MOSI_PAL_MODE 5 // already defined in chibios
    // #define SPI_MISO_PAL_MODE 5 // already defined in chibios
#endif

// All the possible configurations of pointing devices
#if defined(FP_TRACKBALL_BOTH)
    #define POINTING_DEVICE_COMBINED            // two pointing devices
    #define POINTING_DEVICE_INVERT_Y            // for trackball on the left
    #define POINTING_DEVICE_INVERT_X_RIGHT      // for trackball on the right
#endif
#if defined(FP_CIRQUE_BOTH)
    #define POINTING_DEVICE_COMBINED            // two pointing devices
    #define POINTING_DEVICE_ROTATION_90         // for cirque on the left
    #define POINTING_DEVICE_ROTATION_90_RIGHT   // for cirque on the right
#endif
#if defined(FP_TRACKBALL_LEFT_ONLY)
    #define POINTING_DEVICE_LEFT                // one pointing device, on the left
    #define POINTING_DEVICE_INVERT_Y            // for trackball on the left
#endif
#if defined(FP_TRACKBALL_RIGHT_ONLY)
    #define POINTING_DEVICE_RIGHT               // one pointing device, on the right
    #define POINTING_DEVICE_INVERT_X_RIGHT      // for trackball on the right
#endif
#if defined(FP_CIRQUE_LEFT_ONLY)
    #define POINTING_DEVICE_LEFT                // one pointing device, on the left
    #define POINTING_DEVICE_ROTATION_90         // for cirque on the left
#endif
#if defined(FP_CIRQUE_RIGHT_ONLY)
    #define POINTING_DEVICE_RIGHT               // one pointing device, on the right
    #define POINTING_DEVICE_ROTATION_90_RIGHT   // for cirque on the right
#endif
#if defined(FP_TRACKBALL_LEFT_CIRQUE_RIGHT)
    #define POINTING_DEVICE_COMBINED            // two pointing devices
    #define POINTING_DEVICE_INVERT_Y            // for trackball on the left
    #define POINTING_DEVICE_ROTATION_90_RIGHT   // for cirque on the right

#endif
#if defined(FP_CIRQUE_LEFT_TRACKBALL_RIGHT)
    #define POINTING_DEVICE_COMBINED            // two pointing devices
    #define POINTING_DEVICE_ROTATION_90         // for cirque on the left
    #define POINTING_DEVICE_INVERT_X_RIGHT      // for trackball on the right
#endif
