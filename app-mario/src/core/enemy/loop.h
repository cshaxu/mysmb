#ifndef MYSMB_GAME_ENEMY_LOOP_H
#define MYSMB_GAME_ENEMY_LOOP_H
#include "core/area.h"
void mysmb_enemy_process_loop_command(struct mysmb_game *game,
    const struct mysmb_area_source *source, mysmb_u8 slot);
void mysmb_enemy_exec_loopback(struct mysmb_game *game, mysmb_u8 index);
void mysmb_enemy_kill_all(struct mysmb_game *game);
#endif
