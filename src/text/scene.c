#include "text/scene.h"
int mysmb_text_scene_build(const struct mysmb_game *game,
    struct mysmb_text_scene_workspace MYSMB_IO_FAR *workspace,
    struct mysmb_io_text_frame MYSMB_IO_FAR *frame)
{
    struct mysmb_text_background_receipt background;
    struct mysmb_text_actor_receipt actors;
    if(workspace==0)return 0;
    return mysmb_text_background_scene_build(game,&workspace->background,
        frame,&background) && mysmb_text_actor_scene_draw(game,&workspace->actors,
        workspace->background.opaque,frame,&actors);
}
