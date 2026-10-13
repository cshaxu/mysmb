#include "io/video.h"
#ifndef MYSMB_GAME_TEXT_SCENE_H
#define MYSMB_GAME_TEXT_SCENE_H
#include "text/background_scene.h"
#include "text/actor_scene.h"
struct mysmb_text_scene_workspace {
    struct mysmb_text_background_workspace background;
    struct mysmb_text_actor_workspace actors;
};
int mysmb_text_scene_build(const struct mysmb_game *game,
    struct mysmb_text_scene_workspace MYGAMES_KVM_FAR *workspace,
    struct mysmb_io_text_frame MYGAMES_KVM_FAR *frame);
int mysmb_text_scene_build_profile(const struct mysmb_game *game,
    struct mysmb_text_scene_workspace MYGAMES_KVM_FAR *workspace,
    struct mysmb_io_text_frame MYGAMES_KVM_FAR *frame,unsigned short rows);
#endif
