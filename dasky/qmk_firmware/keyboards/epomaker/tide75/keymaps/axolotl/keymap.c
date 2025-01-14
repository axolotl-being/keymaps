// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H



enum layers {
  _COLEMAK = 0,
  _QWERTY,
  _LOWER,
  _RAISE
};

enum keycodes {
  COLEMAK = QK_USER, //use saferange if disabling via
  QWERTY,
  ALT_TAB ,
  ALT_SHIFT_TAB
};

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

#define LOWER TT(_LOWER)
#define RAISE TT(_RAISE)
#define COPA LT(0,KC_NO)
#define BCKSPC LT(0,KC_BSPC)
#define RSLAYER TD(RAISE_SHIFT)
#define CTRLESC MT(MOD_LCTL, KC_ESC)


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_COLEMAK] = LAYOUT( /* Base */

        LGUI(KC_L),   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_BSLS,   QWERTY,  
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_DEL,   KC_HOME,  
        KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,     KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_LBRC,  KC_RBRC,  BCKSPC,  KC_END,    
        CTRLESC,     KC_A,     KC_R,     KC_S,     KC_T,     KC_G,     KC_M,     KC_N,     KC_E,     KC_I,     KC_O,     KC_QUOT,            KC_ENT,   KC_PGUP,          
          KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,OSL(_LOWER),   KC_K,     KC_H,     KC_COMM,  KC_DOT,   KC_SLSH,  RSLAYER,      KC_UP,    KC_PGDN,
          COPA,  KC_LALT,  OSM(MOD_LSFT),  KC_SPC,             KC_RALT,  KC_SPC,   KC_SPC,             LOWER,    RAISE,    KC_RGUI,  KC_LEFT,  KC_DOWN,  KC_RGHT
    ),
	
	[_QWERTY] = LAYOUT( /* Base */
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,   COLEMAK,  
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   BCKSPC,   KC_HOME,  
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_END,    
        KC_LCTL,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,     KC_QUOT,            KC_ENT,   KC_PGUP,          
       KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,    KC_PGDN,
        COPA,  KC_LGUI,  KC_LALT,  KC_SPC,             KC_RALT,  KC_SPC,   KC_SPC,             LOWER,    RAISE,    KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

	[_LOWER] = LAYOUT( 

        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_INS,  KC_MS_BTN1,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_F10,  KC_F11,  KC_F12,  _______,  _______,  _______,  _______,  _______,   
KC_PRINT_SCREEN,  _______,     KC_7,     KC_8,     KC_9,  _______,  _______,    KC_F7,    KC_F8,    KC_F9,   _______,   _______,   _______,   _______,  _______,  
        _______,  _______,     KC_4,     KC_5,     KC_6,  KC_MINS,   KC_EQL,    KC_F4,    KC_F5,    KC_F6,  _______,  _______,  _______,              _______, 
        _______,     KC_1,     KC_2,     KC_3,  _______,  _______,  _______,    KC_F1,    KC_F2,    KC_F3,  _______,  _______,            KC_MS_U,  KC_MS_BTN2,
        _______,  _______,  _______,     KC_0,             KC_0,  KC_0,   KC_0,             _______,  _______,  S(KC_INS),  KC_MS_L,  KC_MS_D,  KC_MS_R
    ),

	[_RAISE] = LAYOUT( 
        QK_BOOT,  KC_BT1,  KC_BT2,  KC_BT3,  KC_2G4,  KC_USB,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_INS,  KC_MS_BTN1,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   
        _______,  HS_BATQ,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  KC_UP,  _______,  _______,  _______,   _______,  _______,  
   KC_CAPS_LOCK,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_LEFT,  KC_RGHT,  _______,  _______,            _______,  _______, 
    KC_NUM_LOCK,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_DOWN,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,  _______,             _______,  _______,   _______,             _______,  _______,  _______,  _______,  _______,  _______
    )
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
	[_COLEMAK] = {ENCODER_CCW_CW(ALT_SHIFT_TAB, ALT_TAB)},
	[_QWERTY] = {ENCODER_CCW_CW(ALT_SHIFT_TAB, ALT_TAB)},
    [_LOWER] = {ENCODER_CCW_CW(KC_DOWN, KC_UP)},
    [_RAISE] = {ENCODER_CCW_CW(S(C(KC_TAB)), C(KC_TAB))}
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
/*    if (test_white_light_flag && record->event.pressed) {
        test_white_light_flag = false;
        rgb_matrix_set_color_all(0x00, 0x00, 0x00);
    }

    if (*md_getp_state() == MD_STATE_CONNECTED) {
        hs_rgb_blink_set_timer(timer_read32());
    }*/

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        rgblight_mode_noeeprom(2);
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        rgblight_reload_from_eeprom();
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    
  //tap backspace, hold is ctrl+bkspc
  case BCKSPC:
      if (!record->tap.count && record->event.pressed) {
          tap_code16(C(KC_BSPC)); // Intercept hold function to send CTRL-BKSPC
          return false;
      }
      return true;             // Return true for normal processing of tap keycode 
  //handle copy and paste on a single key
  case COPA:
      if (record->tap.count && record->event.pressed) {
          tap_code16(C(KC_C)); // Intercept tap function to send Ctrl-C
      } else if (record->event.pressed) {
          tap_code16(C(KC_V)); // Intercept hold function to send Ctrl-V
      }
      return false;

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