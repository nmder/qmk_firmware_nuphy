// Copyright 2024 Wind (@yelishang)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t delete_key_override2 = ko_make_basic(MOD_MASK_SHIFT, LSFT_T(KC_BSPC), KC_DEL);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
    &delete_key_override,
    &delete_key_override2,
};

const uint16_t PROGMEM combo_lbrc[] = {KC_Y, KC_U, COMBO_END};
const uint16_t PROGMEM combo_rbrc[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM combo_plus[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM combo_mins[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM combo_tab_[] = {RCTL_T(KC_L), RSFT_T(KC_K), COMBO_END};
const uint16_t PROGMEM combo_hash[] = {LWIN_T(KC_F), RWIN_T(KC_H), COMBO_END};
const uint16_t PROGMEM combo_uscr[] = {LSFT_T(KC_S), LALT_T(KC_D), COMBO_END};
const uint16_t PROGMEM combo_equl[] = {LALT_T(KC_D), LWIN_T(KC_F), COMBO_END};
const uint16_t PROGMEM combo_ampr[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_cart[] = {LWIN_T(KC_F), KC_E, COMBO_END};
const uint16_t PROGMEM combo_dolr[] = {RWIN_T(KC_H), KC_U, COMBO_END};
const uint16_t PROGMEM combo_lprn[] = {RWIN_T(KC_H), RALT_T(KC_J), COMBO_END};
const uint16_t PROGMEM combo_rprn[] = {RALT_T(KC_J), RSFT_T(KC_K), COMBO_END};
const uint16_t PROGMEM combo_perc[] = {LALT_T(KC_D), KC_C, COMBO_END};
const uint16_t PROGMEM combo_astr[] = {RALT_T(KC_J), KC_N, COMBO_END};
const uint16_t PROGMEM combo_atra[] = {RALT_T(KC_J), LALT_T(KC_D), COMBO_END};
const uint16_t PROGMEM combo_baqt[] = {LALT_T(KC_D), KC_V, COMBO_END};
const uint16_t PROGMEM combo_tild[] = {RALT_T(KC_J), KC_B, COMBO_END};
const uint16_t PROGMEM combo_excl[] = {RSFT_T(KC_K), LSFT_T(KC_S), COMBO_END};
const uint16_t PROGMEM combo_mute[] = {KC_VOLD, KC_VOLU, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_lbrc, KC_LBRC),
    COMBO(combo_rbrc, KC_RBRC),
    COMBO(combo_plus, KC_PLUS),
    COMBO(combo_mins, KC_MINS),
    COMBO(combo_tab_, KC_TAB),
    COMBO(combo_hash, KC_HASH),
    COMBO(combo_uscr, KC_UNDS),
    COMBO(combo_equl, KC_EQUAL),
    COMBO(combo_ampr, KC_AMPR),
    COMBO(combo_cart, KC_CIRC),
    COMBO(combo_dolr, KC_DLR),
    COMBO(combo_lprn, KC_LPRN),
    COMBO(combo_rprn, KC_RPRN),
    COMBO(combo_perc, KC_PERC),
    COMBO(combo_astr, KC_ASTR),
    COMBO(combo_atra, KC_AT),
    COMBO(combo_baqt, KC_GRV),
    COMBO(combo_tild, KC_TILD),
    COMBO(combo_excl, KC_EXLM),
    COMBO(combo_mute, KC_MUTE),
};

#ifdef COMBO_TERM_PER_COMBO
uint16_t get_combo_term(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
        case 4 ... 7:
            return 30;
        case 15:
            return 30;
        case 18:
            return 40;
    }

    return COMBO_TERM;
}
#endif

#ifdef COMBO_MUST_TAP_PER_COMBO
bool get_combo_must_tap(uint16_t combo_index, combo_t *combo) {
    // If you want all combos to be tap-only, just uncomment the next line
    // return true

    // If you want *all* combos, that have Mod-Tap/Layer-Tap/Momentary keys in its chord, to be tap-only, this is for you:
    uint16_t key;
    uint8_t idx = 0;
    while ((key = pgm_read_word(&combo->keys[idx])) != COMBO_END) {
        switch (key) {
            case QK_MOD_TAP...QK_MOD_TAP_MAX:
            case QK_LAYER_TAP...QK_LAYER_TAP_MAX:
            case QK_MOMENTARY...QK_MOMENTARY_MAX:
                return true;
        }
        idx += 1;
    }
    return false;

}
#endif

enum layers {
    WIN_B,
    WIN_FN,
    MAC_B,
    NUM,
};

enum hjkl {
    ID_H,
    ID_J,
    ID_K,
    ID_L,
    L_ID,
    ID_OUT
};

const uint16_t mt_taps[] = { KC_LPRN, KC_LCBR, KC_RCBR, KC_RPRN };
const uint16_t mt_mods[] = { KC_RWIN, KC_RALT, KC_RSFT, KC_RCTL };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    static uint16_t tap_timer[] = { 0, 0, 0, 0 };
    static bool held[] = { false, false, false, false };

    enum hjkl kc;
    switch (keycode) {
        case KC_H:
            kc = ID_H;
            break;

        case KC_J:
            kc = ID_J;
            break;

        case KC_K:
            kc = ID_K;
            break;

        case KC_L:
            kc = ID_L;
            break;

        default:
            kc = ID_OUT;
    }

    if (kc != ID_OUT) {
        if (IS_LAYER_ON(NUM) && record->event.pressed) {
            tap_timer[kc] = timer_read();
            held[kc] = false;
            return false;
        } else if (tap_timer[kc] != 0) {
            if (timer_elapsed(tap_timer[kc]) < TAPPING_TERM) {
                tap_code16(mt_taps[kc]);
            }
            tap_timer[kc] = 0;
            return false;
        } else if (held[kc]) {
            unregister_code(mt_mods[kc]);
            held[kc] = false;
            return false;
        }
    } else {
        for (enum hjkl id = ID_H; id < L_ID; id++) {
            if (tap_timer[id] != 0 && (record->event.pressed || timer_elapsed(tap_timer[id]) > TAPPING_TERM)) {
                tap_timer[id] = 0;
                register_code(mt_mods[id]);
                held[id] = true;
            }
        }
    }
    return true;
}
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WIN_B] = LAYOUT_ansi(
        KC_CAPS, KC_BRID, KC_BRIU, KC_MCTL,	KC_LPAD, KC_F5,	  KC_F6,   KC_MPRV,	KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD,	KC_VOLU,                   KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        LT(NUM, KC_ESC), LCTL_T(KC_A),       LSFT_T(KC_S),       LALT_T(KC_D),       LWIN_T(KC_F),       KC_G,       RWIN_T(KC_H),       RALT_T(KC_J),       RSFT_T(KC_K),       RCTL_T(KC_L),    LT(NUM, KC_SCLN), KC_QUOT,          KC_ENT,           KC_PGDN,
        LSFT_T(KC_BSPC), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT, KC_UP,   KC_END,
        KC_GLB, KC_LALT, KC_LGUI,                            LT(MAC_B, KC_SPC),                  KC_RGUI, MO(WIN_FN),       KC_LEFT, KC_DOWN, KC_RGHT
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
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_DEL,          _______,
        _______, 	KC_EXLM,  	KC_UNDS,	KC_EQUAL,	KC_GRV,   	KC_TILD,   	KC_ASTR,	KC_CIRC,	KC_DLR,		KC_PERC,	KC_PLUS,   	_______,	_______,    _______, _______,
        _______,   	_______,   	_______,   	_______,  	_______,   	KC_AT,		KC_LEFT,   	KC_DOWN,   	KC_UP,   	KC_RGHT,  	KC_BSPC,   	_______,	            _______, _______,
        _______,	KC_AMPR,   	KC_LT,   	KC_GT,  	KC_BSLS,	KC_PIPE, 	KC_ENT,   	KC_MINUS,	KC_HASH,   	KC_TAB,  	KC_BSLS,	_______, _______,    _______,
        _______, _______, _______,                             _______,                           _______, _______,          _______, _______, _______
    ),

    [NUM] = LAYOUT_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_AMPR,		KC_DQUO,   	KC_QUOT,   	KC_AT,		KC_QUES,    _______, _______, _______,          _______,
        KC_BSPC, LCTL_T(KC_6),       LSFT_T(KC_7),       LALT_T(KC_8),       LWIN_T(KC_9), KC_0,	KC_H,	KC_J,	KC_K,	KC_L,	KC_BSPC, _______,          _______,          _______,
        _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU, KC_LBRC,	KC_RBRC,	_______, _______, _______,                   _______, _______, _______,
        _______, _______, _______,                             _______,                           _______, _______,          _______, _______, _______
    )
};
// clang-format on
