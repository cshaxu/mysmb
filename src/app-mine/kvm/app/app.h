#ifndef MINE_APP_H
#define MINE_APP_H
#include "../../core/mine.h"
#define MINE_LEFT 1
#define MINE_RIGHT 2
#define MINE_MIDDLE 4
typedef struct MineApp {
 Mine game;
 int buttons,gesture,chord,suppress,hover_x,hover_y,down_face;
 int level,menu,help,quit,switch_view,dirty;
 unsigned long seed;
} MineApp;
void app_init(MineApp*a,unsigned long seed);
void app_new(MineApp*a,int level);
void app_cancel(MineApp*a);
void app_mouse(MineApp*a,int x,int y,int buttons);
int app_tile(const MineApp*a,int x,int y);
void app_key(MineApp*a,int key);
#endif
