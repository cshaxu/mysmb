#include "game/world/world.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>
#define RECORD_BYTES 4112U
#define CASES 5U
static unsigned int u16_at(const unsigned char *r, unsigned int offset)
{return (unsigned int)r[offset]+256U*(unsigned int)r[offset+1U];}
int main(int argc,char **argv){struct mysmb_game game;struct mysmb_enemy_terrain terrain;unsigned char head[8],rec[RECORD_BYTES];unsigned int i;mysmb_u8 got;FILE *f;if(argc!=2)return 64;f=fopen(argv[1],"rb");if(f==0)return 65;if(fread(head,1U,sizeof(head),f)!=sizeof(head)||memcmp(head,"MSHB\1",5U)!=0||head[5]!=CASES){fclose(f);return 66;}for(i=0U;i<CASES;++i){if(fread(rec,1U,sizeof(rec),f)!=sizeof(rec)||u16_at(rec,0U)!=0xe1aeU||rec[3]!=2U||rec[11]!=i||u16_at(rec,12U)!=0x8001U){fclose(f);return 67;}memset(&game,0,sizeof(game));memcpy(game.ram,rec+16U,2048U);game.area_prg=mysmb_local_prg;game.area_prg_size=MYSMB_LOCAL_PRG_SIZE;got=mysmb_world_query_enemy_under(&game,rec[3],&terrain);if(got!=rec[6]||terrain.metatile!=rec[6]||terrain.block_row_offset!=rec[2066U]||terrain.contact_low_nibble!=rec[2068U]||terrain.block_address_low!=rec[2070U]||terrain.block_address!=(mysmb_u16)(rec[2070U]+256U*rec[2071U]+rec[2066U])){printf("case=%u got=%u/%u/%u/%u/%u want=%u/%u/%u/%u/%u\n",i,got,terrain.metatile,terrain.block_row_offset,terrain.contact_low_nibble,terrain.block_address_low,rec[6],rec[6],rec[2066U],rec[2068U],rec[2070U]);fclose(f);return (int)(i+1U);}}if(fgetc(f)!=EOF){fclose(f);return 68;}fclose(f);return 0;}
