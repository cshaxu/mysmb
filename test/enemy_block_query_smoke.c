#include "game/world/world.h"
int main(void) {
 struct mysmb_game game; struct mysmb_enemy_terrain terrain;
 mysmb_game_initialize_memory(&game,0U);
 game.ram[0x006eU]=1U; game.ram[0x0087U]=0xf8U; game.ram[0x00cfU]=0x40U;
 game.ram[0x0500U+0x00U+0x30U]=0x61U;
 if(mysmb_world_query_enemy_block(&game,0U,0x15U,0U,&terrain)==0U) return 1;
 if(terrain.metatile!=0x61U||terrain.contact_low_nibble!=0U||terrain.block_address_low!=0U||terrain.block_row_offset!=0x30U)return 2;
 game.ram[0x0087U]=0x20U; game.ram[0x00cfU]=0x40U; game.ram[0x05d0U+2U+0x30U]=0x62U;
 if(mysmb_world_query_enemy_block(&game,0U,0x16U,1U,&terrain)==0U||terrain.metatile!=0x62U||terrain.contact_low_nibble!=0U)return 3;
 /* VineObjectHandler uses $1b: X+$04 and Y+$10. X=$fc must carry
  * into the next page, selecting block-buffer address $0600. */
 game.ram[0x006eU]=0U; game.ram[0x0087U]=0xfcU; game.ram[0x00cfU]=0x40U;
 game.ram[0x0600U]=0x26U;
 if(mysmb_world_query_enemy_block(&game,0U,0x1bU,0U,&terrain)==0U||
    terrain.metatile!=0x26U||terrain.block_address_low!=0xd0U||
    terrain.block_row_offset!=0x30U||terrain.block_address!=0x0600U)return 4;
 return 0;
}

