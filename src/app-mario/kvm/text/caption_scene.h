#ifndef MYSMB_GAME_TEXT_CAPTION_SCENE_H
#define MYSMB_GAME_TEXT_CAPTION_SCENE_H
#include "text/background_scene.h"
/* Read-only semantic font/title output. Reuses finished component scratch;
 * no original state,resource bytes or pixels are modified. */
unsigned short mysmb_text_caption_scene_draw(const struct mysmb_game *game,
    struct mysmb_text_background_workspace MYGAMES_KVM_FAR *workspace,
    struct mygames_kvm_text_frame MYGAMES_KVM_FAR *frame);
#endif
