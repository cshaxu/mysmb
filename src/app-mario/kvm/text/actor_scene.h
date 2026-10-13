#ifndef MYSMB_GAME_TEXT_ACTOR_SCENE_H
#define MYSMB_GAME_TEXT_ACTOR_SCENE_H

#include "core/game.h"
#include "text/elements.h"

struct mysmb_text_actor_receipt {
    mygames_kvm_u16 drawn;
    mygames_kvm_u16 unsupported;
    mygames_kvm_u16 unowned_sprites;
};
struct mysmb_text_actor_workspace { unsigned char claimed[500]; };
/* Compose over an existing background. No clear, tick, selector or RAM write.
 * The receipt exposes missing coverage instead of substituting generic art. */
int mysmb_text_actor_scene_draw(const struct mysmb_game *game,
    struct mysmb_text_actor_workspace MYGAMES_KVM_FAR *workspace,
    const unsigned char MYGAMES_KVM_FAR *background_opaque,
    struct mygames_kvm_text_frame MYGAMES_KVM_FAR *frame,
    struct mysmb_text_actor_receipt *receipt);

#endif
