// Copyright 2024 Wind (@yelishang)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
    &delete_key_override
};

enum layers {
    WIN_B,
    WIN_FN,
    MAC_B,
    MAC_FN,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WIN_B] = LAYOUT_ansi(
        KC_CAPS, KC_BRID, KC_BRIU, KC_MCTL,	KC_LPAD, KC_F5,	  KC_F6,   KC_MPRV,	KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD,	KC_VOLU,                   KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        LCTL_T(KC_ESC), LCTL_T(KC_A),       LSFT_T(KC_S),       LALT_T(KC_D),       LWIN_T(KC_F),       KC_G,       RWIN_T(KC_H),       RALT_T(KC_J),       RSFT_T(KC_K),       RCTL_T(KC_L),    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LALT, KC_LGUI,                            LT(MAC_B, KC_SPC),                  KC_RGUI, MO(WIN_FN),       KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [WIN_FN] = LAYOUT_ansi(
        EE_CLR,  KC_BRID, KC_BRIU, KC_MCTL, KC_LPAD, KC_F5,   KC_F6,   KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,                   _______,
        KC_USB,  KC_BT1,  KC_BT2,  KC_BT3,  KC_2G4,  _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______, RGB_TOG, RGB_MOD, RGB_RMOD,RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______,                   _______, _______, _______,
        _______,_______,_______,                             _______,                             _______, _______,          _______, _______, _______
    ),

    [MAC_B] = LAYOUT_ansi(
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,          _______,
        _______, 	KC_EXLM,  	KC_UNDS,	KC_EQUAL,	KC_GRV,   	KC_TILD,   	KC_ASTR,	KC_CIRC,	KC_DLR,		KC_PERC,	KC_PLUS,   	_______,	_______,    _______, _______,
        _______,   	_______,   	_______,   	_______,  	_______,   	KC_AT,		KC_LEFT,   	KC_DOWN,   	KC_UP,   	KC_RGHT,  	KC_BSPC,   	_______,	            _______, _______,
        _______,	KC_AMPR,   	KC_LCBR,   	KC_RCBR,  	KC_LPRN,	KC_RPRN, 	KC_ENT,   	KC_MINUS,	_______,   	_______,  	KC_BSLS,	_______, _______,    _______,
        _______, _______, _______,                             _______,                           _______, _______,          _______, _______, _______
    ),

    [MAC_FN] = LAYOUT_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______,
        _______, _______, _______,                             _______,                           _______, _______,          _______, _______, _______
    )
};
// clang-format on
