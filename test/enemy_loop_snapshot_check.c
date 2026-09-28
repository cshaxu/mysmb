#include "game/enemy/loop.h"
#include "game/enemy/core.h"
#include "game/enemy/actor_slots.h"
#include "game/objects.h"
#include "game/enemy/stream.h"
#include "game/enemy/init.h"
#include <stdio.h>
#include <string.h>

/* Original children are substituted only after their full entry comparison.
 * This proves the loop caller; it does not credit parser/initializer bodies. */
static unsigned char records[2][4098];
static unsigned int count,calls,failures;
static void compare(const unsigned char *actual,const unsigned char *expected)
{
    unsigned int i;
    for(i=0U;i<2048U;++i) {
        if(i>=0x100U && i<0x200U && (i<0x133U || i>0x139U)) continue;
        if(actual[i]!=expected[i]) {
            printf("%04x original=%02x native=%02x\n",i,
                (unsigned int)expected[i],(unsigned int)actual[i]);
            ++failures;
        }
    }
}
static void child(struct mysmb_game *game,mysmb_u8 id,mysmb_u8 slot)
{
    unsigned char *record;
    if(calls>=count) { ++failures;return; }
    record=records[calls++];
    if(record[0]!=id || record[1]!=slot) ++failures;
    compare(game->ram,record+2U);
    memcpy(game->ram,record+2050U,2048U);
}
mysmb_u8 mysmb_enemy_stream_process_current(struct mysmb_game *game,
    const struct mysmb_area_source *source,mysmb_u8 slot)
{ (void)source;child(game,1U,slot);return 0U; }
void mysmb_enemy_checkpoint_loaded(struct mysmb_game *game,mysmb_u8 slot)
{ child(game,2U,slot); }

/* Live-slot fixtures select source NoRunCode, so actor bodies must not run. */
#define UNEXPECTED(name) \
void name(struct mysmb_game *game,mysmb_u8 slot) \
{ (void)game;(void)slot;++failures; }
UNEXPECTED(mysmb_objects_step_normal_enemy)
UNEXPECTED(mysmb_objects_step_bowser_flames_slot)
UNEXPECTED(mysmb_objects_step_fireworks_slot)
UNEXPECTED(mysmb_objects_step_platforms_slot)
UNEXPECTED(mysmb_objects_step_bowsers_slot)
UNEXPECTED(mysmb_objects_draw_bowsers_slot)
UNEXPECTED(mysmb_objects_step_star_flags_slot)
UNEXPECTED(mysmb_objects_step_jumpspring)
UNEXPECTED(mysmb_objects_draw_retainer)
UNEXPECTED(mysmb_objects_step_vine)
#undef UNEXPECTED
mysmb_u8 mysmb_objects_step_firebars_slot(struct mysmb_game *game,mysmb_u8 slot)
{ (void)game;(void)slot;++failures;return 0U; }
void mysmb_objects_step_power_up(struct mysmb_game *game)
{ (void)game;++failures; }

int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char header[8];
    FILE *file;
    if(argc!=3) return 64;
    file=fopen(argv[2],"rb");if(file==NULL) return 65;
    if(fread(header,1,8,file)!=8 || memcmp(header,"MSEC\1",5)!=0 || header[5]>2U) return 66;
    count=header[5];
    if(fread(records,4098,count,file)!=count || fgetc(file)!=EOF) return 66;
    fclose(file);
    file=fopen(argv[1],"rb");if(file==NULL) return 65;
    if(fread(header,1,8,file)!=8 || memcmp(header,"MSEP\1",5)!=0 || header[6]!=0U) return 66;
    if(fread(game.ram,1,2048,file)!=2048 || fread(expected,1,2048,file)!=2048 || fgetc(file)!=EOF) return 66;
    fclose(file);
    if(count==1U && records[0][0]==3U) {
        if(records[0][1]!=0U || game.ram[0x16U]!=0x33U) return 67;
        compare(game.ram,records[0]+2U);
        calls=1U;
    }
    mysmb_enemy_core_step_slot(&game,0,header[6]);
    if(count==1U && records[0][0]==3U) compare(game.ram,records[0]+2050U);
    compare(game.ram,expected);
    if(calls!=count) ++failures;
    return failures?1:0;
}
