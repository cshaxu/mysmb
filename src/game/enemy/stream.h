#ifndef MYSMB_GAME_ENEMY_STREAM_H
#define MYSMB_GAME_ENEMY_STREAM_H

#include "game/area.h"

/* ROM $c0f7-$c1f4 ProcessEnemyData, called once for the current ObjectOffset. */
mysmb_u8 mysmb_enemy_stream_process_current(struct mysmb_game *game,
                                             const struct mysmb_area_source *source,
                                             mysmb_u8 slot);
mysmb_u8 mysmb_enemy_stream_process_slot(struct mysmb_game *game,
                                          const struct mysmb_area_source *source,
                                          mysmb_u8 slot);
mysmb_u8 mysmb_enemy_stream_process_next(struct mysmb_game *game,
                                          const struct mysmb_area_source *source);

#endif
