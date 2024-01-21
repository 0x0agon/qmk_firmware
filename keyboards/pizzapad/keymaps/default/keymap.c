/*
Copyright 2022 imchipwood && deveth0

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

#include QMK_KEYBOARD_H
#include "print.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
            BASE LAYER - Num Pad
    /-------------------------------------------`
    |             |    1    |    2    |    3    |
    |             |---------|---------|---------|
    |             |    4    |    5    |   TT1   |
    \-------------------------------------------'
    */
    [0] = LAYOUT(
                    KC_P1,      KC_P2,    KC_P3,
                    KC_P4,      KC_P5,    TO(1)
    ),
    /*
            SUB LAYER  - RGB controls, Modes on encoder
    /-------------------------------------------`
    |             | On/Off  | Bright- | Bright+ |
    |             |---------|---------|---------|
    |             | Hue-    | Hue+    |  TT0    |
    \-------------------------------------------'
    */
    [1] = LAYOUT(
                    RGB_TOG,    RGB_VAD,     RGB_VAI,
                    RGB_HUD,     RGB_HUI,    TO(0)
                    // KC_P6,      KC_P7,    KC_P8,
                    // KC_P9,      KC_P0,    TO(0)
    ),
};
// clang-format on

bool encoder_update_user(uint8_t index, bool clockwise) {
    uprintf("hi there!\n");
    uprintf("rotation is clockwise? %b", clockwise);
    switch (get_highest_layer(layer_state)) {
        case 0:
            uprintf("case 0");
            // main layer, volume
            if (clockwise) {
                // tap_code(KC_VOLU);
//                uprintf("Encoder CW\n");
                tap_code(KC_SLSH);
            } else {
                // tap_code(KC_VOLD);
//                uprintf("Encoder CCW\n");
                tap_code(KC_BSLS);
            }
            break;
        case 1:
            uprintf("case 1");
            // main layer, volume
            if (clockwise) {
                // tap_code(KC_VOLU);
//                uprintf("Encoder CW\n");
                rgblight_increase_hue();

            } else {
                // tap_code(KC_VOLD);
//                uprintf("Encoder CCW\n");
                rgblight_decrease_hue();
            }
            break;
        default:
            uprintf("case default");
            // rgb control layer, effects
            if (clockwise) {
//                rgblight_step();
//                uprintf("Encoder CW\n");
                tap_code(KC_SLSH);
            } else {
//                rgblight_step_reverse();
//                uprintf("Encoder CCW\n");
                tap_code(KC_BSLS);
            }
            break;
    }
    return false;
}
