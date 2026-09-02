#ifndef CONFIG_H
#define CONFIG_H

// clang-format off

// Keys
#define KEY_QUIT          'q'
#define KEY_REPLAY        'r'
#define KEY_PAUSE         'p'
#define SEC_KEY_PAUSE     ' '     // Space
#define SK_FR_KEY         0405    // Right Arrow
#define SK_BR_KEY         0404    // Left Arrow

// Box Width & Height
#define BOX_W             80
#define BOX_H             10

// Colors (MUST FOLLOW NCURSES COLOR CODES)
#define ACCENT_COLOR_CODE 5 // Magenta
#define MUTED_COLOR_CODE  8 // Gray

#endif
