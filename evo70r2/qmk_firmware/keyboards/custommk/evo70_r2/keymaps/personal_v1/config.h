#define ONESHOT_TAP_TOGGLE 3  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */

#define FORCE_NKRO

#define TAPPING_TOGGLE 3

#define DEBOUNCE 5
//#define DYNAMIC_KEYMAP_LAYER_COUNT 4 //max amount for this keyboard
//#define ENCODER_RESOLUTION 2

//#define RGBLIGHT_DEFAULT_MODE 37
#ifdef AUDIO_ENABLE
#define AUDIO_INIT_DELAY
#define STARTUP_SONG SONG(MEGALOVANIA)
#endif