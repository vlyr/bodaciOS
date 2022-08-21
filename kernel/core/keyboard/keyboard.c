#include <io.h>
#include <keyboard.h>
#include <stddef.h>

// https://web.archive.org/web/20170108170113if_/http://www.computer-engineering.org/ps2keyboard/scancodes1.html
// https://github.com/RicardoLuis0/simple-ps2-keyboard-driver-osdev/blob/main/keyboard.c
static const enum keyboard_keycode us_qwerty_keycodes[0xE0] = {
    KEYBOARD_KEY_INVALID,               // 0x00 invalid
    KEYBOARD_KEY_ESC_PRESSED,           // 0x01 ESCAPE
    KEYBOARD_KEY_1_PRESSED,             // 0x02
    KEYBOARD_KEY_2_PRESSED,             // 0x03
    KEYBOARD_KEY_3_PRESSED,             // 0x04
    KEYBOARD_KEY_4_PRESSED,             // 0x05
    KEYBOARD_KEY_5_PRESSED,             // 0x06
    KEYBOARD_KEY_6_PRESSED,             // 0x07
    KEYBOARD_KEY_7_PRESSED,             // 0x08
    KEYBOARD_KEY_8_PRESSED,             // 0x09
    KEYBOARD_KEY_9_PRESSED,             // 0x0A
    KEYBOARD_KEY_0_PRESSED,             // 0x0B
    KEYBOARD_KEY_MINUS_PRESSED,         // 0x0C
    KEYBOARD_KEY_EQUALS_PRESSED,        // 0x0D
    KEYBOARD_KEY_BACKSPACE_PRESSED,     // 0x0E
    KEYBOARD_KEY_TAB_PRESSED,           // 0x0F
    KEYBOARD_KEY_Q_PRESSED,             // 0x10
    KEYBOARD_KEY_W_PRESSED,             // 0x11
    KEYBOARD_KEY_E_PRESSED,             // 0x12
    KEYBOARD_KEY_R_PRESSED,             // 0x13
    KEYBOARD_KEY_T_PRESSED,             // 0x14
    KEYBOARD_KEY_Y_PRESSED,             // 0x15
    KEYBOARD_KEY_U_PRESSED,             // 0x16
    KEYBOARD_KEY_I_PRESSED,             // 0x17
    KEYBOARD_KEY_O_PRESSED,             // 0x18
    KEYBOARD_KEY_P_PRESSED,             // 0x19
    KEYBOARD_KEY_LEFT_BRACKET_PRESSED,  // 0x1A
    KEYBOARD_KEY_RIGHT_BRACKET_PRESSED, // 0x1B
    KEYBOARD_KEY_ENTER_PRESSED,         // 0x1C
    KEYBOARD_KEY_LEFT_CONTROL_PRESSED,  // 0x1D
    KEYBOARD_KEY_A_PRESSED,             // 0x1E
    KEYBOARD_KEY_S_PRESSED,             // 0x1F
    KEYBOARD_KEY_D_PRESSED,             // 0x20
    KEYBOARD_KEY_F_PRESSED,             // 0x21
    KEYBOARD_KEY_G_PRESSED,             // 0x22
    KEYBOARD_KEY_H_PRESSED,             // 0x23
    KEYBOARD_KEY_J_PRESSED,             // 0x24
    KEYBOARD_KEY_K_PRESSED,             // 0x25
    KEYBOARD_KEY_L_PRESSED,             // 0x26
    KEYBOARD_KEY_SEMICOLON_PRESSED,     // 0x27
    KEYBOARD_KEY_SINGLE_QUOTE_PRESSED,  // 0x28
    KEYBOARD_KEY_BACKTICK_PRESSED,      // 0x29
    KEYBOARD_KEY_LEFT_SHIFT_PRESSED,    // 0x2A
    KEYBOARD_KEY_BACKSLASH_PRESSED,     // 0x2B
    KEYBOARD_KEY_Z_PRESSED,             // 0x2C
    KEYBOARD_KEY_X_PRESSED,             // 0x2D
    KEYBOARD_KEY_C_PRESSED,             // 0x2E
    KEYBOARD_KEY_V_PRESSED,             // 0x2F
    KEYBOARD_KEY_B_PRESSED,             // 0x30
    KEYBOARD_KEY_N_PRESSED,             // 0x31
    KEYBOARD_KEY_M_PRESSED,             // 0x32
    KEYBOARD_KEY_COMMA_PRESSED,         // 0x33
    KEYBOARD_KEY_DOT_PRESSED,           // 0x34
    KEYBOARD_KEY_SLASH_PRESSED,         // 0x35
    KEYBOARD_KEY_RIGHT_SHIFT_PRESSED,   // 0x36
    KEYBOARD_KEY_KP_STAR_PRESSED,       // 0x37
    KEYBOARD_KEY_LEFT_ALT_PRESSED,      // 0x38
    KEYBOARD_KEY_SPACE_PRESSED,         // 0x39
    KEYBOARD_KEY_CAPSLOCK_PRESSED,      // 0x3A
    KEYBOARD_KEY_F1_PRESSED,            // 0x3B
    KEYBOARD_KEY_F2_PRESSED,            // 0x3C
    KEYBOARD_KEY_F3_PRESSED,            // 0x3D
    KEYBOARD_KEY_F4_PRESSED,            // 0x3E
    KEYBOARD_KEY_F5_PRESSED,            // 0x3F
    KEYBOARD_KEY_F6_PRESSED,            // 0x40
    KEYBOARD_KEY_F7_PRESSED,            // 0x41
    KEYBOARD_KEY_F8_PRESSED,            // 0x42
    KEYBOARD_KEY_F9_PRESSED,            // 0x43
    KEYBOARD_KEY_F10_PRESSED,           // 0x44
    KEYBOARD_KEY_NUM_LOCK_PRESSED,      // 0x45
    KEYBOARD_KEY_SCROLL_LOCK_PRESSED,   // 0x46
    KEYBOARD_KEY_KP_7_PRESSED,          // 0x47
    KEYBOARD_KEY_KP_8_PRESSED,          // 0x48
    KEYBOARD_KEY_KP_9_PRESSED,          // 0x49
    KEYBOARD_KEY_KP_MINUS_PRESSED,      // 0x4A
    KEYBOARD_KEY_KP_4_PRESSED,          // 0x4B
    KEYBOARD_KEY_KP_5_PRESSED,          // 0x4C
    KEYBOARD_KEY_KP_6_PRESSED,          // 0x4D
    KEYBOARD_KEY_KP_PLUS_PRESSED,       // 0x4E
    KEYBOARD_KEY_KP_1_PRESSED,          // 0x4F
    KEYBOARD_KEY_KP_2_PRESSED,          // 0x50
    KEYBOARD_KEY_KP_3_PRESSED,          // 0x51
    KEYBOARD_KEY_KP_0_PRESSED,          // 0x52
    KEYBOARD_KEY_KP_DOT_PRESSED,        // 0x53
    KEYBOARD_KEY_INVALID,               // 0x54
    KEYBOARD_KEY_INVALID,               // 0x55
    KEYBOARD_KEY_INVALID,               // 0x56
    KEYBOARD_KEY_F11_PRESSED,           // 0x57
    KEYBOARD_KEY_F12_PRESSED,           // 0x58
    KEYBOARD_KEY_INVALID,               // 0x59
    KEYBOARD_KEY_INVALID,               // 0x5A
    KEYBOARD_KEY_INVALID,               // 0x5B
    KEYBOARD_KEY_INVALID,               // 0x5C
    KEYBOARD_KEY_INVALID,               // 0x5D
    KEYBOARD_KEY_INVALID,               // 0x5E
    KEYBOARD_KEY_INVALID,               // 0x5F
    KEYBOARD_KEY_INVALID,               // 0x60
    KEYBOARD_KEY_INVALID,               // 0x61
    KEYBOARD_KEY_INVALID,               // 0x62
    KEYBOARD_KEY_INVALID,               // 0x63
    KEYBOARD_KEY_INVALID,               // 0x64
    KEYBOARD_KEY_INVALID,               // 0x65
    KEYBOARD_KEY_INVALID,               // 0x66
    KEYBOARD_KEY_INVALID,               // 0x67
    KEYBOARD_KEY_INVALID,               // 0x68
    KEYBOARD_KEY_INVALID,               // 0x69
    KEYBOARD_KEY_INVALID,               // 0x6A
    KEYBOARD_KEY_INVALID,               // 0x6B
    KEYBOARD_KEY_INVALID,               // 0x6C
    KEYBOARD_KEY_INVALID,               // 0x6D
    KEYBOARD_KEY_INVALID,               // 0x6E
    KEYBOARD_KEY_INVALID,               // 0x6F
    KEYBOARD_KEY_INVALID,               // 0x70
    KEYBOARD_KEY_INVALID,               // 0x71
    KEYBOARD_KEY_INVALID,               // 0x72
    KEYBOARD_KEY_INVALID,               // 0x73
    KEYBOARD_KEY_INVALID,               // 0x74
    KEYBOARD_KEY_INVALID,               // 0x75
    KEYBOARD_KEY_INVALID,               // 0x76
    KEYBOARD_KEY_INVALID,               // 0x77
    KEYBOARD_KEY_INVALID,               // 0x78
    KEYBOARD_KEY_INVALID,               // 0x79
    KEYBOARD_KEY_INVALID,               // 0x7A
    KEYBOARD_KEY_INVALID,               // 0x7B
    KEYBOARD_KEY_INVALID,               // 0x7C
    KEYBOARD_KEY_INVALID,               // 0x7D
    KEYBOARD_KEY_INVALID,               // 0x7E
    KEYBOARD_KEY_INVALID,               // 0x7F
    KEYBOARD_KEY_INVALID,               // 0x80
    // RELEASED
    KEYBOARD_KEY_ESC_RELEASED,           // 0x81
    KEYBOARD_KEY_1_RELEASED,             // 0x82
    KEYBOARD_KEY_2_RELEASED,             // 0x83
    KEYBOARD_KEY_3_RELEASED,             // 0x84
    KEYBOARD_KEY_4_RELEASED,             // 0x85
    KEYBOARD_KEY_5_RELEASED,             // 0x86
    KEYBOARD_KEY_6_RELEASED,             // 0x87
    KEYBOARD_KEY_7_RELEASED,             // 0x88
    KEYBOARD_KEY_8_RELEASED,             // 0x89
    KEYBOARD_KEY_9_RELEASED,             // 0x8A
    KEYBOARD_KEY_0_RELEASED,             // 0x8B
    KEYBOARD_KEY_MINUS_RELEASED,         // 0x8C
    KEYBOARD_KEY_EQUALS_RELEASED,        // 0x8D
    KEYBOARD_KEY_BACKSPACE_RELEASED,     // 0x8E
    KEYBOARD_KEY_TAB_RELEASED,           // 0x9F
    KEYBOARD_KEY_Q_RELEASED,             // 0x90
    KEYBOARD_KEY_W_RELEASED,             // 0x91
    KEYBOARD_KEY_E_RELEASED,             // 0x92
    KEYBOARD_KEY_R_RELEASED,             // 0x93
    KEYBOARD_KEY_T_RELEASED,             // 0x94
    KEYBOARD_KEY_Y_RELEASED,             // 0x95
    KEYBOARD_KEY_U_RELEASED,             // 0x96
    KEYBOARD_KEY_I_RELEASED,             // 0x97
    KEYBOARD_KEY_O_RELEASED,             // 0x98
    KEYBOARD_KEY_P_RELEASED,             // 0x99
    KEYBOARD_KEY_LEFT_BRACKET_RELEASED,  // 0x9A
    KEYBOARD_KEY_RIGHT_BRACKET_RELEASED, // 0x9B
    KEYBOARD_KEY_ENTER_RELEASED,         // 0x9C
    KEYBOARD_KEY_LEFT_CONTROL_RELEASED,  // 0x9D
    KEYBOARD_KEY_A_RELEASED,             // 0x9E
    KEYBOARD_KEY_S_RELEASED,             // 0x9F
    KEYBOARD_KEY_D_RELEASED,             // 0xA0
    KEYBOARD_KEY_F_RELEASED,             // 0xA1
    KEYBOARD_KEY_G_RELEASED,             // 0xA2
    KEYBOARD_KEY_H_RELEASED,             // 0xA3
    KEYBOARD_KEY_J_RELEASED,             // 0xA4
    KEYBOARD_KEY_K_RELEASED,             // 0xA5
    KEYBOARD_KEY_L_RELEASED,             // 0xA6
    KEYBOARD_KEY_SEMICOLON_RELEASED,     // 0xA7
    KEYBOARD_KEY_SINGLE_QUOTE_RELEASED,  // 0xA8
    KEYBOARD_KEY_BACKTICK_RELEASED,      // 0xA9
    KEYBOARD_KEY_LEFT_SHIFT_RELEASED,    // 0xAA
    KEYBOARD_KEY_BACKSLASH_RELEASED,     // 0xAB
    KEYBOARD_KEY_Z_RELEASED,             // 0xAC
    KEYBOARD_KEY_X_RELEASED,             // 0xAD
    KEYBOARD_KEY_C_RELEASED,             // 0xAE
    KEYBOARD_KEY_V_RELEASED,             // 0xAF
    KEYBOARD_KEY_B_RELEASED,             // 0xB0
    KEYBOARD_KEY_N_RELEASED,             // 0xB1
    KEYBOARD_KEY_M_RELEASED,             // 0xB2
    KEYBOARD_KEY_COMMA_RELEASED,         // 0xB3
    KEYBOARD_KEY_DOT_RELEASED,           // 0xB4
    KEYBOARD_KEY_SLASH_RELEASED,         // 0xB5
    KEYBOARD_KEY_RIGHT_SHIFT_RELEASED,   // 0xB6
    KEYBOARD_KEY_KP_STAR_RELEASED,       // 0xB7
    KEYBOARD_KEY_LEFT_ALT_RELEASED,      // 0xB8
    KEYBOARD_KEY_SPACE_RELEASED,         // 0xB9
    KEYBOARD_KEY_CAPSLOCK_RELEASED,      // 0xBA
    KEYBOARD_KEY_F1_RELEASED,            // 0xBB
    KEYBOARD_KEY_F2_RELEASED,            // 0xBC
    KEYBOARD_KEY_F3_RELEASED,            // 0xBD
    KEYBOARD_KEY_F4_RELEASED,            // 0xBE
    KEYBOARD_KEY_F5_RELEASED,            // 0xBF
    KEYBOARD_KEY_F6_RELEASED,            // 0xC0
    KEYBOARD_KEY_F7_RELEASED,            // 0xC1
    KEYBOARD_KEY_F8_RELEASED,            // 0xC2
    KEYBOARD_KEY_F9_RELEASED,            // 0xC3
    KEYBOARD_KEY_F10_RELEASED,           // 0xC4
    KEYBOARD_KEY_NUM_LOCK_RELEASED,      // 0xC5
    KEYBOARD_KEY_SCROLL_LOCK_RELEASED,   // 0xC6
    KEYBOARD_KEY_KP_7_RELEASED,          // 0xC7
    KEYBOARD_KEY_KP_8_RELEASED,          // 0xC8
    KEYBOARD_KEY_KP_9_RELEASED,          // 0xC9
    KEYBOARD_KEY_KP_MINUS_RELEASED,      // 0xCA
    KEYBOARD_KEY_KP_4_RELEASED,          // 0xCB
    KEYBOARD_KEY_KP_5_RELEASED,          // 0xCC
    KEYBOARD_KEY_KP_6_RELEASED,          // 0xCD
    KEYBOARD_KEY_KP_PLUS_RELEASED,       // 0xCE
    KEYBOARD_KEY_KP_1_RELEASED,          // 0xCF
    KEYBOARD_KEY_KP_2_RELEASED,          // 0xD0
    KEYBOARD_KEY_KP_3_RELEASED,          // 0xD1
    KEYBOARD_KEY_KP_0_RELEASED,          // 0xD2
    KEYBOARD_KEY_KP_DOT_RELEASED,        // 0xD3
    KEYBOARD_KEY_INVALID,                // 0xD4
    KEYBOARD_KEY_INVALID,                // 0xD5
    KEYBOARD_KEY_INVALID,                // 0xD6
    KEYBOARD_KEY_F11_RELEASED,           // 0xD7
    KEYBOARD_KEY_F12_RELEASED,           // 0xD8
    KEYBOARD_KEY_INVALID,                // 0xD9
    KEYBOARD_KEY_INVALID,                // 0xDA
    KEYBOARD_KEY_INVALID,                // 0xDB
    KEYBOARD_KEY_INVALID,                // 0xDC
    KEYBOARD_KEY_INVALID,                // 0xDD
    KEYBOARD_KEY_INVALID,                // 0xDE
    KEYBOARD_KEY_INVALID,                // 0xDF
};

uint8_t keyboard_get_scancode() {
    while (!(inb(0x64) & 1))
        asm volatile("pause");

    return inb(0x60);
}

// FIXME: Only supports basic keys
keyboard_keycode keyboard_get_keycode() {
    keyboard_keycode kc;

    uint8_t scancode = keyboard_get_scancode();

    if (scancode < 0xE0) {
        return us_qwerty_keycodes[scancode];
    }

    return KEYBOARD_KEY_INVALID;
}

keyboard_keycode keyboard_get_key() {
    keyboard_keycode kc;

    for (;;) {
        if ((kc = keyboard_get_keycode()) <= 0x127) {
            return kc;
        }
    }
}
