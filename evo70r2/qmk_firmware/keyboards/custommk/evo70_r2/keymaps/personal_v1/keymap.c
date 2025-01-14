// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


enum custom_keycodes{
  ALT_TAB = QK_USER_0,
  ALT_SHIFT_TAB
};

enum td_keycodes{
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
#define RSLAYER TD(RAISE_SHIFT)
#define CTRLESC MT(MOD_LCTL, KC_ESC)


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //colemak-dh
    [0] = LAYOUT( /* Base */

     _______,         KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_DEL,     KC_HOME,  
                    KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,     KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_LBRC,  KC_RBRC,  BCKSPC,      KC_END,    
 KC_INS, KC_LCTL,   CTRLESC,   KC_A,     KC_R,     KC_S,     KC_T,     KC_G,     KC_M,     KC_N,     KC_E,     KC_I,     KC_O,     KC_QUOT,            KC_ENT,      KC_PGUP,          
  KC_F5,  KC_F12,      KC_Z, _______,   KC_X,     KC_C,     KC_D,     KC_V,OSL(2),   KC_K,     KC_H,     KC_COMM,  KC_DOT,   KC_SLSH,  RSLAYER,              KC_UP,     KC_PGDN,
  TG(1),  OSM(MOD_LGUI),      COPA,  KC_LALT,  OSM(MOD_LSFT),                              KC_SPC,                    LOWER,    RAISE,              KC_LEFT,  KC_DOWN,  KC_RGHT
    ),
	//qwerty
	[1] = LAYOUT( /* Base */
   
    _______,          KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   BCKSPC,   KC_HOME,  
                    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_END,    
KC_F1,KC_F2,     KC_LCTL,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_PGUP,          
KC_F3,KC_F4,       KC_LSFT,_______,   KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,    KC_PGDN,
_______,KC_F5,        COPA,   KC_LGUI,  KC_LALT,                                 KC_SPC,                         LOWER,    RAISE,              KC_LEFT,  KC_DOWN,  KC_RGHT
    ),
    //lower
	[2] = LAYOUT( 

    _______,                   KC_GRV,    _______,  _______,  _______,  _______,  _______,  _______,  KC_F10,  KC_F11,  KC_F12,  _______,  _______,  _______,  KC_INS,  _______,   
                        KC_PRINT_SCREEN,_______,     KC_7,     KC_8,     KC_9,  _______,  _______,    KC_F7,    KC_F8,    KC_F9,   _______,  _______,   _______,   KC_BSLS,  _______,  
KC_MS_BTN1,KC_MS_BTN2,        _______,  _______,     KC_4,     KC_5,     KC_6,  KC_MINS,   KC_EQL,    KC_F4,    KC_F5,    KC_F6,  _______,   _______,  C(S(KC_C)),              _______, 
_______,_______,          _______,_______,      KC_1,     KC_2,     KC_3,  _______,  _______,  _______,    KC_F1,    KC_F2,    KC_F3,  _______,  S(KC_INS),            KC_MS_U,  _______,
_______,_______,                 _______,  _______,  _______,                                     KC_0,                     _______,  _______,              KC_MS_L,  KC_MS_D,  KC_MS_R
    ),
    //raise
	[3] = LAYOUT( 

 _______,            _______,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,  KC_F11,  KC_F12,  _______,  _______,   
                   _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  KC_UP,  _______,  _______,  _______,   _______,  _______,  
_______,_______,   KC_CAPS_LOCK,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_LEFT,  KC_RGHT,  _______,  _______,            _______,  _______, 
_______,_______,    KC_NUM_LOCK,_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_DOWN,  _______,  _______,  _______,            _______,  _______,
_______,_______,        QK_BOOT,  _______,  _______,                            _______,                         _______,  _______,              _______,  _______,  _______
    ),
};



#ifdef ENCODER_MAP_ENABLE //------------------------------------------------------------------------------------------------------------------------------

bool is_alt_tab_active = false; // ADD this near the begining of keymap.c
bool is_alt_shift_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.

//ALT TAB Encoder Timer
void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 900) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
}
  if (is_alt_shift_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 900) {
      unregister_code(KC_LALT);
      unregister_code(KC_LSFT);
      is_alt_shift_tab_active = false;
    }
  }
};


 const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
	[0] = {ENCODER_CCW_CW(ALT_SHIFT_TAB, ALT_TAB)},
	[1] = {ENCODER_CCW_CW(ALT_SHIFT_TAB, ALT_TAB)},
    [2] = {ENCODER_CCW_CW(KC_DOWN, KC_UP)},
    [3] = {ENCODER_CCW_CW(S(C(KC_TAB)), C(KC_TAB))}
}; 
#endif

// clang-format on

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
            //tap_code16(KC_CAPS_LOCK);
            break;
        case TD_DOUBLE_HOLD: //
            //register_mods(MOD_BIT(KC_RSFT));
            tap_code16(KC_CAPS_LOCK);
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
            //unregister_mods(MOD_BIT(KC_RSFT));
          //unregister_code(KC_CAPS_LOCK);
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

    case ALT_TAB:
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
      break; 
  }
  return true;
}