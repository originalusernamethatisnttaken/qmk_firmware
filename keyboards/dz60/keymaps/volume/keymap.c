#include QMK_KEYBOARD_H

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

#define ______ KC_TRNS


//Macros
enum custom_keycodes {
    M_BRENDAN = SAFE_RANGE,
	M_TPRIME,
	M_ANIME,
	M_ALEXJONES,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------------------------------------------------------.
   * | ` ~ |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |   Bkspc   |
   * |-----------------------------------------------------------------------------------------+
   * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
   * |-----------------------------------------------------------------------------------------+
   * | Caps    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
   * |-----------------------------------------------------------------------------------------+
   * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | RSh |  U  | DEL |
   * |-----------------------------------------------------------------------------------------+
   * | Ctrl |  Cmd  |  Alt  |              Space                | RAlt | FN  |  L  |  D  |  R  |
   * `-----------------------------------------------------------------------------------------'
   */

  LAYOUT_2_shifts(
      F(0), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, ______, KC_BSPC,
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
      KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
      KC_LSFT, ______, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_DEL,
      KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_SPC, KC_RALT, MO(1), KC_LEFT, KC_DOWN, KC_RIGHT
      ),

  /* FN Layer
   * ,-----------------------------------------------------------------------------------------.
   * | Esc |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |   RESET   |
   * |-----------------------------------------------------------------------------------------+
   * |       |RBB T|RGB M| Hue+| Hue-| Sat+| Sat-| Val+| Val-|     |PrintS|      |      |      |
   * |-----------------------------------------------------------------------------------------+
   * |       | BL T| BL M| BL+ | BL- |Bklight|     |     |     |     |     |     |             |
   * |-----------------------------------------------------------------------------------------+
   * |           |     |     |     |     |     |     |     |     |     |     |     | VolU| MUTE|
   * |-----------------------------------------------------------------------------------------+
   * |      |       |       |                                   |     |      |     | VolD|     |
   * `-----------------------------------------------------------------------------------------'
   */

  LAYOUT_directional(
      KC_GRV, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_F11, KC_F12, KC_TRNS, RESET,
      ______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, ______, KC_PSCR, ______, ______, ______,
      ______, BL_TOGG, BL_STEP, BL_INC, BL_DEC, BL_BRTG, ______, M_BRENDAN, M_ANIME, M_ALEXJONES, ______, ______,
      ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_VOLU, KC_MUTE,
      ______, M_TPRIME, ______, ______, ______, ______, ______, ______, ______, KC_VOLD, ______
      ),
};

enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        DDRB |= (1 << 2); PORTB &= ~(1 << 2);
    } else {
        DDRB &= ~(1 << 2); PORTB &= ~(1 << 2);
    }
}



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
			case M_BRENDAN:
				 SEND_STRING("https://osu.ppy.sh/beatmapsets/818313#osu/1715870");
				return false; break;
            case M_TPRIME:
                SEND_STRING("DID YOU KNOW YOU CAN USE YOUR AMAZON PRIME ACCOUNT TO SUB TO YOUR FAVORITE STREAMER ON TWITCH.TV? Oh! You may be asking, What's Twitch Prime? Let me tell ya! When you connect your Amazon account to your Twitch account, you can get 1 free sub to ANY streamer on Twitch, every month! Yup, and along with that, get yourself some Twitch loot! With Twitch loot, you can go ahead and get yourself some exclusive Twitch gear and your favorite games! So go ahead! Grab your Amazon account, grab a family or friend's Amazon Prime account, and link it to your Twitch account TODAY!"); 
                return false; break;
			case M_ANIME:
				SEND_STRING("Anime is trash and so am I!");
				return false; break;
				case M_ALEXJONES:
				SEND_STRING("The government puts chemicals in the water that makes the frogs gay.");
				return false; break;
		}		
    }
    return true;
};



