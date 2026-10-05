#include "game/player.h"
#include <stdio.h>
#include <string.h>
#ifndef MYSMB_CALLER_CHECK
#include "core/area.h"
#include "smb1_local_rom.h"
#endif

static unsigned int failures;
static void compare(const unsigned char *actual,const unsigned char *expected)
{
    unsigned int i;
    for(i=8U;i<2048U;++i) {
        if(i>=0x100U && i<0x200U) continue;
        if(actual[i]!=expected[i]) {
            printf("%04x original=%02x native=%02x\n",i,
                (unsigned int)expected[i],(unsigned int)actual[i]);
            ++failures;
        }
    }
}
#ifdef MYSMB_CALLER_CHECK
static unsigned char child_record[4098];
static unsigned int child_count,child_calls;
/* Replaying the actual ROM child result proves the caller only. */
void mysmb_player_step(struct mysmb_game *game,mysmb_u8 buttons)
{
    ++child_calls;
    if(child_count!=1U || child_calls!=1U || child_record[0]!=1U ||
       buttons!=child_record[2U+0x06fcU]) {++failures;return;}
    compare(game->ram,child_record+2U);
    memcpy(game->ram,child_record+2050U,2048U);
}
#endif

int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char header[8],kind,argument;
    FILE *input;
#ifdef MYSMB_CALLER_CHECK
    if(argc!=3) return 64;
#else
    if(argc!=2) return 64;
#endif
    input=fopen(argv[1],"rb");if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MSMP\1",5)!=0 ||
       header[5]<1U || header[5]>6U || header[7]!=0U ||
       fread(game.ram,1,2048,input)!=2048 || fread(expected,1,2048,input)!=2048 ||
       fgetc(input)!=EOF) {fclose(input);return 66;}
    fclose(input);kind=header[5];argument=header[6];
#ifdef MYSMB_CALLER_CHECK
    input=fopen(argv[2],"rb");if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MSMC\1",5)!=0 ||
       header[5]>1U || header[6]!=0U || header[7]!=0U) {fclose(input);return 66;}
    child_count=header[5];
    if(child_count!=0U && fread(child_record,1,4098,input)!=4098) {fclose(input);return 66;}
    if(fgetc(input)!=EOF) {fclose(input);return 66;}fclose(input);
#else
    mysmb_game_bind_area_source(&game,mysmb_local_prg,MYSMB_LOCAL_PRG_SIZE);
    game.ppu.ppu_control_0=game.ram[0x778U];
#endif
    switch(kind) {
    case 1U: mysmb_player_step_change_size(&game);break;
    case 2U: mysmb_player_step_injury_blink(&game,game.ram[0x6fcU]);break;
    case 3U: mysmb_player_step_death(&game);break;
    case 4U: mysmb_player_step_fire_flower(&game);break;
    case 5U: mysmb_player_cycle_palette(&game,argument);break;
    default: mysmb_player_reset_palette(&game);break;
    }
#ifdef MYSMB_CALLER_CHECK
    if(child_calls!=child_count) ++failures;
#endif
    compare(game.ram,expected);
    return failures!=0U?1:0;
}
