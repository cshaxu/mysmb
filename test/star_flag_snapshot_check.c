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
    if(r[0]!=id || slot!=r[1]) ++failures;
    compare(g->ram,r+2U);memcpy(g->ram,r+2050U,2048U);return r[1];
}
void mysmb_oam_relative_enemy_position(struct mysmb_game *g,mysmb_u8 s) { (void)child(g,1U,s); }
void mysmb_status_apply_digit_modifier(struct mysmb_game *g,mysmb_u8 y) { (void)child(g,2U,y); }
mysmb_u8 mysmb_score_update_number(struct mysmb_game *g,mysmb_u8 a) { (void)child(g,3U,a);return g->ram[8U]; }
static int run_case(const char *snapshot_path,const char *calls_path)
{
    static struct mysmb_game g;static unsigned char expected[2048];
    unsigned char h[8];FILE *f;
    count=calls=failures=0U;
    f=fopen(calls_path,"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8 || memcmp(h,"MSpC\1",5) || h[5]>16U)return fclose(f),66;
    count=h[5];if(fread(records,4098,count,f)!=count || fgetc(f)!=EOF)return fclose(f),66;
    fclose(f);f=fopen(snapshot_path,"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8 || memcmp(h,"MSpP\1",5) || fread(g.ram,1,2048,f)!=2048 || fread(expected,1,2048,f)!=2048 || fgetc(f)!=EOF)return fclose(f),66;
    fclose(f);mysmb_objects_step_star_flags_slot(&g,h[6]);compare(g.ram,expected);if(calls!=count)++failures;return failures?1:0;
}
int main(int argc,char **argv)
{
    FILE *f;char snapshot[512],calls_path[512],line[1100];unsigned int cases,bad;
    if(argc==3 && strcmp(argv[1],"--manifest")!=0)return run_case(argv[1],argv[2]);
    if(argc!=3 || strcmp(argv[1],"--manifest")!=0)return 64;
    f=fopen(argv[2],"rb");if(!f)return 65;cases=bad=0U;
    while(fgets(line,sizeof(line),f)!=0) {if(sscanf(line,"%511[^\t]\t%511[^\r\n]",snapshot,calls_path)!=2){fclose(f);return 66;}++cases;if(run_case(snapshot,calls_path)!=0)++bad;}
    fclose(f);printf("star-flag manifest: %u cases, %u failures\n",cases,bad);return bad?1:0;
}
