#ifndef MYSMB_GAME_TEXT_BACKGROUND_SCENE_H
#define MYSMB_GAME_TEXT_BACKGROUND_SCENE_H

#include "core/game.h"
#include "kvm/video.h"

/* Caller-owned far storage. No ROM bytes or bitmap samples are cached. */
struct mysmb_text_background_workspace {
    unsigned char kinds[480];
    unsigned char palettes[480];
    unsigned char visited[480];
    unsigned short queue[480];
    unsigned char opaque[500];
};
struct mysmb_text_background_receipt {
    unsigned short recognized;
    unsigned short unsupported;
    unsigned short ambiguous;
    unsigned short objects;
    unsigned short letters;
};
int mysmb_text_background_scene_build(const struct mysmb_game *game,
    struct mysmb_text_background_workspace MYGAMES_KVM_FAR *workspace,
    struct mygames_kvm_text_frame MYGAMES_KVM_FAR *frame,
    struct mysmb_text_background_receipt *receipt);
int mysmb_text_background_scene_build_profile(const struct mysmb_game *game,
    struct mysmb_text_background_workspace MYGAMES_KVM_FAR *workspace,
    struct mygames_kvm_text_frame MYGAMES_KVM_FAR *frame,
    struct mysmb_text_background_receipt *receipt,unsigned short rows);

#endif
