#include "core/player.h"
#include "core/frame_root.h"
#include "core/area.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>

static unsigned int failures;
static void compare(const unsigned char *actual,const unsigned char *expected)
{
    unsigned int i;
    for(i=4U;i<2048U;++i) {
        if(i>=0x100U && i<0x200U) continue;
        if(actual[i]!=expected[i]) {
            printf("%04x original=%02x native=%02x\n",i,
                (unsigned int)expected[i],(unsigned int)actual[i]);
            ++failures;
        }
    }
}
#ifdef MYSMB_CALLER_CHECK
static unsigned char children[8][4098];
static unsigned int child_count,child_calls;
static unsigned int dispatch_calls;

/* Caller diagnostic only: children use original recorded returns. This
 * observer checks the post-physics dispatch and its scratch publication;
 * it does not certify the production JumpEngine or native child bodies. */
void mysmb_game_jump_engine_state(struct mysmb_game *game,
                                 mysmb_u16 ret, mysmb_u8 selector)
{
    mysmb_u16 offset;

    ++dispatch_calls;
    if (ret != 0xb350U || selector >= 4U ||
        selector != game->ram[0x001dU] || game->ram[0x070bU] != 0U ||
        child_calls != 1U || game->area_prg == NULL ||
        game->area_prg_size < 0x3359U) {
        ++failures;
        return;
    }
    offset = (mysmb_u16)(0x3351U + (mysmb_u16)selector * 2U);
    game->ram[4U] = (mysmb_u8)ret;
    game->ram[5U] = (mysmb_u8)(ret >> 8U);
    game->ram[6U] = game->area_prg[offset];
    game->ram[7U] = game->area_prg[offset + 1U];
}
static mysmb_u8 child(struct mysmb_game *game,unsigned int id)
{
    unsigned char *record;
    if(child_calls>=child_count) {++failures;return 0U;}
    record=children[child_calls++];
    if(record[0]!=id) ++failures;
    compare(game->ram,record+2U);
    memcpy(game->ram,record+2050U,2048U);
    return record[1];
}
void mysmb_player_physics_sub(struct mysmb_game *game)
{(void)child(game,1U);}
void mysmb_player_update_animation_speed(struct mysmb_game *game,mysmb_u8 buttons)
{if(buttons!=game->ram[0x6fcU]) ++failures;(void)child(game,2U);}
void mysmb_player_impose_friction(struct mysmb_game *game)
{(void)child(game,3U);}
mysmb_u8 mysmb_player_move_horizontally(struct mysmb_game *game)
{return child(game,4U);}
void mysmb_player_move_vertically(struct mysmb_game *game)
{(void)child(game,5U);}
void mysmb_player_climb(struct mysmb_game *game)
{(void)child(game,6U);}
#endif

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
    if(fread(header,1,8,input)!=8 || memcmp(header,"MSWP\1",5)!=0 ||
       header[5]!=1U || header[7]!=0U ||
       fread(game.ram,1,2048,input)!=2048 || fread(expected,1,2048,input)!=2048 ||
       fgetc(input)!=EOF) {fclose(input);return 66;}
    fclose(input);
#ifdef MYSMB_CALLER_CHECK
    input=fopen(argv[2],"rb");if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MSWC\1",5)!=0 ||
       header[5]>8U || header[6]!=0U || header[7]!=0U) {fclose(input);return 66;}
    child_count=header[5];
    for(i=0U;i<child_count;++i)
        if(fread(children[i],1,4098,input)!=4098) {fclose(input);return 66;}
    if(fgetc(input)!=EOF) {fclose(input);return 66;}fclose(input);
#endif
    game.area_prg=mysmb_local_prg;game.area_prg_size=MYSMB_LOCAL_PRG_SIZE;
    game.ppu.ppu_control_0=game.ram[0x778U];
    mysmb_player_movement_subs(&game);
#ifdef MYSMB_CALLER_CHECK
    if(child_calls!=child_count) ++failures;
    if(child_count == 0U || dispatch_calls !=
        (children[0][2050U + 0x070bU] == 0U ? 1U : 0U)) ++failures;
#endif
    compare(game.ram,expected);
    return failures!=0U?1:0;
}
