/* Copyright 2022 imchipwood && deveth0
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {{// Key Matrix to LED Index
                              {0, 1, 2},
                              {3, 4, 5,}},
                             {// LED Index to Physical Position
                              {0, 0},
                              {75, 0},
                              {149, 0},

                              {224, 0},
                              {224, 21},
                              {149, 21}},
                             {// LED Index to Flag
                              4, 4, 4, 4, 4, 4}};
#endif

void keyboard_pre_init_kb(void) {
    // Set LED IO as outputs
    // setPinOutput(LED_00);

    // Set the encoder A pin (B2) to input with pull-up resistor
//    DDRB &= ~(1<<2);
//    PORTB &= ~(1<<2);
//
//    // Set the encoder B pin (D4) to input with pull-up resistor
//    DDRD &= ~(1<<4);
//    PORTD &= ~(1<<4);  // disable the pull up for testing

    keyboard_pre_init_user();
}

void shutdown_user(void) {
    // Shutdown LEDs
    // writePinLow(LED_00);
}

// layer_state_t layer_state_set_kb(layer_state_t state) {
//     // Layer LEDs act as binary indication of current layer
//     uint8_t layer = get_highest_layer(state);
//     writePin(LED_00, layer & 0b1);
//     writePin(LED_01, (layer >> 1) & 0b1);
//     uprintf("%d string", layer);
//     return layer_state_set_user(state);
// }

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    // uint8_t led_delay_ms = 80;
    // for (int i = 0; i < 2; i++) {
    //     writePinHigh(LED_00);
    //     wait_ms(led_delay_ms);
    //     writePinLow(LED_00);
    //     if (i < 1) {
    //         wait_ms(led_delay_ms);
    //     }
    // }

    matrix_init_user();
}

void keyboard_post_init_user(void) {
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
}

// bool led_update_kb(led_t led_state) {
//     if (!led_update_user(led_state)) return false;
//     // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
//     writePin(LED_01, !led_state.num_lock);
//     return true;
// }
bool encoder_update_kb(uint8_t index, bool clockwise) {
    uprintf("Encoder time!\n");
    if (!encoder_update_user(index, clockwise)) {
        uprintf("returning \n");
        return false; /* Don't process further events if user function exists and returns false */
    }
    if (index == 0) { /* First encoder */
        if (clockwise) {
            // tap_code(KC_VOLU);
            uprintf("Encoder CW\n");
            tap_code(KC_SLSH);
        } else {
            // tap_code(KC_VOLD);
            uprintf("Encoder CCW\n");
            tap_code(KC_BSLS);
        }
    } else if (index == 1) { /* Second encoder */
	    // ignore this
        // if (clockwise) {
        //     // tap_code(KC_VOLU);
        //     uprintf("Encoder CW\n");
        //     tap_code(KC_SLSH);
        // } else {
        //     // tap_code(KC_VOLD);
        //     uprintf("Encoder CCW\n");
        //     tap_code(KC_BSLS);
        // }
	
    }
    return true;
}
