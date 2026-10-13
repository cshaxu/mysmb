#ifndef MINE_GRAPHICS_SCENE_H
#define MINE_GRAPHICS_SCENE_H
#include "../app/app.h"
#include "kvm/video.h"
int mine_graphics_width(const MineApp *app);
int mine_graphics_height(const MineApp *app);
int mine_graphics_rows(const MineApp *app,unsigned short first,unsigned short rows,
    unsigned char *pixels,unsigned short capacity,struct mygames_kvm_video_band *band);
void mine_graphics_mouse(MineApp *app,int x,int y,int buttons);
#endif
