#ifndef MYSMB_WIN32_KEYBOARD_H
#define MYSMB_WIN32_KEYBOARD_H
#define MYSMB_WIN32_KEY_LEFT   0x0001U
#define MYSMB_WIN32_KEY_RIGHT  0x0002U
#define MYSMB_WIN32_KEY_DOWN   0x0004U
#define MYSMB_WIN32_KEY_UP     0x0008U
#define MYSMB_WIN32_KEY_START  0x0010U
#define MYSMB_WIN32_KEY_SELECT 0x0020U
#define MYSMB_WIN32_KEY_B      0x0040U
#define MYSMB_WIN32_KEY_A      0x0080U
struct mysmb_win32_keyboard {
    unsigned char held[256],pressed[256];
};
void mysmb_win32_keyboard_reset(struct mysmb_win32_keyboard *keyboard);
void mysmb_win32_keyboard_clear_game(struct mysmb_win32_keyboard *keyboard);
/* Event returns0 for unmapped,1 for a transition,2 for a held-key repeat. */
int mysmb_win32_keyboard_event(struct mysmb_win32_keyboard *keyboard,
    unsigned short key,unsigned short scan,unsigned char down);
unsigned int mysmb_win32_keyboard_sample(struct mysmb_win32_keyboard *keyboard);
#endif
