#ifndef MYSMB_GAME_ENEMY_STREAM_H
#define MYSMB_GAME_ENEMY_STREAM_H

#include "core/area.h"

/* ROM Inc2B, shared tail of parser and HandleGroupEnemies. */
void mysmb_enemy_stream_advance_record(struct mysmb_game *game);

/* ROM $C144-$C26B ProcessEnemyData, current ObjectOffset and loop continuation. */
mysmb_u8 mysmb_enemy_stream_process_current(struct mysmb_game *game,
                                             const struct mysmb_area_source *source,
                                             mysmb_u8 slot);
mysmb_u8 mysmb_enemy_stream_process_slot(struct mysmb_game *game,
                                          const struct mysmb_area_source *source,
                                          mysmb_u8 slot);
mysmb_u8 mysmb_enemy_stream_process_next(struct mysmb_game *game,
                                          const struct mysmb_area_source *source);

#endif
