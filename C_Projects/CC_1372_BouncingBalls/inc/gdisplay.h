// Simple Graphics API for CS1372
// George F. Riley, Georgia Tech, CS1372, Fall 2008

#ifndef __GDISPLAY_H__
#define __GDISPLAY_H__

#ifdef QT4
typedef enum {
        Key_Escape = 0x01000000,                // misc keys
        Key_Tab = 0x01000001,
        Key_Backtab = 0x01000002,
#if defined(QT3_SUPPORT) && !defined(Q_MOC_RUN)
        Key_BackTab = Key_Backtab,
#endif
        Key_Backspace = 0x01000003,
#if defined(QT3_SUPPORT) && !defined(Q_MOC_RUN)
        Key_BackSpace = Key_Backspace,
#endif
        Key_Return = 0x01000004,
        Key_Enter = 0x01000005,
        Key_Insert = 0x01000006,
        Key_Delete = 0x01000007,
        Key_Pause = 0x01000008,
        Key_Print = 0x01000009,
        Key_SysReq = 0x0100000a,
        Key_Clear = 0x0100000b,
        Key_Home = 0x01000010,                // cursor movement
        Key_End = 0x01000011,
        Key_Left = 0x01000012,
        Key_Up = 0x01000013,
        Key_Right = 0x01000014,
        Key_Down = 0x01000015,
        Key_PageUp = 0x01000016,
#if defined(QT3_SUPPORT) && !defined(Q_MOC_RUN)
        Key_Prior = Key_PageUp,
#endif
        Key_PageDown = 0x01000017,
#if defined(QT3_SUPPORT) && !defined(Q_MOC_RUN)
        Key_Next = Key_PageDown,
#endif
        Key_Shift = 0x01000020,                // modifiers
        Key_Control = 0x01000021,
        Key_Meta = 0x01000022,
        Key_Alt = 0x01000023,
        Key_CapsLock = 0x01000024,
        Key_NumLock = 0x01000025,
        Key_ScrollLock = 0x01000026,
        Key_F1 = 0x01000030,                // function keys
        Key_F2 = 0x01000031,
        Key_F3 = 0x01000032,
        Key_F4 = 0x01000033,
        Key_F5 = 0x01000034,
        Key_F6 = 0x01000035,
        Key_F7 = 0x01000036,
        Key_F8 = 0x01000037,
        Key_F9 = 0x01000038,
        Key_F10 = 0x01000039,
        Key_F11 = 0x0100003a,
        Key_F12 = 0x0100003b,
        Key_F13 = 0x0100003c,
        Key_F14 = 0x0100003d,
        Key_F15 = 0x0100003e,
        Key_F16 = 0x0100003f,
        Key_F17 = 0x01000040,
        Key_F18 = 0x01000041,
        Key_F19 = 0x01000042,
        Key_F20 = 0x01000043,
        Key_F21 = 0x01000044,
        Key_F22 = 0x01000045,
        Key_F23 = 0x01000046,
        Key_F24 = 0x01000047,
        Key_F25 = 0x01000048,                // F25 .. F35 only on X11
        Key_F26 = 0x01000049,
        Key_F27 = 0x0100004a,
        Key_F28 = 0x0100004b,
        Key_F29 = 0x0100004c,
        Key_F30 = 0x0100004d,
        Key_F31 = 0x0100004e,
        Key_F32 = 0x0100004f,
        Key_F33 = 0x01000050,
        Key_F34 = 0x01000051,
        Key_F35 = 0x01000052,
        Key_Super_L = 0x01000053,                 // extra keys
        Key_Super_R = 0x01000054,
        Key_Menu = 0x01000055,
        Key_Hyper_L = 0x01000056,
        Key_Hyper_R = 0x01000057,
        Key_Help = 0x01000058,
        Key_Direction_L = 0x01000059,
        Key_Direction_R = 0x01000060,
        Key_Space = 0x20,                // 7 bit printable ASCII
        Key_Any = Key_Space,
        Key_Exclam = 0x21,
        Key_QuoteDbl = 0x22,
        Key_NumberSign = 0x23,
        Key_Dollar = 0x24,
        Key_Percent = 0x25,
        Key_Ampersand = 0x26,
        Key_Apostrophe = 0x27,
        Key_ParenLeft = 0x28,
        Key_ParenRight = 0x29,
        Key_Asterisk = 0x2a,
        Key_Plus = 0x2b,
        Key_Comma = 0x2c,
        Key_Minus = 0x2d,
        Key_Period = 0x2e,
        Key_Slash = 0x2f,
        Key_0 = 0x30,
        Key_1 = 0x31,
        Key_2 = 0x32,
        Key_3 = 0x33,
        Key_4 = 0x34,
        Key_5 = 0x35,
        Key_6 = 0x36,
        Key_7 = 0x37,
        Key_8 = 0x38,
        Key_9 = 0x39,
        Key_Colon = 0x3a,
        Key_Semicolon = 0x3b,
        Key_Less = 0x3c,
        Key_Equal = 0x3d,
        Key_Greater = 0x3e,
        Key_Question = 0x3f,
        Key_At = 0x40,
        Key_A = 0x41,
        Key_B = 0x42,
        Key_C = 0x43,
        Key_D = 0x44,
        Key_E = 0x45,
        Key_F = 0x46,
        Key_G = 0x47,
        Key_H = 0x48,
        Key_I = 0x49,
        Key_J = 0x4a,
        Key_K = 0x4b,
        Key_L = 0x4c,
        Key_M = 0x4d,
        Key_N = 0x4e,
        Key_O = 0x4f,
        Key_P = 0x50,
        Key_Q = 0x51,
        Key_R = 0x52,
        Key_S = 0x53,
        Key_T = 0x54,
        Key_U = 0x55,
        Key_V = 0x56,
        Key_W = 0x57,
        Key_X = 0x58,
        Key_Y = 0x59,
        Key_Z = 0x5a,
        Key_BracketLeft = 0x5b,
        Key_Backslash = 0x5c,
        Key_BracketRight = 0x5d,
        Key_AsciiCircum = 0x5e,
        Key_Underscore = 0x5f,
        Key_QuoteLeft = 0x60,
        Key_BraceLeft = 0x7b,
        Key_Bar = 0x7c,
        Key_BraceRight = 0x7d,
        Key_AsciiTilde = 0x7e,

        Key_nobreakspace = 0x0a0,
        Key_exclamdown = 0x0a1,
        Key_cent = 0x0a2,
        Key_sterling = 0x0a3,
        Key_currency = 0x0a4,
        Key_yen = 0x0a5,
        Key_brokenbar = 0x0a6,
        Key_section = 0x0a7,
        Key_diaeresis = 0x0a8,
        Key_copyright = 0x0a9,
        Key_ordfeminine = 0x0aa,
        Key_guillemotleft = 0x0ab,        // left angle quotation mark
        Key_notsign = 0x0ac,
        Key_hyphen = 0x0ad,
        Key_registered = 0x0ae,
        Key_macron = 0x0af,
        Key_degree = 0x0b0,
        Key_plusminus = 0x0b1,
        Key_twosuperior = 0x0b2,
        Key_threesuperior = 0x0b3,
        Key_acute = 0x0b4,
        Key_mu = 0x0b5,
        Key_paragraph = 0x0b6,
        Key_periodcentered = 0x0b7,
        Key_cedilla = 0x0b8,
        Key_onesuperior = 0x0b9,
        Key_masculine = 0x0ba,
        Key_guillemotright = 0x0bb,        // right angle quotation mark
        Key_onequarter = 0x0bc,
        Key_onehalf = 0x0bd,
        Key_threequarters = 0x0be,
        Key_questiondown = 0x0bf,
        Key_Agrave = 0x0c0,
        Key_Aacute = 0x0c1,
        Key_Acircumflex = 0x0c2,
        Key_Atilde = 0x0c3,
        Key_Adiaeresis = 0x0c4,
        Key_Aring = 0x0c5,
        Key_AE = 0x0c6,
        Key_Ccedilla = 0x0c7,
        Key_Egrave = 0x0c8,
        Key_Eacute = 0x0c9,
        Key_Ecircumflex = 0x0ca,
        Key_Ediaeresis = 0x0cb,
        Key_Igrave = 0x0cc,
        Key_Iacute = 0x0cd,
        Key_Icircumflex = 0x0ce,
        Key_Idiaeresis = 0x0cf,
        Key_ETH = 0x0d0,
        Key_Ntilde = 0x0d1,
        Key_Ograve = 0x0d2,
        Key_Oacute = 0x0d3,
        Key_Ocircumflex = 0x0d4,
        Key_Otilde = 0x0d5,
        Key_Odiaeresis = 0x0d6,
        Key_multiply = 0x0d7,
        Key_Ooblique = 0x0d8,
        Key_Ugrave = 0x0d9,
        Key_Uacute = 0x0da,
        Key_Ucircumflex = 0x0db,
        Key_Udiaeresis = 0x0dc,
        Key_Yacute = 0x0dd,
        Key_THORN = 0x0de,
        Key_ssharp = 0x0df,
#if defined(QT3_SUPPORT) && !defined(Q_MOC_RUN)
        Key_agrave = Key_Agrave,
        Key_aacute = Key_Aacute,
        Key_acircumflex = Key_Acircumflex,
        Key_atilde = Key_Atilde,
        Key_adiaeresis = Key_Adiaeresis,
        Key_aring = Key_Aring,
        Key_ae = Key_AE,
        Key_ccedilla = Key_Ccedilla,
        Key_egrave = Key_Egrave,
        Key_eacute = Key_Eacute,
        Key_ecircumflex = Key_Ecircumflex,
        Key_ediaeresis = Key_Ediaeresis,
        Key_igrave = Key_Igrave,
        Key_iacute = Key_Iacute,
        Key_icircumflex = Key_Icircumflex,
        Key_idiaeresis = Key_Idiaeresis,
        Key_eth = Key_ETH,
        Key_ntilde = Key_Ntilde,
        Key_ograve = Key_Ograve,
        Key_oacute = Key_Oacute,
        Key_ocircumflex = Key_Ocircumflex,
        Key_otilde = Key_Otilde,
        Key_odiaeresis = Key_Odiaeresis,
#endif
        Key_division = 0x0f7,
#if defined(QT3_SUPPORT) && !defined(Q_MOC_RUN)
        Key_oslash = Key_Ooblique,
        Key_ugrave = Key_Ugrave,
        Key_uacute = Key_Uacute,
        Key_ucircumflex = Key_Ucircumflex,
        Key_udiaeresis = Key_Udiaeresis,
        Key_yacute = Key_Yacute,
        Key_thorn = Key_THORN,
#endif
        Key_ydiaeresis = 0x0ff,

        // International input method support (X keycode - 0xEE00, the
        // definition follows Qt/Embedded 2.3.7) Only interesting if
        // you are writing your own input method

        // International & multi-key character composition
        Key_AltGr               = 0x01001103,
        Key_Multi_key           = 0x01001120,  // Multi-key character compose
        Key_Codeinput           = 0x01001137,
        Key_SingleCandidate     = 0x0100113c,
        Key_MultipleCandidate   = 0x0100113d,
        Key_PreviousCandidate   = 0x0100113e,

        // Misc Functions
        Key_Mode_switch         = 0x0100117e,  // Character set switch
        //Key_script_switch       = 0x0100117e,  // Alias for mode_switch

        // Japanese keyboard support
        Key_Kanji               = 0x01001121,  // Kanji, Kanji convert
        Key_Muhenkan            = 0x01001122,  // Cancel Conversion
        //Key_Henkan_Mode         = 0x01001123,  // Start/Stop Conversion
        Key_Henkan              = 0x01001123,  // Alias for Henkan_Mode
        Key_Romaji              = 0x01001124,  // to Romaji
        Key_Hiragana            = 0x01001125,  // to Hiragana
        Key_Katakana            = 0x01001126,  // to Katakana
        Key_Hiragana_Katakana   = 0x01001127,  // Hiragana/Katakana toggle
        Key_Zenkaku             = 0x01001128,  // to Zenkaku
        Key_Hankaku             = 0x01001129,  // to Hankaku
        Key_Zenkaku_Hankaku     = 0x0100112a,  // Zenkaku/Hankaku toggle
        Key_Touroku             = 0x0100112b,  // Add to Dictionary
        Key_Massyo              = 0x0100112c,  // Delete from Dictionary
        Key_Kana_Lock           = 0x0100112d,  // Kana Lock
        Key_Kana_Shift          = 0x0100112e,  // Kana Shift
        Key_Eisu_Shift          = 0x0100112f,  // Alphanumeric Shift
        Key_Eisu_toggle         = 0x01001130,  // Alphanumeric toggle
        //Key_Kanji_Bangou        = 0x01001137,  // Codeinput
        //Key_Zen_Koho            = 0x0100113d,  // Multiple/All Candidate(s)
        //Key_Mae_Koho            = 0x0100113e,  // Previous Candidate

        // Korean keyboard support
        //
        // In fact, many Korean users need only 2 keys, Key_Hangul and
        // Key_Hangul_Hanja. But rest of the keys are good for future.

        Key_Hangul              = 0x01001131,  // Hangul start/stop(toggle)
        Key_Hangul_Start        = 0x01001132,  // Hangul start
        Key_Hangul_End          = 0x01001133,  // Hangul end, English start
        Key_Hangul_Hanja        = 0x01001134,  // Start Hangul->Hanja Conversion
        Key_Hangul_Jamo         = 0x01001135,  // Hangul Jamo mode
        Key_Hangul_Romaja       = 0x01001136,  // Hangul Romaja mode
        //Key_Hangul_Codeinput    = 0x01001137,  // Hangul code input mode
        Key_Hangul_Jeonja       = 0x01001138,  // Jeonja mode
        Key_Hangul_Banja        = 0x01001139,  // Banja mode
        Key_Hangul_PreHanja     = 0x0100113a,  // Pre Hanja conversion
        Key_Hangul_PostHanja    = 0x0100113b,  // Post Hanja conversion
        //Key_Hangul_SingleCandidate   = 0x0100113c,  // Single candidate
        //Key_Hangul_MultipleCandidate = 0x0100113d,  // Multiple candidate
        //Key_Hangul_PreviousCandidate = 0x0100113e,  // Previous candidate
        Key_Hangul_Special      = 0x0100113f,  // Special symbols
        //Key_Hangul_switch       = 0x0100117e,  // Alias for mode_switch

        // dead keys (X keycode - 0xED00 to avoid the conflict)
        Key_Dead_Grave          = 0x01001250,
        Key_Dead_Acute          = 0x01001251,
        Key_Dead_Circumflex     = 0x01001252,
        Key_Dead_Tilde          = 0x01001253,
        Key_Dead_Macron         = 0x01001254,
        Key_Dead_Breve          = 0x01001255,
        Key_Dead_Abovedot       = 0x01001256,
        Key_Dead_Diaeresis      = 0x01001257,
        Key_Dead_Abovering      = 0x01001258,
        Key_Dead_Doubleacute    = 0x01001259,
        Key_Dead_Caron          = 0x0100125a,
        Key_Dead_Cedilla        = 0x0100125b,
        Key_Dead_Ogonek         = 0x0100125c,
        Key_Dead_Iota           = 0x0100125d,
        Key_Dead_Voiced_Sound   = 0x0100125e,
        Key_Dead_Semivoiced_Sound = 0x0100125f,
        Key_Dead_Belowdot       = 0x01001260,
        Key_Dead_Hook           = 0x01001261,
        Key_Dead_Horn           = 0x01001262,

        // multimedia/internet keys - ignored by default - see QKeyEvent c'tor

        Key_Back  = 0x01000061,
        Key_Forward  = 0x01000062,
        Key_Stop  = 0x01000063,
        Key_Refresh  = 0x01000064,

        Key_VolumeDown = 0x01000070,
        Key_VolumeMute  = 0x01000071,
        Key_VolumeUp = 0x01000072,
        Key_BassBoost = 0x01000073,
        Key_BassUp = 0x01000074,
        Key_BassDown = 0x01000075,
        Key_TrebleUp = 0x01000076,
        Key_TrebleDown = 0x01000077,

        Key_MediaPlay  = 0x01000080,
        Key_MediaStop  = 0x01000081,
        Key_MediaPrevious  = 0x01000082,
#if defined(QT3_SUPPORT) && !defined(Q_MOC_RUN)
        Key_MediaPrev  = Key_MediaPrevious,
#endif
        Key_MediaNext  = 0x01000083,
        Key_MediaRecord = 0x01000084,

        Key_HomePage  = 0x01000090,
        Key_Favorites  = 0x01000091,
        Key_Search  = 0x01000092,
        Key_Standby = 0x01000093,
        Key_OpenUrl = 0x01000094,

        Key_LaunchMail  = 0x010000a0,
        Key_LaunchMedia = 0x010000a1,
        Key_Launch0  = 0x010000a2,
        Key_Launch1  = 0x010000a3,
        Key_Launch2  = 0x010000a4,
        Key_Launch3  = 0x010000a5,
        Key_Launch4  = 0x010000a6,
        Key_Launch5  = 0x010000a7,
        Key_Launch6  = 0x010000a8,
        Key_Launch7  = 0x010000a9,
        Key_Launch8  = 0x010000aa,
        Key_Launch9  = 0x010000ab,
        Key_LaunchA  = 0x010000ac,
        Key_LaunchB  = 0x010000ad,
        Key_LaunchC  = 0x010000ae,
        Key_LaunchD  = 0x010000af,
        Key_LaunchE  = 0x010000b0,
        Key_LaunchF  = 0x010000b1,

        Key_MediaLast = 0x0100ffff,

        // Keypad navigation keys
        Key_Select = 0x01010000,
        Key_Yes = 0x01010001,
        Key_No = 0x01010002,

        // Newer misc keys
        Key_Cancel  = 0x01020001,
        Key_Printer = 0x01020002,
        Key_Execute = 0x01020003,
        Key_Sleep   = 0x01020004,
        Key_Play    = 0x01020005, // Not the same as Key_MediaPlay
        Key_Zoom    = 0x01020006,
        //Key_Jisho   = 0x01020007, // IME: Dictionary key
        //Key_Oyayubi_Left = 0x01020008, // IME: Left Oyayubi key
        //Key_Oyayubi_Right = 0x01020009, // IME: Right Oyayubi key

        // Device keys
        Key_Context1 = 0x01100000,
        Key_Context2 = 0x01100001,
        Key_Context3 = 0x01100002,
        Key_Context4 = 0x01100003,
        Key_Call = 0x01100004,
        Key_Hangup = 0x01100005,
        Key_Flip = 0x01100006,

        Key_unknown = 0x01ffffff
    } Key_t;
#else
typedef enum {
  Key_Escape = 0x1000,		// misc keys
  Key_Tab = 0x1001,
  Key_Backtab = 0x1002, Key_BackTab = Key_Backtab,
  Key_Backspace = 0x1003, Key_BackSpace = Key_Backspace,
  Key_Return = 0x1004,
  Key_Enter = 0x1005,
  Key_Insert = 0x1006,
  Key_Delete = 0x1007,
  Key_Pause = 0x1008,
  Key_Print = 0x1009,
  Key_SysReq = 0x100a,
  Key_Clear = 0x100b,
  Key_Home = 0x1010,		// cursor movement
  Key_End = 0x1011,
  Key_Left = 0x1012,
  Key_Up = 0x1013,
  Key_Right = 0x1014,
  Key_Down = 0x1015,
  Key_Prior = 0x1016, Key_PageUp = Key_Prior,
  Key_Next = 0x1017, Key_PageDown = Key_Next,
  Key_Shift = 0x1020,		// modifiers
  Key_Control = 0x1021,
  Key_Meta = 0x1022,
  Key_Alt = 0x1023,
  Key_CapsLock = 0x1024,
  Key_NumLock = 0x1025,
  Key_ScrollLock = 0x1026,
  Key_F1 = 0x1030,		// function keys
  Key_F2 = 0x1031,
  Key_F3 = 0x1032,
  Key_F4 = 0x1033,
  Key_F5 = 0x1034,
  Key_F6 = 0x1035,
  Key_F7 = 0x1036,
  Key_F8 = 0x1037,
  Key_F9 = 0x1038,
  Key_F10 = 0x1039,
  Key_F11 = 0x103a,
  Key_F12 = 0x103b,
  Key_F13 = 0x103c,
  Key_F14 = 0x103d,
  Key_F15 = 0x103e,
  Key_F16 = 0x103f,
  Key_F17 = 0x1040,
  Key_F18 = 0x1041,
  Key_F19 = 0x1042,
  Key_F20 = 0x1043,
  Key_F21 = 0x1044,
  Key_F22 = 0x1045,
  Key_F23 = 0x1046,
  Key_F24 = 0x1047,
  Key_F25 = 0x1048,		// F25 .. F35 only on X11
  Key_F26 = 0x1049,
  Key_F27 = 0x104a,
  Key_F28 = 0x104b,
  Key_F29 = 0x104c,
  Key_F30 = 0x104d,
  Key_F31 = 0x104e,
  Key_F32 = 0x104f,
  Key_F33 = 0x1050,
  Key_F34 = 0x1051,
  Key_F35 = 0x1052,
  Key_Super_L = 0x1053, 		// extra keys
  Key_Super_R = 0x1054,
  Key_Menu = 0x1055,
  Key_Hyper_L = 0x1056,
  Key_Hyper_R = 0x1057,
  Key_Help = 0x1058,
  Key_Direction_L = 0x1059,
  Key_Direction_R = 0x1060,
  Key_Space = 0x20,		// 7 bit printable ASCII
  Key_Any = Key_Space,
  Key_Exclam = 0x21,
  Key_QuoteDbl = 0x22,
  Key_NumberSign = 0x23,
  Key_Dollar = 0x24,
  Key_Percent = 0x25,
  Key_Ampersand = 0x26,
  Key_Apostrophe = 0x27,
  Key_ParenLeft = 0x28,
  Key_ParenRight = 0x29,
  Key_Asterisk = 0x2a,
  Key_Plus = 0x2b,
  Key_Comma = 0x2c,
  Key_Minus = 0x2d,
  Key_Period = 0x2e,
  Key_Slash = 0x2f,
  Key_0 = 0x30,
  Key_1 = 0x31,
  Key_2 = 0x32,
  Key_3 = 0x33,
  Key_4 = 0x34,
  Key_5 = 0x35,
  Key_6 = 0x36,
  Key_7 = 0x37,
  Key_8 = 0x38,
  Key_9 = 0x39,
  Key_Colon = 0x3a,
  Key_Semicolon = 0x3b,
  Key_Less = 0x3c,
  Key_Equal = 0x3d,
  Key_Greater = 0x3e,
  Key_Question = 0x3f,
  Key_At = 0x40,
  Key_A = 0x41,
  Key_B = 0x42,
  Key_C = 0x43,
  Key_D = 0x44,
  Key_E = 0x45,
  Key_F = 0x46,
  Key_G = 0x47,
  Key_H = 0x48,
  Key_I = 0x49,
  Key_J = 0x4a,
  Key_K = 0x4b,
  Key_L = 0x4c,
  Key_M = 0x4d,
  Key_N = 0x4e,
  Key_O = 0x4f,
  Key_P = 0x50,
  Key_Q = 0x51,
  Key_R = 0x52,
  Key_S = 0x53,
  Key_T = 0x54,
  Key_U = 0x55,
  Key_V = 0x56,
  Key_W = 0x57,
  Key_X = 0x58,
  Key_Y = 0x59,
  Key_Z = 0x5a,
  Key_BracketLeft = 0x5b,
  Key_Backslash = 0x5c,
  Key_BracketRight = 0x5d,
  Key_AsciiCircum = 0x5e,
  Key_Underscore = 0x5f,
  Key_QuoteLeft = 0x60,
  Key_BraceLeft = 0x7b,
  Key_Bar = 0x7c,
  Key_BraceRight = 0x7d,
  Key_AsciiTilde = 0x7e,

  // Latin 1 codes adapted from X: keysymdef.h,v 1.21 94/08/28 16:17:06

  Key_nobreakspace = 0x0a0,
  Key_exclamdown = 0x0a1,
  Key_cent = 0x0a2,
  Key_sterling = 0x0a3,
  Key_currency = 0x0a4,
  Key_yen = 0x0a5,
  Key_brokenbar = 0x0a6,
  Key_section = 0x0a7,
  Key_diaeresis = 0x0a8,
  Key_copyright = 0x0a9,
  Key_ordfeminine = 0x0aa,
  Key_guillemotleft = 0x0ab,	// left angle quotation mark
  Key_notsign = 0x0ac,
  Key_hyphen = 0x0ad,
  Key_registered = 0x0ae,
  Key_macron = 0x0af,
  Key_degree = 0x0b0,
  Key_plusminus = 0x0b1,
  Key_twosuperior = 0x0b2,
  Key_threesuperior = 0x0b3,
  Key_acute = 0x0b4,
  Key_mu = 0x0b5,
  Key_paragraph = 0x0b6,
  Key_periodcentered = 0x0b7,
  Key_cedilla = 0x0b8,
  Key_onesuperior = 0x0b9,
  Key_masculine = 0x0ba,
  Key_guillemotright = 0x0bb,	// right angle quotation mark
  Key_onequarter = 0x0bc,
  Key_onehalf = 0x0bd,
  Key_threequarters = 0x0be,
  Key_questiondown = 0x0bf,
  Key_Agrave = 0x0c0,
  Key_Aacute = 0x0c1,
  Key_Acircumflex = 0x0c2,
  Key_Atilde = 0x0c3,
  Key_Adiaeresis = 0x0c4,
  Key_Aring = 0x0c5,
  Key_AE = 0x0c6,
  Key_Ccedilla = 0x0c7,
  Key_Egrave = 0x0c8,
  Key_Eacute = 0x0c9,
  Key_Ecircumflex = 0x0ca,
  Key_Ediaeresis = 0x0cb,
  Key_Igrave = 0x0cc,
  Key_Iacute = 0x0cd,
  Key_Icircumflex = 0x0ce,
  Key_Idiaeresis = 0x0cf,
  Key_ETH = 0x0d0,
  Key_Ntilde = 0x0d1,
  Key_Ograve = 0x0d2,
  Key_Oacute = 0x0d3,
  Key_Ocircumflex = 0x0d4,
  Key_Otilde = 0x0d5,
  Key_Odiaeresis = 0x0d6,
  Key_multiply = 0x0d7,
  Key_Ooblique = 0x0d8,
  Key_Ugrave = 0x0d9,
  Key_Uacute = 0x0da,
  Key_Ucircumflex = 0x0db,
  Key_Udiaeresis = 0x0dc,
  Key_Yacute = 0x0dd,
  Key_THORN = 0x0de,
  Key_ssharp = 0x0df,
  Key_agrave = 0x0e0,
  Key_aacute = 0x0e1,
  Key_acircumflex = 0x0e2,
  Key_atilde = 0x0e3,
  Key_adiaeresis = 0x0e4,
  Key_aring = 0x0e5,
  Key_ae = 0x0e6,
  Key_ccedilla = 0x0e7,
  Key_egrave = 0x0e8,
  Key_eacute = 0x0e9,
  Key_ecircumflex = 0x0ea,
  Key_ediaeresis = 0x0eb,
  Key_igrave = 0x0ec,
  Key_iacute = 0x0ed,
  Key_icircumflex = 0x0ee,
  Key_idiaeresis = 0x0ef,
  Key_eth = 0x0f0,
  Key_ntilde = 0x0f1,
  Key_ograve = 0x0f2,
  Key_oacute = 0x0f3,
  Key_ocircumflex = 0x0f4,
  Key_otilde = 0x0f5,
  Key_odiaeresis = 0x0f6,
  Key_division = 0x0f7,
  Key_oslash = 0x0f8,
  Key_ugrave = 0x0f9,
  Key_uacute = 0x0fa,
  Key_ucircumflex = 0x0fb,
  Key_udiaeresis = 0x0fc,
  Key_yacute = 0x0fd,
  Key_thorn = 0x0fe,
  Key_ydiaeresis = 0x0ff,

  // multimedia/internet keys - ignored by default - see QKeyEvent c'tor

  Key_Back  = 0x1061,
  Key_Forward  = 0x1062,
  Key_Stop  = 0x1063,
  Key_Refresh  = 0x1064,

  Key_VolumeDown = 0x1070,
  Key_VolumeMute  = 0x1071,
  Key_VolumeUp = 0x1072,
  Key_BassBoost = 0x1073,
  Key_BassUp = 0x1074,
  Key_BassDown = 0x1075,
  Key_TrebleUp = 0x1076,
  Key_TrebleDown = 0x1077,

  Key_MediaPlay  = 0x1080,
  Key_MediaStop  = 0x1081,
  Key_MediaPrev  = 0x1082,
  Key_MediaNext  = 0x1083,
  Key_MediaRecord = 0x1084,

  Key_HomePage  = 0x1090,
  Key_Favorites  = 0x1091,
  Key_Search  = 0x1092,
  Key_Standby = 0x1093,
  Key_OpenUrl = 0x1094,

  Key_LaunchMail  = 0x10a0,
  Key_LaunchMedia = 0x10a1,
  Key_Launch0  = 0x10a2,
  Key_Launch1  = 0x10a3,
  Key_Launch2  = 0x10a4,
  Key_Launch3  = 0x10a5,
  Key_Launch4  = 0x10a6,
  Key_Launch5  = 0x10a7,
  Key_Launch6  = 0x10a8,
  Key_Launch7  = 0x10a9,
  Key_Launch8  = 0x10aa,
  Key_Launch9  = 0x10ab,
  Key_LaunchA  = 0x10ac,
  Key_LaunchB  = 0x10ad,
  Key_LaunchC  = 0x10ae,
  Key_LaunchD  = 0x10af,
  Key_LaunchE  = 0x10b0,
  Key_LaunchF  = 0x10b1,

  Key_MediaLast = 0x1fff,

  Key_unknown = 0xffff
} Key_t;
#endif

// Define the type
typedef void* GDisplay;

// Define the GColor structure
typedef struct 
{
#ifdef MAC_OSX
  unsigned char alpha;  // The transparency
  unsigned char red;    // The green component
  unsigned char green;  // The blue component
  unsigned char blue;   // The red component 
#else
  unsigned char blue;   // The red component 
  unsigned char green;  // The blue component
  unsigned char red;    // The green component
  unsigned char alpha;  // The transparency
#endif
} GColor;

// Create a blank display of the specified width and height
GDisplay BlankDisplay(int w, int h);

// Load the specified image file and create a display window
GDisplay LoadImage(const char* fileName);

// Save the image
void SaveImage(GDisplay d, const char* fileName);

// Return the width of the image
int Width(GDisplay);

// Return the height of the image
int Height(GDisplay);

// Update the on-Screen image
void Update(GDisplay);

// Update a portion of the on-Screen image
void Update(GDisplay, int x, int y, int w, int h);

// Update a portion of the on-Screen image, but don't wait for fps timer
void UpdateNoWait(GDisplay, int x, int y, int w, int h);

// Get the image data for the display
GColor* GetImageData(GDisplay);

// Specify that the window it not visible
void Hide(GDisplay);

// Wait for the windows to close
void WaitForClose();

// Set the update rate, in frames per second
void SetUpdateRate(GDisplay g, int framesPerSecond);

// Helper function to make a RGB color element
GColor RGBColor(unsigned char red, unsigned char green, unsigned char blue);

// Query and retrieve keystrokes
bool   KeyPressed(GDisplay);   // Return true if a key has been pressed

Key_t  GetKey(GDisplay);       // Get the key value
// Define the keystroke enumerations (from Qt/qnamespaceh

void Pause(GDisplay);          // Pause the next update
#endif
