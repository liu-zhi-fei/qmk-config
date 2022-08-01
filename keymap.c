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
uint8_t mod_state;
uint8_t shifted;
#include <string.h>
#include QMK_KEYBOARD_H
#define l_m(r,b,a)  mod_state = get_mods(); shifted = (mod_state & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))) ? true : false; del_mods(MOD_MASK_SHIFT); if (record->event.pressed) { if (shifted) {SEND_STRING(a);} else {SEND_STRING(b);}}set_mods(mod_state);
// 先判断shifted状态 禁用shift 发送ab 还原当前mod state

enum lzf_key {          // Make sure have the awesome keycode ready
    // {}
    LZF_1= SAFE_RANGE ,
    // ()
    LZF_2 ,
    // <>
    LZF_3 ,
    // :;
    LZF_4 ,
    // []
    LZF_5 ,
    // ./
    LZF_6 ,
    // ,?
    LZF_7,
    LZF_8,
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LZF_1:
            l_m(record, "{", "}");
            return false;
        case LZF_2:
            l_m(record, "(", ")");
            return false;
        case LZF_3:
            l_m(record, "<", ">");
            return false;
        case LZF_4:
            l_m(record, ":", ";");
            return false;
        case LZF_5:
            l_m(record, "[", "]");
            return false;
        case LZF_6:
            l_m(record, ".", "/");
            return false;
        case LZF_7:
            l_m(record, ",", "?");
            return false;
        case LZF_8:
            if (record->event.pressed){
                layer_on(1);
            }
            return false;
        default:
            return true; // 正常响应其他键码
    }
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
[_LAYER0] = LAYOUT(
        KC_CAPS, KC_F1  ,   KC_F2  , KC_F3,   KC_F4         , KC_F5  ,                        KC_F6,   KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_HOME, KC_END,
        KC_GRV , KC_1   ,   KC_2   , KC_3 ,   KC_4          , KC_5   ,                        KC_6 ,   KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC,
        KC_TAB , KC_Q   ,   KC_W   , KC_E ,   KC_R          , KC_T   ,                        KC_Y ,   KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_ESC , KC_A   ,   KC_S   , KC_D ,   KC_F          , KC_G   , KC_BSPC,               KC_H ,   KC_J   , KC_K   , KC_L   , KC_BSPC, KC_QUOT, KC_ENT , KC_PGDN,
        KC_LSFT, KC_Z   ,   KC_X   , KC_C ,   KC_V          , KC_B   , KC_ENT,                KC_N ,   KC_M   , LZF_7  , LZF_6  , KC_ENT , KC_RSFT, KC_UP  ,
        KC_LCTL, KC_LALT,   KC_LGUI, MO(1),   LCTL_T(KC_F12), KC_LSFT, LT(2,KC_SPC), KC_RGUI, MO(4),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

[_LAYER1] = LAYOUT(
        KC_TRNS, KC_TRNS  , KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS  , KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TAB , KC_GRV   , KC_QUOT, LZF_2  , LZF_3  ,        KC_F16 ,                        KC_NO  , KC_7   , KC_8   , KC_9   , KC_NO  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_ESC , KC_MINS  , KC_EQL , LZF_1  , LZF_5  ,        KC_BSLS, KC_BSPC,               KC_NO  , KC_4   , KC_5   , KC_6   , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_LSFT, KC_LSFT  , KC_MINS, LZF_4  , KC_BSLS,        KC_F17 , KC_ENT ,               KC_NO  , KC_1   , KC_2   , KC_3   , KC_TRNS, KC_TRNS, KC_VOLU,
        KC_LCTL, KC_LALT  , KC_LGUI, KC_TRNS, LCTL_T(KC_F12), KC_LSFT, KC_0   , KC_PDOT,      KC_TRNS, KC_TRNS, KC_F14 , KC_VOLD, KC_F15
    ),

[_LAYER2] = LAYOUT(
        KC_TRNS, KC_TRNS  , KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_HOME, KC_END,
        KC_TRNS, KC_TRNS  , KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB , KC_GRV   , KC_QUOT, LZF_2  , LZF_3  ,        KC_F16 ,                        KC_NO,   KC_PGDN, KC_PGUP, KC_NO,   KC_NO,   KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_ESC , KC_MINS  , KC_EQL , LZF_1  , LZF_5  ,        KC_BSLS, KC_BSPC,               KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS, KC_ENT,  KC_PGDN,
        KC_LSFT, KC_LSFT  , KC_MINS, LZF_4  , KC_BSLS,        KC_F17 , KC_ENT,                KC_NO,   RGUI(KC_END),  RGUI(KC_HOME), KC_NO,   KC_TRNS, KC_RSFT, KC_UP,
        KC_LCTL, KC_LALT  , KC_LGUI, KC_TRNS, LCTL_T(KC_F12), KC_LSFT, KC_SPC, KC_RGUI,       KC_NO,   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

[_LAYER3] = LAYOUT(
        KC_CAPS, KC_F1,     KC_F2,   KC_F3,   KC_F4,          KC_F5,                          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_HOME, KC_END,
        KC_GRV , KC_1,      KC_2,    KC_3,    KC_4,           KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB , KC_Q,      KC_W,    KC_E,    KC_R,           KC_T,                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_ESC , KC_A,      KC_S,    KC_D,    KC_F,           KC_G, KC_BSPC,                  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PGDN,
        KC_LSFT, KC_Z,      KC_X,    KC_C,    KC_V,           KC_B, KC_ENT,                   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI,   KC_LALT, KC_SPC,  LCTL_T(KC_F12), KC_LSFT, KC_SPC, KC_RGUI,       TG(3),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

[_LAYER4] = LAYOUT(
        QK_BOOT, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_CALC, KC_MYCM, KC_MSEL, KC_MAIL, NK_TOGG, EE_CLR,
        KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NUM,
        RGB_TOG, RGB_MOD,   RGB_VAI, RGB_HUI, KC_NO,          KC_NO,                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME,
        KC_TRNS, RGB_SPD,   RGB_VAD, RGB_SPI, KC_NO,          TG(3), KC_TRNS,                 KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_END,
        KC_TRNS, KC_NO  ,   KC_NO,   KC_NO,   KC_NO,          KC_TRNS, KC_TRNS,               KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_MUTE, KC_VOLU,
        KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_MPLY, KC_F14,  KC_VOLD, KC_F15
    )

};
