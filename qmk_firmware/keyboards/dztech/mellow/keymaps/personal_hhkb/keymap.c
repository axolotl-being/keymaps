/* Copyright 2024 DZTECH <moyi4681@Live.cn>
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
#include QMK_KEYBOARD_H

/*enum custom_keycodes{
  ALT_TAB = QK_USER_0,
  ALT_SHIFT_TAB
};*/

enum {
  RAISE_SHIFT
};


// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void altlp_finished(tap_dance_state_t *state, void *user_data);
void altlp_reset(tap_dance_state_t *state, void *user_data);


// keymap section --------------------------------------------------------------------------------------------------------------------------------

#define LOWER TT(2)
#define RAISE TT(3)
#define COPA LT(0,KC_NO)
#define BCKSPC LT(0,KC_BSPC)
#define RSLAYER TD(RAISE_SHIFT) //layer 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_hhkb(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, BCKSPC,
        KC_LCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,          KC_ENT,
        KC_Z,          KC_X,    KC_C,    KC_D,    KC_V,    LOWER,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, RSLAYER, LOWER,
                          KC_LALT, OSM(MOD_LSFT),                   KC_SPC,                             KC_RGUI, COPA
    ),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ \ │ ` │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ Bspc│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │ Ctrl │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│MO1│
     * └─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┘
     *       │Alt│ GUI │                           │ GUI │Alt│
     *       └───┴─────┴───────────────────────────┴─────┴───┘
     */
    [1] = LAYOUT_60_hhkb(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(2),
                          KC_LALT, KC_LGUI,                   KC_SPC,                             KC_RGUI, MO(3)
    ),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Pwr│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Ins│Del│
     * ├───┴─┬─┴───┴───┴───┴───┴───┴───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴───┘
     * │Caps │ Q │ W │ E │ R │ T │ Y │ U │PSc│Scr│Pse│ ↑ │ ] │ Bspc│
     * └─────┘┌───┬───┬───┐──┴┬──┴┌───┬──┴┬──┴┬──┴┬──┴┬──┴┬────────┐
     * │ Ctrl │Vl-│Vl+│Mut│ F │ G │ * │ / │Hom│PgU│ ← │ → │  Enter │
     * ├──────└───┴───┴───┘─┬─┴─┬─└─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┘
     * │ Shift  │ Z │ X │ C │ V │ B │ + │ - │End│PgD│ ↓ │ Shift│MO1│
     * └─────┬──┴┬──┴──┬┴───┴───┴───└───┴───┴───┴───┴───┘┬───┬─┴───┘
     *       │Alt│ GUI │                           │ GUI │Alt│
     *       └───┴─────┴───────────────────────────┴─────┴───┘
     */
    [2] = LAYOUT_60_hhkb(
        KC_GRV,  _______,   _______,   _______,   _______,   _______, _______,   KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,  KC_INS,  KC_DEL,
        KC_CAPS, _______,      KC_7,      KC_8,      KC_9,  _______, _______,   KC_F7,     KC_F8,   KC_F9, _______, MS_UP,   MS_BTN1, MS_BTN2,
        KC_PSCR, _______,      KC_4,      KC_5,      KC_6,  KC_MINS,  KC_EQL,   KC_F4,     KC_F5,   KC_F6, MS_LEFT, MS_RGHT,          KC_PENT,
        KC_NUM,           KC_1,    KC_2,    KC_3,   _______,    _______,  _______,   KC_F1, KC_F2,  KC_F3, MS_DOWN, _______, _______,
                          _______, _______,                    KC_0,                            _______, _______
    ),

    [3] = LAYOUT_60_hhkb(
        QK_BOOT,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
        _______, _______, _______, KC_INS, KC_HOME, KC_PGUP, _______, _______, _______, _______, KC_UP, _______,   _______, _______,
        _______, _______, KC_DEL, KC_END, KC_PGDN, KC_PMNS, KC_PPLS, _______, _______, KC_LEFT, KC_RGHT, _______,          KC_PENT,
        _______,   _______, _______, _______, _______, _______, _______, _______, _______,  KC_DOWN, _______, _______, _______,
                          _______, _______,                   _______,                            _______, _______
    )
};

// custom tap dance code here ---------------------------------------------------------------------------------------------------------------------------

// Determine the tapdance state to return
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) {
      if (state->pressed) return TD_DOUBLE_HOLD;
      else return TD_DOUBLE_TAP;
    }
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above

}

// Handle the possible states for each tapdance keycode you define:

void altlp_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            set_oneshot_layer(3, ONESHOT_START);
            break;
        case TD_SINGLE_HOLD:
            layer_on(3); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_TAP: // 
            set_oneshot_mods(MOD_BIT(KC_RSFT));
            break;
        case TD_DOUBLE_HOLD: //
            register_mods(MOD_BIT(KC_RSFT));
            break;
        default:
            break;
    }
}

void altlp_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case TD_SINGLE_HOLD:
            layer_off(3); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_TAP:
            
            break;
        case TD_DOUBLE_HOLD:
            unregister_mods(MOD_BIT(KC_RSFT));
            break;
        default:
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
tap_dance_action_t tap_dance_actions[] = {
    [RAISE_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altlp_finished, altlp_reset)
};

//---------------------------------------------------------------------------------------------------------------------

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

  //tap backspace, hold is ctrl+bkspc
  case BCKSPC:
      if (!record->tap.count && record->event.pressed) {
          tap_code16(C(KC_BSPC)); // Intercept hold function to send CTRL-BKSPC
          return false;
      }
      return true;             // Return true for normal processing of tap keycode
      break; 
  //handle copy and paste on a single key
  case COPA:
      if (record->tap.count && record->event.pressed) {
          tap_code16(C(KC_C)); // Intercept tap function to send Ctrl-C
      } else if (record->event.pressed) {
          tap_code16(C(KC_V)); // Intercept hold function to send Ctrl-V
      }
      return false;
      break;

/*    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
case ALT_SHIFT_TAB:
      if (record->event.pressed) {
        if (!is_alt_shift_tab_active) {
          is_alt_shift_tab_active = true;
          register_code(KC_LALT);
          
        }
        alt_tab_timer = timer_read();
        register_code(KC_LSFT);
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
        unregister_code(KC_LSFT);
      }
      break; */
  }
  return true;
}