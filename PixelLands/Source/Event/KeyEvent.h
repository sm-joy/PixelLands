#ifndef KEY_EVENT_H
#define KEY_EVENT_H

#include "Event.h"


typedef enum {
    KEY_NONE = 0,

    KEY_A = 65,
    KEY_B = 66,
    KEY_C = 67,
    KEY_D = 68,
    KEY_E = 69,
    KEY_F = 70,
    KEY_G = 71,
    KEY_H = 72,
    KEY_I = 73,
    KEY_J = 74,
    KEY_K = 75,
    KEY_L = 76,
    KEY_M = 77,
    KEY_N = 78,
    KEY_O = 79,
    KEY_P = 80,
    KEY_Q = 81,
    KEY_R = 82,
    KEY_S = 83,
    KEY_T = 84,
    KEY_U = 85,
    KEY_V = 86,
    KEY_W = 87,
    KEY_X = 88,
    KEY_Y = 89,
    KEY_Z = 90,

    KEY_0 = 48,
    KEY_1 = 49,
    KEY_2 = 50,
    KEY_3 = 51,
    KEY_4 = 52,
    KEY_5 = 53,
    KEY_6 = 54,
    KEY_7 = 55,
    KEY_8 = 56,
    KEY_9 = 57,

    KEY_UP    = 265,
    KEY_DOWN  = 264,
    KEY_LEFT  = 263,
    KEY_RIGHT = 262,

    KEY_SPACE       = 32,
    KEY_ENTER       = 257,
    KEY_ESCAPE      = 256,
    KEY_BACKSPACE   = 259,
    KEY_TAB         = 258,
    KEY_LEFT_SHIFT  = 340,
    KEY_RIGHT_SHIFT = 344,
    KEY_LEFT_CTRL   = 341,
    KEY_RIGHT_CTRL  = 345,
    KEY_LEFT_ALT    = 342,
    KEY_RIGHT_ALT   = 346,

    KEY_COMMA         = 44,
    KEY_PERIOD        = 46,
    KEY_SLASH         = 47,
    KEY_SEMICOLON     = 59,
    KEY_APOSTROPHE    = 39,
    KEY_LEFT_BRACKET  = 91,
    KEY_RIGHT_BRACKET = 93,
    KEY_BACKSLASH     = 92,
    KEY_GRAVE         = 96,
    KEY_EQUAL         = 61,
    KEY_MINUS         = 45,

    KEY_F01 = 290,
    KEY_F02 = 291,
    KEY_F03 = 292,
    KEY_F04 = 293,
    KEY_F05 = 294,
    KEY_F06 = 295,
    KEY_F07 = 296,
    KEY_F08 = 297,
    KEY_F09 = 298,
    KEY_F10 = 299,
    KEY_F11 = 300,
    KEY_F12 = 301,

    KEY_PAUSE         = 284,
    KEY_INSERT        = 260,
    KEY_HOME          = 268,
    KEY_PAGE_UP       = 266,
    KEY_DELETE        = 261,
    KEY_END           = 269,
    KEY_PAGE_DOWN     = 270,

    KEY_MAX
} KeyCode;




typedef struct {
	Event base;
	KeyCode key_code;
} KeyEvent;

typedef struct {
	KeyEvent key_base;
} KeyPressedEvent;

typedef struct {
	KeyEvent key_base;
} KeyReleasedEvent;



#endif // KEY_EVENT_H
