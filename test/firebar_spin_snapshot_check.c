#include "game/enemy/firebar.h"
#include "game/objects.h"
#include "game/oam/oam.h"
#include <stdio.h>
#include <string.h>
mysmb_u8 mysmb_objects_get_enemy_offscreen_bits(const struct mysmb_game *g,mysmb_u8 s)
{ (void)g;(void)s;return 0U; }
void mysmb_oam_relative_enemy_position(struct mysmb_game *g,mysmb_u8 s)
{ (void)g;(void)s; }
static int run_file(const char *path){static struct mysmb_game g;static unsigned char record[4098];unsigned char h[8];FILE *f;unsigned int n,i,fail;mysmb_u8 slot,result;f=fopen(path,"rb");if(!f)return 65;if(fread(h,1,8,f)!=8||memcmp(h,"MShC\1",5))return fclose(f),66;fail=0U;for(n=0U;n<h[5];++n){if(fread(record,1,4098,f)!=4098)return fclose(f),66;if(record[0]!=2U)continue;memcpy(g.ram,record+2U,2048U);slot=g.ram[8U];result=mysmb_firebar_spin(&g,slot,g.ram[0x388U+slot]);if(result!=record[1])++fail;for(i=0U;i<2048U;++i)if(!(i>=0x100U&&i<0x200U&&(i<0x109U||i>0x139U))&&g.ram[i]!=record[2050U+i])++fail;}if(fgetc(f)!=EOF)return fclose(f),66;fclose(f);return fail?1:0;}
int main(int argc,char **argv){FILE*f;char line[512];unsigned int n,b;if(argc==2)return run_file(argv[1]);if(argc!=3||strcmp(argv[1],"--manifest"))return 64;f=fopen(argv[2],"rb");if(!f)return 65;n=b=0U;while(fgets(line,sizeof(line),f)){line[strcspn(line,"\r\n")]=0;++n;if(run_file(line))++b;}fclose(f);printf("firebar manifest: %u files, %u failures\n",n,b);return b?1:0;}
