#include "core/enemy/movement.h"
#include "core/oam/oam.h"
#include "core/objects.h"
#include "core/world/world.h"
#include "core/area.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>

static unsigned int failures;
static void compare(const unsigned char *actual,const unsigned char *expected)
{
    unsigned int i;
    for(i=8U;i<2048U;++i) {
        if(i>=0x100U && i<0x200U && (i<0x133U || i>0x139U)) continue;
        if(actual[i]!=expected[i]) {
            printf("%04x original=%02x native=%02x\n",i,
                (unsigned int)expected[i],(unsigned int)actual[i]);
            ++failures;
        }
    }
}
#ifdef MYSMB_CALLER_CHECK
static unsigned char children[16][4098];
static unsigned int child_count,child_calls;
static void child(struct mysmb_game *game,unsigned int id,mysmb_u8 slot)
{
    unsigned char *record;
    if(child_calls>=child_count) {++failures;return;}
    record=children[child_calls++];
    if(record[0]!=id || record[1]!=slot) ++failures;
    compare(game->ram,record+2U);
    memcpy(game->ram,record+2050U,2048U);
}
void mysmb_enemy_move_jumping(struct mysmb_game *g,mysmb_u8 x) {child(g,1U,x);}
void mysmb_objects_step_enemy_jump_terrain(struct mysmb_game *g,mysmb_u8 x) {child(g,2U,x);}
void mysmb_enemy_move_normal(struct mysmb_game *g,mysmb_u8 x) {child(g,3U,x);}
void mysmb_objects_enemy_background_current(struct mysmb_game *g,mysmb_u8 x) {child(g,4U,x);}
void mysmb_oam_relative_enemy_position(struct mysmb_game *g,mysmb_u8 x) {child(g,5U,x);}
void mysmb_oam_get_enemy_offscreen_bits(struct mysmb_game *g,mysmb_u8 x)
{child(g,6U,x);}
void mysmb_objects_update_enemy_bounding_box(struct mysmb_game *g,mysmb_u8 x) {child(g,7U,x);}
void mysmb_objects_draw_power_up(struct mysmb_game *g) {child(g,8U,5U);}
void mysmb_objects_player_enemy_current(struct mysmb_game *g,mysmb_u8 x,mysmb_u8 preserve)
{if(preserve!=1U) ++failures;child(g,9U,x);}
void mysmb_objects_check_enemy_offscreen_bounds(struct mysmb_game *g,mysmb_u8 x) {child(g,10U,x);}
#endif

#ifdef MYSMB_CHILD_DIAGNOSTIC
int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char record[4098];
    unsigned char header[8];
    unsigned int i,before;
    mysmb_u8 slot;
    FILE *input;
    if(argc!=2) return 64;
    input=fopen(argv[1],"rb");if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MS7C\1",5)!=0 || header[5]>16U) return 66;
    for(i=0U;i<header[5];++i) {
        if(fread(record,1,4098,input)!=4098) return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,record+2,2048U);
        game.area_prg=mysmb_local_prg;game.area_prg_size=MYSMB_LOCAL_PRG_SIZE;
        game.ppu.ppu_control_0=game.ram[0x778U];slot=record[1];
        switch(record[0]) {
        case 1U: mysmb_enemy_move_jumping(&game,slot);break;
        case 2U: mysmb_objects_step_enemy_jump_terrain(&game,slot);break;
        case 3U: mysmb_enemy_move_normal(&game,slot);break;
        case 4U: mysmb_objects_enemy_background_current(&game,slot);break;
        case 5U: mysmb_oam_relative_enemy_position(&game,slot);break;
        case 6U: mysmb_oam_get_enemy_offscreen_bits(&game,slot);break;
        case 7U: mysmb_objects_update_enemy_bounding_box(&game,slot);break;
        case 8U: mysmb_objects_draw_power_up(&game);break;
        case 9U: mysmb_objects_player_enemy_current(&game,slot,1U);break;
        case 10U: mysmb_objects_check_enemy_offscreen_bounds(&game,slot);break;
        default: return 66;
        }
        before=failures;compare(game.ram,record+2050U);
        if(failures!=before) printf("child %u id %u differs\n",i,(unsigned int)record[0]);
    }
    if(fgetc(input)!=EOF) return 66;
    fclose(input);return failures?1:0;
}
#else
int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char header[8];
    FILE *input;
#ifdef MYSMB_CALLER_CHECK
    unsigned int i;
    if(argc!=3) return 64;
#else
    if(argc!=2) return 64;
#endif
    input=fopen(argv[1],"rb");if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MS7P\1",5)!=0 ||
       header[5]!=1U ||
       fread(game.ram,1,2048,input)!=2048 || fread(expected,1,2048,input)!=2048 ||
       fgetc(input)!=EOF) {fclose(input);return 66;}
    fclose(input);
#ifdef MYSMB_CALLER_CHECK
    input=fopen(argv[2],"rb");if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MS7C\1",5)!=0 ||
       header[5]>16U || header[6]!=0U || header[7]!=0U) {fclose(input);return 66;}
    child_count=header[5];
    for(i=0U;i<child_count;++i)
        if(fread(children[i],1,4098,input)!=4098) {fclose(input);return 66;}
    if(fgetc(input)!=EOF) {fclose(input);return 66;}fclose(input);
#endif
    game.area_prg=mysmb_local_prg;game.area_prg_size=MYSMB_LOCAL_PRG_SIZE;
    game.ppu.ppu_control_0=game.ram[0x778U];
    mysmb_objects_step_power_up(&game);
#ifdef MYSMB_CALLER_CHECK
    if(child_calls!=child_count) ++failures;
#endif
    compare(game.ram,expected);
    return failures!=0U?1:0;
}

#endif
