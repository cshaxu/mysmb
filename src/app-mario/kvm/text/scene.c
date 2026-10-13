#include "text/scene.h"
int mysmb_text_scene_build_profile(const struct mysmb_game *game,
    struct mysmb_text_scene_workspace MYGAMES_KVM_FAR *workspace,
    struct mygames_kvm_text_frame MYGAMES_KVM_FAR *frame,unsigned short rows)
{
    struct mysmb_text_background_receipt background;
    struct mysmb_text_actor_receipt actors;
    if(workspace==0)return 0;
    return mysmb_text_background_scene_build_profile(game,&workspace->background,
        frame,&background,rows) && mysmb_text_actor_scene_draw(game,&workspace->actors,
        workspace->background.opaque,frame,&actors);
}
int mysmb_text_scene_build(const struct mysmb_game *game,
    struct mysmb_text_scene_workspace MYGAMES_KVM_FAR *workspace,
    struct mygames_kvm_text_frame MYGAMES_KVM_FAR *frame)
{return mysmb_text_scene_build_profile(game,workspace,frame,50U);}
