#ifndef MYSMB_PLAYER_TERRAIN_CHILDREN_H
#define MYSMB_PLAYER_TERRAIN_CHILDREN_H
#include "game/world/world.h"

/* Native terrain child interfaces; source-scoped evidence and remaining
 * dependencies are recorded in T43. Predicate returns carry consumed flags. */
mysmb_u8 mysmb_player_coin_metatile(struct mysmb_game *game, mysmb_u8 tile);
mysmb_u8 mysmb_player_handle_climbing(struct mysmb_game *game,
    const struct mysmb_player_terrain *terrain);
void mysmb_player_handle_axe_metatile(struct mysmb_game *game,
    mysmb_u8 block_low, mysmb_u8 block_row);
void mysmb_player_land_jumpspring(struct mysmb_game *game, mysmb_u8 metatile);
mysmb_u8 mysmb_player_invisible_metatile(mysmb_u8 metatile);
mysmb_u8 mysmb_player_jumpspring_metatile(mysmb_u8 metatile);
#endif
