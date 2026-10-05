#include "game/player.h"
#include "core/frame_root.h"
#include <stdio.h>
#include <string.h>

/* Caller-only proof. The ROM executes each real child; its observed result
 * is replayed at that declared boundary. This cannot certify a native child
 * or erase the separately retained production whole-call discrepancies. */
static unsigned char children[4][4098];
static unsigned int child_count,child_index,failures;

/* This harness enters PlayerEntrance below the GameRoutines dispatch.
 * The parent remains linked; its actual JumpEngine has separate ROM proof. */
void mysmb_game_jump_engine_state(struct mysmb_game *game,
                                 mysmb_u16 ret, mysmb_u8 selector)
{
    (void)game; (void)ret; (void)selector;
}

static void compare(const unsigned char *actual,const unsigned char *expected,
                    const char *phase)
{
    unsigned int i;
    for(i=8U;i<2048U;++i) {
        if(i>=0x100U && i<0x200U) continue;
        if(actual[i]!=expected[i]) {
            printf("%s child=%u RAM=%04x original=%02x native=%02x\n",
                   phase,child_index,i,(unsigned int)expected[i],(unsigned int)actual[i]);
            ++failures;
        }
    }
}
static void child(struct mysmb_game *game,unsigned int id,mysmb_u8 argument)
{
    unsigned char *record;
    if(child_index>=child_count) {++failures;return;}
    record=children[child_index];
    if(record[0]!=id || (id==3U && record[1]!=argument) ||
       (id==1U && record[2U+0x6fcU]!=argument)) ++failures;
    compare(game->ram,record+2U,"child-entry");
    memcpy(game->ram,record+2050U,2048U);
    ++child_index;
}
void mysmb_player_step(struct mysmb_game *game,mysmb_u8 buttons)
{child(game,1U,buttons);}
void mysmb_player_enter_side_pipe(struct mysmb_game *game)
{child(game,2U,0U);}
void mysmb_player_move_y_axis(struct mysmb_game *game,mysmb_u8 amount)
{child(game,3U,amount);}
void mysmb_game_next_area(struct mysmb_game *game)
{child(game,4U,0U);}

/* GameRoutines is linked from the same owner but is not under this check. */
#define UNUSED(name) void name(struct mysmb_game *game) {(void)game;++failures;}
UNUSED(mysmb_player_initialize_entrance)
UNUSED(mysmb_player_step_auto_climb)
UNUSED(mysmb_player_step_side_pipe)
UNUSED(mysmb_player_step_vertical_pipe)
UNUSED(mysmb_player_step_flagpole_slide)
UNUSED(mysmb_player_step_end_level)
UNUSED(mysmb_game_lose_life)
UNUSED(mysmb_player_step_change_size)
UNUSED(mysmb_player_step_death)
UNUSED(mysmb_player_step_fire_flower)
#undef UNUSED
void mysmb_player_step_injury_blink(struct mysmb_game *game,mysmb_u8 buttons)
{(void)game;(void)buttons;++failures;}

int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char header[8];
    unsigned int i;
    FILE *input;
    if(argc!=3) return 64;
    input=fopen(argv[1],"rb");if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MSEN\1\0\0\0",8)!=0 ||
       fread(game.ram,1,2048,input)!=2048 || fread(expected,1,2048,input)!=2048 ||
       fgetc(input)!=EOF) {fclose(input);return 66;}
    fclose(input);
    input=fopen(argv[2],"rb");if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MSEC\1",5)!=0 ||
       header[5]>4U || header[6]!=0U || header[7]!=0U) {fclose(input);return 66;}
    child_count=header[5];
    for(i=0U;i<child_count;++i)
        if(fread(children[i],1,4098,input)!=4098) {fclose(input);return 66;}
    if(fgetc(input)!=EOF) {fclose(input);return 66;}
    fclose(input);
    mysmb_player_finish_normal_entrance(&game);
    if(child_index!=child_count) ++failures;
    compare(game.ram,expected,"caller-return");
    return failures!=0U ? 1:0;
}
