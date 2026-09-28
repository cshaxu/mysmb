#include "game/player.h"
#include "game/oam/oam.h"
#include "game/world/world.h"
#include <stdio.h>
#include <string.h>

/* Caller-only proof. The ROM executes each real child; its observed result
 * is replayed at that declared boundary. This cannot certify a native child
 * or erase the separately retained production whole-call discrepancies. */
static unsigned char children[8][4098];
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
    if(record[0]!=id) ++failures;
    (void)argument;
    compare(game->ram,record+2U,"child-entry");
    memcpy(game->ram,record+2050U,2048U);
    ++child_index;
}
void mysmb_player_movement_subs(struct mysmb_game *game)
{child(game,1U,0U);}
void mysmb_player_update_scroll(struct mysmb_game *game)
{child(game,2U,0U);}
void mysmb_oam_get_player_offscreen_bits(struct mysmb_game *game)
{child(game,3U,0U);}
void mysmb_oam_relative_player_position(struct mysmb_game *game)
{child(game,4U,0U);}
void mysmb_world_set_bounding_box(struct mysmb_game *game,mysmb_u16 address,
                                 mysmb_u8 control,mysmb_u8 x,mysmb_u8 y)
{
    if(address!=0x4acU || control!=game->ram[0x499U] ||
       x!=game->ram[0x3adU] || y!=game->ram[0x3b8U] ||
       child_index>=child_count || children[child_index][1]!=0U) ++failures;
    child(game,5U,0U);
}
void mysmb_player_background_collision(struct mysmb_game *game)
{child(game,6U,0U);}
void mysmb_player_set_entrance(struct mysmb_game *game)
{child(game,7U,0U);}

int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char header[8];
    unsigned int i;
    FILE *input;
    if(argc!=3) return 64;
    input=fopen(argv[1],"rb");if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MSPC\1\0\0\0",8)!=0 ||
       fread(game.ram,1,2048,input)!=2048 || fread(expected,1,2048,input)!=2048 ||
       fgetc(input)!=EOF) {fclose(input);return 66;}
    fclose(input);
    input=fopen(argv[2],"rb");if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MSPC\1",5)!=0 ||
       header[5]>8U || header[6]!=0U || header[7]!=0U) {fclose(input);return 66;}
    child_count=header[5];
    for(i=0U;i<child_count;++i)
        if(fread(children[i],1,4098,input)!=4098) {fclose(input);return 66;}
    if(fgetc(input)!=EOF) {fclose(input);return 66;}
    fclose(input);
    mysmb_player_step(&game,game.ram[0x6fcU]);
    if(child_index!=child_count) ++failures;
    compare(game.ram,expected,"caller-return");
    return failures!=0U ? 1:0;
}
