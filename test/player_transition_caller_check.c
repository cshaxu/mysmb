#include "game/player.h"
#include "game/oam/oam.h"
#include "game/world/world.h"
#include <stdio.h>
#include <string.h>

/* Caller-only proof. The ROM executes each real child; its observed result
 * is replayed at that declared boundary. This cannot certify a native child
 * or erase the separately retained production whole-call discrepancies. */
static unsigned char children[4][4098];
static unsigned int child_count,child_index,failures;

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
    if(record[0]!=id || (id==1U && record[1]!=argument)) ++failures;
    compare(game->ram,record+2U,"child-entry");
    memcpy(game->ram,record+2050U,2048U);
    ++child_index;
}
void mysmb_player_auto_control(struct mysmb_game *game,mysmb_u8 buttons)
{child(game,1U,buttons);}
void mysmb_player_update_scroll(struct mysmb_game *game)
{child(game,2U,0U);}

int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char header[8];
    unsigned char root_kind,move_argument;
    unsigned int i;
    FILE *input;
    if(argc!=3) return 64;
    input=fopen(argv[1],"rb");if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MSTP\1",5)!=0 || header[5]<1U || header[5]>4U || header[7]!=0U ||
       fread(game.ram,1,2048,input)!=2048 || fread(expected,1,2048,input)!=2048 ||
       fgetc(input)!=EOF) {fclose(input);return 66;}
    root_kind=header[5];move_argument=header[6];
    fclose(input);
    input=fopen(argv[2],"rb");if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MSTC\1",5)!=0 ||
       header[5]>4U || header[6]!=0U || header[7]!=0U) {fclose(input);return 66;}
    child_count=header[5];
    for(i=0U;i<child_count;++i)
        if(fread(children[i],1,4098,input)!=4098) {fclose(input);return 66;}
    if(fgetc(input)!=EOF) {fclose(input);return 66;}
    fclose(input);
    switch(root_kind) {
    case 1U: mysmb_player_step_auto_climb(&game); break;
    case 2U: mysmb_player_step_side_pipe(&game); break;
    case 3U: mysmb_player_step_vertical_pipe(&game); break;
    default: mysmb_player_move_y_axis(&game,move_argument); break;
    }
    if(child_index!=child_count) ++failures;
    compare(game.ram,expected,"caller-return");
    return failures!=0U ? 1:0;
}
