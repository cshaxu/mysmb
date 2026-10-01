#include "game/enemy/core.h"
#include "game/enemy/actor_slots.h"
#include "game/enemy/distance.h"
#include "game/enemy/frenzy.h"
#include "game/enemy/init_targets.h"
#include "game/enemy/init.h"
#include "game/enemy/stream.h"
#include "game/enemy/movement.h"
#include "game/objects.h"
#include <stdio.h>
#include <string.h>
static unsigned char records[16][4098];
static unsigned int count,calls,failures;
static void compare(const unsigned char *a,const unsigned char *z)
{
    unsigned int i;
    for(i=0U;i<2048U;++i) {
        if(i>=0x100U && i<0x200U && (i<0x109U || i>0x139U)) continue;
        if(a[i]!=z[i]) {
            printf("%04x original=%02x native=%02x\n",i,(unsigned int)z[i],(unsigned int)a[i]);
            ++failures;
        }
    }
}
static mysmb_u8 child(struct mysmb_game *g,unsigned int id,mysmb_u8 slot)
{
    unsigned char *r;
    if(calls>=count) { ++failures;return 0U; }
    r=records[calls++];
    if(r[0]!=id || slot!=r[2U+8U]) ++failures;
    compare(g->ram,r+2U);memcpy(g->ram,r+2050U,2048U);return r[1];
}
mysmb_u8 mysmb_enemy_player_difference(struct mysmb_game *g,mysmb_u8 slot) { return child(g,1U,slot); }
static int run_case(const char *snapshot_path,const char *calls_path){static struct mysmb_game g;static unsigned char expected[2048];unsigned char h[8];FILE *f;count=calls=failures=0U;f=fopen(calls_path,"rb");if(!f)return 65;if(fread(h,1,8,f)!=8||memcmp(h,"MSqC\1",5)||h[5]>16U)return fclose(f),66;count=h[5];if(fread(records,4098,count,f)!=count||fgetc(f)!=EOF)return fclose(f),66;fclose(f);f=fopen(snapshot_path,"rb");if(!f)return 65;if(fread(h,1,8,f)!=8||memcmp(h,"MSqP\1",5)||fread(g.ram,1,2048,f)!=2048||fread(expected,1,2048,f)!=2048||fgetc(f)!=EOF)return fclose(f),66;fclose(f);mysmb_objects_step_piranha_plants_slot(&g,h[6]);compare(g.ram,expected);if(calls!=count)++failures;return failures?1:0;}
int main(int argc,char **argv){FILE *f;char a[512],b[512],l[1100];unsigned int n,bad;if(argc==3&&strcmp(argv[1],"--manifest")!=0)return run_case(argv[1],argv[2]);if(argc!=3||strcmp(argv[1],"--manifest")!=0)return 64;f=fopen(argv[2],"rb");if(!f)return 65;n=bad=0U;while(fgets(l,sizeof(l),f)!=0){if(sscanf(l,"%511[^\t]\t%511[^\r\n]",a,b)!=2){fclose(f);return 66;}++n;if(run_case(a,b)!=0)++bad;}fclose(f);printf("piranha manifest: %u cases, %u failures\n",n,bad);return bad?1:0;}
