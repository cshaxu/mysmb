#include "core/world/world.h"
#include <stdio.h>
#include <string.h>
#define CASES 8U
#define RECORD_BYTES 16U
static unsigned int u16_at(const unsigned char *r,unsigned int o){return (unsigned int)r[o]+256U*(unsigned int)r[o+1U];}
int main(int argc,char **argv){unsigned char head[8],r[RECORD_BYTES];FILE*f;unsigned int i;mysmb_u8 got,want;if(argc!=2)return 64;f=fopen(argv[1],"rb");if(f==0)return 65;if(fread(head,1U,8U,f)!=8U||memcmp(head,"MSNS\1",5U)!=0||head[5]!=CASES){fclose(f);return 66;}for(i=0U;i<CASES;++i){if(fread(r,1U,RECORD_BYTES,f)!=RECORD_BYTES||u16_at(r,0U)!=0xe1b5U||r[3]!=i||u16_at(r,10U)!=0x8001U){fclose(f);return 67;}got=mysmb_world_enemy_metatile_is_non_solid(r[2]);want=(mysmb_u8)((r[9]&2U)!=0U);if(got!=want||r[8]!=r[2]){printf("case=%u tile=%u got=%u p=%u\n",i,r[2],got,r[9]);fclose(f);return (int)(i+1U);}}if(fgetc(f)!=EOF){fclose(f);return 68;}fclose(f);return 0;}