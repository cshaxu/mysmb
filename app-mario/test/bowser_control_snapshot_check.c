#include "core/enemy/core.h"
#include "core/enemy/actor_slots.h"
#include "core/enemy/distance.h"
#include "core/enemy/frenzy.h"
#include "core/enemy/init_targets.h"
#include "core/enemy/init.h"
#include "core/enemy/stream.h"
#include "core/enemy/movement.h"
#include "core/objects.h"
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
    if(r[0]!=id || (id!=4U && id!=7U && slot!=r[1])) ++failures;
    if(id==4U && slot!=g->ram[8U]) ++failures;
    compare(g->ram,r+2U);memcpy(g->ram,r+2050U,2048U);return r[1];
}
void mysmb_objects_erase_enemy(struct mysmb_game *g,mysmb_u8 s) { (void)child(g,1U,s); }
void mysmb_enemy_move_slow_vertically(struct mysmb_game *g,mysmb_u8 s) { (void)child(g,2U,s); }
void mysmb_objects_draw_bowsers_slot(struct mysmb_game *g,mysmb_u8 s) { (void)child(g,3U,s); }
mysmb_u8 mysmb_enemy_player_difference(struct mysmb_game *g,mysmb_u8 s) { return child(g,4U,s); }
mysmb_u8 mysmb_objects_spawn_hammer(struct mysmb_game *g) { (void)child(g,5U,g->ram[8U]);return 0U; }
void mysmb_enemy_init_vertical_state(struct mysmb_game *g,mysmb_u8 s) { (void)child(g,6U,s); }
mysmb_u8 mysmb_enemy_set_flame_timer(struct mysmb_game *g) { return child(g,7U,0U); }
/* Unused entries in the shared bridge/loop owners must never be reached. */
void mysmb_area_rem_bridge(struct mysmb_game *g,mysmb_u8 a,mysmb_u8 b,mysmb_u8 c,mysmb_u8 d)
{ (void)g;(void)a;(void)b;(void)c;(void)d;++failures; }
void mysmb_area_move_v_offset(struct mysmb_game *g,mysmb_u8 y) { (void)g;(void)y;++failures; }
void mysmb_enemy_checkpoint_loaded(struct mysmb_game *g,mysmb_u8 s) { (void)g;(void)s;++failures; }
mysmb_u8 mysmb_enemy_stream_process_current(struct mysmb_game *g,const struct mysmb_area_source *src,mysmb_u8 s)
{ (void)g;(void)src;(void)s;++failures;return 0U; }
static int run_case(const char *snapshot_path,const char *calls_path)
{
    static struct mysmb_game g;static unsigned char expected[2048];
    unsigned char h[8];FILE *f;
    count=calls=failures=0U;
    f=fopen(calls_path,"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8 || memcmp(h,"MSlC\1",5) || h[5]>16U)return 66;
    count=h[5];if(fread(records,4098,count,f)!=count || fgetc(f)!=EOF)return 66;
    fclose(f);f=fopen(snapshot_path,"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8 || memcmp(h,"MSlP\1",5) ||
        fread(g.ram,1,2048,f)!=2048 || fread(expected,1,2048,f)!=2048 || fgetc(f)!=EOF)return 66;
    fclose(f);mysmb_enemy_run_bowser(&g,h[6]);compare(g.ram,expected);
    if(calls!=count)++failures;
    return failures?1:0;
}

int main(int argc,char **argv)
{
    FILE *manifest;
    char line[1024],*separator;
    unsigned int cases,failed;
    int result;
    if(argc==3 && strcmp(argv[1],"--manifest")!=0)
        return run_case(argv[1],argv[2]);
    if(argc!=3 || strcmp(argv[1],"--manifest")!=0)return 64;
    manifest=fopen(argv[2],"r");if(!manifest)return 65;
    cases=failed=0U;
    while(fgets(line,sizeof(line),manifest)!=0) {
        separator=strchr(line,'\t');
        if(separator==0) { fclose(manifest);return 66; }
        *separator++='\0';
        separator[strcspn(separator,"\r\n")]='\0';
        if(line[0]=='\0' || separator[0]=='\0') { fclose(manifest);return 66; }
        result=run_case(line,separator);
        ++cases;
        if(result!=0) { ++failed;printf("case %u failed (%d)\n",cases-1U,result); }
    }
    fclose(manifest);
    printf("bowser manifest: %u cases, %u failures\n",cases,failed);
    return failed==0U?0:1;
}
