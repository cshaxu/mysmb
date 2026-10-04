#ifndef MYSMB_GAME_TEXT_ACTOR_SCENE_H
#define MYSMB_GAME_TEXT_ACTOR_SCENE_H

#include "game/game.h"
#include "game/presentation/text/elements.h"

struct mysmb_text_actor_receipt {
    mysmb_io_u16 drawn;
    mysmb_io_u16 unsupported;
    mysmb_io_u16 unowned_sprites;
};
struct mysmb_text_actor_workspace { unsigned char claimed[500]; };
/* Compose over an existing background. No clear, tick, selector or RAM write.
 * The receipt exposes missing coverage instead of substituting generic art. */
int mysmb_text_actor_scene_draw(const struct mysmb_game *game,
    struct mysmb_text_actor_workspace MYSMB_IO_FAR *workspace,
    const unsigned char MYSMB_IO_FAR *background_opaque,
    struct mysmb_io_text_frame MYSMB_IO_FAR *frame,
    struct mysmb_text_actor_receipt *receipt);

#endif
