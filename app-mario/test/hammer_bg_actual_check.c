#include "core/objects.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>
#define RECORD_BYTES 4112U
#define CASES 5U
static int equal_ram(const unsigned char *a,const unsigned char *b){unsigned int i;for(i=0U;i<2048U;++i){if(i>=0x100U&&i<0x200U)continue;if(a[i]!=b[i])return 0;}return 1;}
int main(int argc,char **argv){static const unsigned char magic[5]={'M','S','H','B',1U};struct mysmb_game game;unsigned char head[8],rec[RECORD_BYTES];unsigned int i;FILE*f;if(argc!=2)return 64;f=fopen(argv[1],"rb");if(f==NULL)return 65;if(fread(head,1U,sizeof(head),f)!=sizeof(head)||memcmp(head,magic,sizeof(magic))!=0||head[5]!=CASES){fclose(f);return 66;}for(i=0U;i<CASES;++i){if(fread(rec,1U,sizeof(rec),f)!=sizeof(rec)||rec[0]!=0x85U||rec[1]!=0xe1U||rec[3]!=2U||rec[11]!=i||rec[12]!=1U||rec[13]!=0x80U){fclose(f);return 67;}memset(&game,0,sizeof(game));memcpy(game.ram,rec+16U,2048U);game.area_prg=mysmb_local_prg;game.area_prg_size=MYSMB_LOCAL_PRG_SIZE;mysmb_objects_step_hammer_terrain(&game,2U);if(!equal_ram(game.ram,rec+2064U)){fclose(f);return (int)(i+1U);}}fclose(f);return 0;}