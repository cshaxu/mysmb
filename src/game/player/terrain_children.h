#ifndef MYSMB_PLAYER_TERRAIN_CHILDREN_H
#define MYSMB_PLAYER_TERRAIN_CHILDREN_H
#include "game/world/world.h"

/* Existing child bodies remain separately owned by T43 S2/S3/S4/S7.
 * These native metadata seams will be compared with their ROM call inputs. */
mysmb_u8 mysmb_player_coin_metatile(struct mysmb_game *game, mysmb_u8 tile);
mysmb_u8 mysmb_player_handle_climbing(struct mysmb_game *game,
    const struct mysmb_player_terrain *terrain);
void mysmb_player_handle_axe_metatile(struct mysmb_game *game,
    mysmb_u8 block_low, mysmb_u8 block_row);
void mysmb_player_land_jumpspring(struct mysmb_game *game, mysmb_u8 metatile);
#endif
