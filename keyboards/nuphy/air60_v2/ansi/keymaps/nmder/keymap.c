/*
Copyright 2023 @ Nuphy <https://nuphy.com/>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t delete_key_override2 = ko_make_basic(MOD_MASK_SHIFT, LSFT_T(KC_BSPC), KC_DEL);
const key_override_t delete_key_override3 = ko_make_basic(MOD_MASK_SHIFT, LT(8, KC_BSPC), KC_DEL);

const key_override_t vold_override = ko_make_basic(MOD_MASK_SHIFT, KC_VOLD, KC_MUTE);

const key_override_t mswh_l_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_MS_R, KC_WH_L);
const key_override_t mswh_r_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_MS_L, KC_WH_R);
const key_override_t mswh_u_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_MS_D, KC_WH_U);
const key_override_t mswh_d_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_MS_U, KC_WH_D);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    &delete_key_override2,
    &delete_key_override3,
    &vold_override,
    &mswh_l_key_override,
    &mswh_r_key_override,
    &mswh_u_key_override,
    &mswh_d_key_override,
    NULL
};

const uint16_t PROGMEM combo_lbrc[] = {RWIN_T(KC_J), KC_COMM, COMBO_END};
const uint16_t PROGMEM combo_rbrc[] = {RALT_T(KC_K), KC_DOT, COMBO_END};
const uint16_t PROGMEM combo_plus[] = {KC_DOT, KC_COMM, COMBO_END};
const uint16_t PROGMEM combo_mins[] = {KC_COMM, KC_M, COMBO_END};
const uint16_t PROGMEM combo_tab_[] = {RSFT_T(KC_L), RALT_T(KC_K), COMBO_END};
const uint16_t PROGMEM combo_uscr[] = {LSFT_T(KC_S), LALT_T(KC_D), COMBO_END};
const uint16_t PROGMEM combo_equl[] = {LALT_T(KC_D), LWIN_T(KC_F), COMBO_END};
const uint16_t PROGMEM combo_lprn[] = {KC_H, RALT_T(KC_K), COMBO_END};
const uint16_t PROGMEM combo_rprn[] = {RWIN_T(KC_J), RALT_T(KC_K), COMBO_END};
const uint16_t PROGMEM combo_astr[] = {RALT_T(KC_K), KC_M, COMBO_END};
const uint16_t PROGMEM combo_baqt[] = {LALT_T(KC_D), KC_V, COMBO_END};
const uint16_t PROGMEM combo_lcrb[] = {KC_H, RSFT_T(KC_L), COMBO_END};
const uint16_t PROGMEM combo_rcrb[] = {RWIN_T(KC_J), RSFT_T(KC_L), COMBO_END};
const uint16_t PROGMEM combo_dquo[] = {LSFT_T(KC_S), LWIN_T(KC_F), COMBO_END};
const uint16_t PROGMEM combo_squo[] = {LWIN_T(KC_F), LCTL_T(KC_A), COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_lbrc, KC_LBRC),
    COMBO(combo_rbrc, KC_RBRC),
    COMBO(combo_plus, KC_PLUS),
    COMBO(combo_mins, KC_MINS),
    COMBO(combo_tab_, KC_TAB),
    COMBO(combo_uscr, KC_UNDS),
    COMBO(combo_equl, KC_EQUAL),
    COMBO(combo_lprn, KC_LPRN),
    COMBO(combo_rprn, KC_RPRN),
    COMBO(combo_astr, KC_ASTR),
    COMBO(combo_baqt, KC_GRV),
    COMBO(combo_lcrb, KC_LCBR),
    COMBO(combo_rcrb, KC_RCBR),
    COMBO(combo_dquo, KC_DQUO),
    COMBO(combo_squo, KC_QUOT),
};

#ifdef COMBO_TERM_PER_COMBO
uint16_t get_combo_term(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
        case 4 ... 6:
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

enum hjkl {
    ID_J,
    ID_K,
    ID_L,
    ID_A,
    ID_S,
    ID_F,
    L_ID,
    ID_OUT
};

const uint16_t mt_taps[] = { KC_LCBR, KC_RCBR, KC_RPRN, KC_AT, KC_AMPR, KC_DQUO };
const uint16_t mt_mods[] = { KC_RWIN, KC_RALT, KC_RSFT, KC_LCTL, KC_LSFT, KC_LWIN };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    static uint16_t tap_timer[] = { 0, 0, 0, 0, 0, 0 };
    static bool held[] = { false, false, false, false, false, false };

    enum hjkl kc;
    switch (keycode) {
        case KC_J:
            kc = ID_J;
            break;

        case KC_K:
            kc = ID_K;
            break;

        case KC_L:
            kc = ID_L;
            break;

        case KC_A:
            kc = ID_A;
            break;

        case KC_S:
            kc = ID_S;
            break;

        case KC_F:
            kc = ID_F;
            break;

        default:
            kc = ID_OUT;
    }

    if (kc != ID_OUT) {
        if (((IS_LAYER_ON(7) && kc < ID_A ) || (IS_LAYER_ON(6) && ID_L < kc && kc < L_ID )) && record->event.pressed) {
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
        for (enum hjkl id = ID_J; id < L_ID; id++) {
            if (tap_timer[id] != 0 && (record->event.pressed || timer_elapsed(tap_timer[id]) > TAPPING_TERM)) {
                tap_timer[id] = 0;
                register_code(mt_mods[id]);
                held[id] = true;
            }
        }
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// layer 0 Mac
[0] = LAYOUT(
	KC_GRV, 			KC_1,   		KC_2,   		KC_3,  			KC_4,   		KC_5,	KC_6,			KC_7,   		KC_8,   		KC_9,  			KC_0,   		KC_MINS,	KC_EQL, 	KC_BSPC,
	KC_TAB, 			KC_Q,   		KC_W,   		KC_E,  			KC_R,   		KC_T,	KC_Y,			KC_U,   		KC_I,   		KC_O,  			KC_P,   		KC_LBRC,	KC_RBRC, 	KC_BSLS,
	LT(7, KC_ESC),		LCTL_T(KC_A),  	LSFT_T(KC_S),  	LALT_T(KC_D),	LWIN_T(KC_F),  	KC_G,	KC_H,	RWIN_T(KC_J),  	RALT_T(KC_K),  	RSFT_T(KC_L),	RCTL_T(KC_SCLN),	LT(7, KC_QUOT), 	            KC_ENT,
	LSFT_T(KC_BSPC),	KC_Z,   		KC_X,   		KC_C,  			KC_V,   		KC_B,	KC_N,			KC_M,   		KC_COMM,		KC_DOT,			KC_SLSH,		KC_RSFT,	KC_UP,		KC_CAPS,
	KC_GLB, 			KC_LALT,		KC_LGUI,										LT(6, KC_SPC),   										KC_RGUI,		MO(1),   		KC_LEFT,	KC_DOWN,    KC_RGHT),

// layer 1 Mac fn
[1] = LAYOUT(
	KC_ESC, 	KC_BRID,  	KC_BRIU,  	MAC_TASK, 	MAC_SEARCH, MAC_VOICE,  MAC_DND,  	KC_MPRV,  	KC_MPLY,  	KC_MNXT, 	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 	_______,
	_______, 	LNK_BLE1,  	LNK_BLE2,  	LNK_BLE3,  	LNK_RF,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	DEV_RESET,	SLEEP_MODE, BAT_SHOW,
	_______, 	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	            _______,
	MO(2),	    _______,   	_______,   	_______,  	_______,   	_______,   	_______,   	MO(5),   	RGB_SPD,	RGB_SPI,  	_______,	MO(2),  	RGB_VAI,    _______,
	_______,	_______,	_______,										DF(3),   							_______,	_______,   	RGB_MOD,	RGB_VAD,    RGB_HUI),

// layer 2 Mac Fn+shift
[2] = LAYOUT(
	SHIFT_GRV, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	_______,
	_______, 	_______,  	_______,  	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______,    _______,
	_______, 	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	            _______,
	_______,	_______,   	_______,   	RGB_TEST,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,	_______, 	_______,    _______,
	_______,	_______,	_______,										_______, 							_______,	_______,   	_______,	_______,    _______),

// layer 3 Win
[3] = LAYOUT(
	KC_GRV, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 	KC_BSPC,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC, 	KC_BSLS,
	MT(MOD_LCTL, KC_ESC),	KC_A,   	KC_S,   	KC_D,  		KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	KC_QUOT,	KC_ENT,
	KC_LSFT,	KC_Z,   	KC_X,   	KC_C,  		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,	KC_RSFT,	KC_UP,		KC_DEL,
	KC_LCTL,	KC_LGUI,	KC_LALT,										KC_SPC, 							KC_RALT,	MO(4),   	KC_LEFT,	KC_DOWN,    KC_RGHT),

// layer 4 win fn
[4] = LAYOUT(
	KC_GRV, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	_______,
	_______, 	LNK_BLE1,  	LNK_BLE2,  	LNK_BLE3,  	LNK_RF,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	DEV_RESET,	SLEEP_MODE, BAT_SHOW,
	_______, 	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	            _______,
	MO(1),	    _______,   	_______,   	_______,  	_______,   	_______,   	_______,   	MO(5),   	RGB_SPD,	RGB_SPI,  	_______,	MO(1),  	RGB_VAI,    _______,
	_______,	_______,	_______,										DF(0),   							_______,	_______,   	RGB_MOD,	RGB_VAD,    RGB_HUI),

/*// layer 5 win fn+shift*/
/*[5] = LAYOUT(*/
/*	SHIFT_GRV, 	KC_BRID,   	KC_BRIU,    _______,  	_______,   	_______,   	_______,   	KC_MPRV,   	KC_MPLY,   	KC_MNXT,  	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 	_______,*/
/*	_______, 	_______,  	_______,  	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______,    _______,*/
/*	_______, 	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	            _______,*/
/*	_______,	_______,   	_______,   	RGB_TEST,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,	_______, 	_______,    _______,*/
/*	_______,	_______,	_______,										_______, 							_______,	_______,   	_______,	_______,    _______),*/

// layer 6 function
[5] = LAYOUT(
	_______, 	_______,  	_______,  	_______, 	_______,  	_______,  	_______,  	_______,  	_______,  	_______, 	_______, 	_______, 	_______, 	_______,
	_______, 	_______,  	_______,  	_______, 	_______,  	_______,  	_______,  	_______,  	_______,  	_______, 	_______, 	_______, 	_______, 	_______,
	_______, 	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	            _______,
	_______,    _______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	SIDE_SPD,	SIDE_SPI,  	_______,	_______,  	SIDE_VAI,    _______,
	_______,	_______,	_______,										_______, 							_______,	_______,   	SIDE_MOD,	SIDE_VAD,    SIDE_HUI),

// layer 7 Mac Space
[6] = LAYOUT(
	_______, 	KC_F1,  	KC_F2,  	KC_F3,   	KC_F4,  		KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9,   	KC_F10, 	KC_F11, 	KC_F12, 	KC_DEL,
	KC_MUTE, 	KC_EXLM,  	KC_UNDS,	KC_EQUAL,	KC_GRV,   		KC_TILD,   	KC_ASTR,	KC_CIRC,	KC_DLR,		KC_PERC,	KC_PLUS,   	_______,	_______,    _______,
	KC_VOLU,	KC_A,	 	KC_S,		LALT_T(KC_QUOT),	KC_F,	KC_HASH,		KC_LEFT,   	KC_DOWN,   	KC_UP,   	KC_RGHT,  	LT(8, KC_BSPC),   	_______,	            _______,
	KC_VOLD,	_______,   	KC_MPRV,   	KC_MPLY,  	KC_MNXT,		KC_PIPE, 	KC_ENT,   	KC_MINUS,	KC_PLUS,   	KC_TAB,  	KC_BSLS,	KC_MS_BTN1, KC_MS_U,    KC_MS_BTN2,
	_______,	_______,	_______,											_______, 							_______,	_______,   	KC_MS_L,	KC_MS_D,    KC_MS_R),

// layer 8 numbers
[7] = LAYOUT(
	KC_ESC, 	KC_BRID,  	KC_BRIU,  	MAC_TASK, 	MAC_SEARCH, MAC_VOICE,  MAC_DND,  	KC_MPRV,  	KC_MPLY,  	KC_MNXT, 	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 	_______,
	_______, 	KC_MINUS,	    KC_1,	    KC_2,	    KC_3,		KC_PLUS,		KC_VOLD,		KC_MPRV,   	KC_MPLY,  	KC_MNXT,	KC_VOLU,   	_______,	_______,    _______,
	_______,   	LCTL_T(KC_BSPC),  	LSFT_T(KC_4),  	LALT_T(KC_5),	LWIN_T(KC_6),	KC_0,		KC_LPRN,		KC_J,		KC_K,		KC_L,		RCTL_T(KC_BSPC),   	_______,	            _______,
	KC_SLSH,	KC_ASTR,  	KC_7,  	KC_8, 	KC_9,		KC_DOT, 	_______,	KC_LBRC,	KC_RBRC,	_______,	_______,	_______, 	_______, 	_______,
	_______,	_______,	_______,											MO(8), 							_______,	_______,   	_______,	_______,    _______),

// layer 9 numbers
[8] = LAYOUT(
	_______, 	_______,  	_______,  	_______, 	_______, _______,  _______,  	_______,  	_______,  	_______, 	_______, 	_______, 	_______, 	_______,
	_______, 	_______,	    KC_F1,	    KC_F2,	    KC_F3,		KC_F10,		_______,		_______,   	_______,   	_______,		_______,   	_______,	_______,    _______,
	_______,   	_______,  	KC_F4,  	KC_F5,	KC_F6,	KC_F11,		_______,		_______,		_______,		_______,		_______,   	_______,	            _______,
	_______,	_______,  	KC_F7,  	KC_F8, 	KC_F9,		KC_F12, 	_______,	_______,	_______,	_______,	_______,	_______, 	_______, 	_______,
	_______,	_______,	_______,											_______, 							_______,	_______,   	_______,	_______,    _______)
};


const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
    {0, A_16,   B_16,   C_16},      // "Esc"
    {0, A_2,    B_2,    C_2},       // "!1"
    {0, A_3,    B_3,    C_3},       // "@2"
    {0, A_4,    B_4,    C_4},       // "#3"
    {0, A_5,    B_5,    C_5},       // "$4"
    {0, A_6,    B_6,    C_6},       // "%5"
    {0, A_7,    B_7,    C_7},       // "^6"
    {0, A_8,    B_8,    C_8},       // "&7"
    {0, A_9,    B_9,    C_9},       // "*8"
    {0, A_10,   B_10,   C_10},      // "(9"
    {0, A_11,   B_11,   C_11},      // ")0"
    {1, D_1,    E_1,    F_1},       // "_-"
    {1, D_2,    E_2,    F_2},       // "+="
    {1, D_3,    E_3,    F_3},       // "Backsp"
    {0, D_1,    E_1,    F_1},       // "Tab"
    {0, D_2,    E_2,    F_2},       // "Q"
    {0, D_3,    E_3,    F_3},       // "W"
    {0, D_4,    E_4,    F_4},       // "E"
    {0, D_5,    E_5,    F_5},       // "R"
    {0, D_6,    E_6,    F_6},       // "T"
    {0, D_7,    E_7,    F_7},       // "Y"
    {0, D_8,    E_8,    F_8},       // "U"
    {0, D_9,    E_9,    F_9},       // "I"
    {0, D_10,   E_10,   F_10},      // "O"
    {0, D_11,   E_11,   F_11},      // "P"
    {1, G_1,    H_1,    I_1},       // "{["
    {1, G_2,    H_2,    I_2},       // "}]"
    {1, G_3,    H_3,    I_3},       // "|\\"
    {0, G_1,    H_1,    I_1},       // "Caps"
    {0, G_2,    H_2,    I_2},       // "A"
    {0, G_3,    H_3,    I_3},       // "S"
    {0, G_4,    H_4,    I_4},       // "D"
    {0, G_5,    H_5,    I_5},       // "F"
    {0, G_6,    H_6,    I_6},       // "G"
    {0, G_7,    H_7,    I_7},       // "H"
    {0, G_8,    H_8,    I_8},       // "J"
    {0, G_9,    H_9,    I_9},       // "K"
    {0, G_10,   H_10,   I_10},      // "L"
    {0, G_11,   H_11,   I_11},      // ":"
    {1, G_16,   H_16,   I_16},      // "\""
    {1, G_14,   H_14,   I_14},      // "Enter"
    {0, J_1,    K_1,    L_1},       // "Shift"
    {0, J_3,    K_3,    L_3},       // "Z"
    {0, J_4,    K_4,    L_4},       // "X"
    {0, J_5,    K_5,    L_5},       // "C"
    {0, J_6,    K_6,    L_6},       // "V"
    {0, J_7,    K_7,    L_7},       // "B"
    {0, J_8,    K_8,    L_8},       // "N"
    {0, J_9,    K_9,    L_9},       // "M"
    {0, J_10,   K_10,   L_10},      // "<,"
    {0, J_11,   K_11,   L_11},      // ">."
    {1, J_1,    K_1,    L_1},       // "?/"
    {1, J_3,    K_3,    L_3},       // "Shift"
    {1, J_4,    K_4,    L_4},       // "↑"
    {1, G_4,    H_4,    I_4},       // "Del"
    {0, J_16,   K_16,   L_16},      // "Ctrl"
    {0, J_15,   K_15,   L_15},      // "Opt"
    {0, J_14,   K_14,   L_14},      // "Cmd"
    {0, J_13,   K_13,   L_13},      // "Space"
    {0, J_12,   K_12,   L_12},      // "Cmd"
    {1, J_16,   K_16,   L_16},      // "Fn"
    {1, J_13,   K_13,   L_13},      // "←"
    {1, J_12,   K_12,   L_12},      // "↓"
    {1, J_11,   K_11,   L_11},      // "→"

    {1, A_5,    B_5,    C_5},       // logo left
    {1, A_4,    B_4,    C_4},       //
    {1, A_3,    B_3,    C_3},       //
    {1, A_2,    B_2,    C_2},       //
    {1, A_1,    B_1,    C_1},       //

    {1, A_6,    B_6,    C_6},       // logo right
    {1, A_7,    B_7,    C_7},       //
    {1, A_8,    B_8,    C_8},       //
    {1, A_9,    B_9,    C_9},       //
    {1, A_10,   B_10,   C_10}       //
};
