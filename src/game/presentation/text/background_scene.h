#ifndef MYSMB_GAME_TEXT_BACKGROUND_SCENE_H
#define MYSMB_GAME_TEXT_BACKGROUND_SCENE_H

#include "game/game.h"
#include "io/video.h"

/* Caller-owned far storage. No ROM bytes or bitmap samples are cached. */
struct mysmb_text_background_workspace {
    unsigned char kinds[480];
    unsigned char palettes[480];
    unsigned char visited[480];
    unsigned short queue[480];
};
struct mysmb_text_background_receipt {
    unsigned short recognized;
    unsigned short unsupported;
    unsigned short ambiguous;
    unsigned short objects;
    unsigned short letters;
};
int mysmb_text_background_scene_build(const struct mysmb_game *game,
    struct mysmb_text_background_workspace MYSMB_IO_FAR *workspace,
    struct mysmb_io_text_frame MYSMB_IO_FAR *frame,
    struct mysmb_text_background_receipt *receipt);

#endif
