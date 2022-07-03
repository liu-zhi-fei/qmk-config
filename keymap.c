/* Copyright 2021 Shulin Huang <mumu@x-bows.com>
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
enum lzf_key {          // Make sure have the awesome keycode ready
    // {}  CURLY_BRACE
    LZF_CB= SAFE_RANGE ,
    // ()  PAREN
    LZF_PRN ,
    // <>  ANGLE_BRACKET
    LZF_ABK ,
    // :;  QUOTE
    LZF_QUOTE ,
    // [] BRACKET
    LZF_RC ,

};
uint8_t mod_state;

//bool l_m(keyrecord_t *record, uint16_t a, uint16_t b) {
//    mod_state = get_mods();
//    if (record->event.pressed) { // 按下时做些什么
//        if (mod_state & MOD_MASK_SHIFT) {
//            tap_code(b);
//        } else {
//            tap_code(a);
//        }
//    }
//    return false;
//}
//
//
//bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//    switch (keycode) {
//        case DE:
//            return l_m(record, KC_BACKSPACE, KC_ENTER); // 跳过此键的所有进一步处理
//        default:
//            return true; // 正常响应其他键码
//    }
//}


bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case LZF_CB:
        case LZF_PRN:
        case LZF_ABK:
        case LZF_QUOTE:
        case LZF_RC:
            return true;
        default:
            return false;
    }
}

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        // {}  CURLY_BRACE
        case LZF_CB:
            if (!shifted) {
                SEND_STRING("{");
            } else {
                SEND_STRING("}");
            }
            break;
        // ()  PAREN
        case LZF_PRN:
            if (!shifted) {
                SEND_STRING("(");
            } else {
                SEND_STRING(")");
            }
            break;
        // <>  ANGLE_BRACKET
        case LZF_ABK:
            if (!shifted) {
                SEND_STRING("<");
            } else {
                SEND_STRING(">");
            }
            break;
        // :;  QUOTE
        case LZF_QUOTE:
            if (!shifted) {
                SEND_STRING(":");
            } else {
                SEND_STRING(";");
            }
            break;
        // [] BRACKET
        case LZF_RC:
            if (!shifted) {
                SEND_STRING("[");
            } else {
                SEND_STRING("]");
            }
            break;
        default:
            if (shifted) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        // {}  CURLY_BRACE
//        case LZF_CB:
//            register_code16((!shifted) ? KC_LCBR : KC_RCBR);
//            break;
        // ()  PAREN
//        case LZF_PRN:
//            register_code16((!shifted) ? KC_LPRN : KC_RPRN);
//            break;
        // <>  ANGLE_BRACKET
//        case LZF_ABK:
//            register_code16((!shifted) ? KC_LT : KC_GT);
//            break;
        // :;  QUOTE
//        case LZF_QUOTE:
//            register_code16((!shifted) ? KC_COLN : KC_SEMICOLON);
//            break;
        // [] BRACKET
//        case LZF_RC:
//            register_code16((!shifted) ? KC_LBRC : KC_RBRC);
//            break;
        default:
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            // The IS_RETRO check isn't really necessary here, always using
            // keycode & 0xFF would be fine.
            unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

bool get_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#    ifndef NO_AUTO_SHIFT_ALPHA
        case KC_A ... KC_Z:
#    endif
#    ifndef NO_AUTO_SHIFT_NUMERIC
        case KC_1 ... KC_0:
#    endif
#    ifndef NO_AUTO_SHIFT_SPECIAL
        case KC_TAB:
        case KC_MINUS ... KC_SLASH:
        case KC_NONUS_BACKSLASH:
#    endif
            return true;
    }
    return get_custom_auto_shifted_key(keycode, record);
}

#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3
#define _LAYER4 4
#define _LAYER5 5

enum custom_keycodes {
    LAYER0 = SAFE_RANGE,
    LAYER1,
    LAYER2,
    LAYER3,
    LAYER4,
    LAYER5,
};

const uint16_t PROGMEM
keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap VANILLA: (Base Layer) Default Layer
 *
 * |---------------------------------------------------------------------------------------------------------------------------------|
 * | Esc |  F1  |  F2  |  F3  |  F4  |      F5  |  F6  |  F7  |  F8  |      F9  |  F10 |  F11 |  F12 |   Delete   |    Prtsc    |
 * |---------------------------------------------------------------------------------------------------------------------------------|
 * |  ~  |     1   |   2   |   3   |   4   |    5      |       6    |    7    |    8   |   9  |   0  |   -  |  =  |  Backspace  |
 * |---------------------------------------------------------------------------------------------------------------------------------|
 * | Tab |   Q    |    W   |   E  |   R  |   T  |            |    Y   |    U   |    I  |   O  |   P  |   [  |  ]  |   \  | PgUp |
 * |---------------------------------------------------------------------------------------------------------------------------------|
 * | Ctl |   A   |   S   |   D  |   F  |   G  |      Bksp      |    H  |    J   |   K  |   L  |   ;  |  '"  |    Enter   | PgDn |
 * |---------------------------------------------------------------------------------------------------------------------------------|
 * |Shift|   Z  |   X  |   C  |   V  |   B  |       Enter       |    N  |    M   |  ,  |   .  |  /?  | Shift|      |  Up |
 * |---------------------------------------------------------------------------------------------------------------------------------|
 * |Ctrl | GUI |     Alter   |    Space   |   Ctrl   |   Shift   |     Space     |    Alter   |  FN  | Ctrl | Lft  |  Dn |  Rig |
 * |---------------------------------------------------------------------------------------------------------------------------------|
 */
[_LAYER0] = LAYOUT(KC_CAPS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_HOME, KC_END, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_BSPC, KC_H, KC_J, KC_K, KC_L, KC_BSPC, KC_QUOT, KC_ENT, KC_PGDN, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_ENT, KC_N, KC_M, KC_COMM, KC_DOT, KC_ENT, KC_RSFT, KC_UP, KC_LCTL, KC_LALT, KC_RGUI, MO(1), LCTL_T(KC_F12), KC_LSFT, LT(2,KC_SPC), KC_RGUI, MO(5), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

[_LAYER1] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TAB, KC_GRV, KC_QUOT, LZF_PRN, LZF_ABK, KC_F16, KC_NO, KC_7, KC_8, KC_9, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_ESC, KC_MINS, KC_EQL, LZF_CB, LZF_RC, KC_BSLS, KC_BSPC, KC_NO, KC_4, KC_5, KC_6, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LSFT, LZF_QUOTE, KC_COMM, KC_DOT, KC_SLSH, KC_F17, KC_ENT, KC_NO, KC_1, KC_2, KC_3, KC_TRNS, KC_TRNS, KC_VOLU, KC_LCTL, KC_LALT, KC_LGUI, KC_TRNS, KC_LCTL, KC_RSFT, KC_0, KC_PDOT, KC_TRNS, KC_TRNS, KC_F14, KC_VOLD, KC_F15),

[_LAYER2] = LAYOUT(KC_CAPS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_HOME, KC_END, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_TAB, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_PGUP, KC_NO, KC_HOME, KC_NO, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_TRNS, KC_TRNS, KC_ENT, KC_PGDN, KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_ENT, KC_NO, KC_PGDN, KC_NO, KC_END, KC_TRNS, KC_RSFT, KC_UP, KC_LCTL, KC_LALT, KC_LGUI, KC_TRNS, KC_LCTL, KC_LSFT, KC_SPC, KC_RGUI, KC_NO, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

[_LAYER3] = LAYOUT(KC_CAPS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_HOME, KC_END, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_BSPC, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGDN, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_ENT, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_LCTL, KC_LALT, KC_LGUI, MO(2), KC_LCTL, KC_LSFT, KC_SPC, KC_RGUI, MO(1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

[_LAYER4] = LAYOUT(KC_CAPS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_HOME, KC_END, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_BSPC, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGDN, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_ENT, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_LCTL, KC_LALT, KC_LGUI, MO(2), KC_LCTL, KC_LSFT, KC_SPC, KC_RGUI, MO(1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

[_LAYER5] = LAYOUT(QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_CALC, KC_MYCM, KC_MSEL, KC_MAIL, NK_TOGG, EE_CLR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NUM, RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_TRNS, RGB_SPD, RGB_VAD, RGB_SPI, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_END, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_MUTE, KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_F14, KC_VOLD, KC_F15)

};
