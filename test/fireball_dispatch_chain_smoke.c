#include "game/fireball/fireball.h"
#include <string.h>

static unsigned int calls,failures,mutation;
static char order[24];
static mysmb_u8 slots[24];
static void record(struct mysmb_game *game,char kind,mysmb_u8 slot)
{
    if(calls>=23U) {++failures;return;}
    order[calls]=kind;slots[calls]=slot;++calls;order[calls]='\0';
    if(kind!='F' && game->ram[8U]!=slot) ++failures;
}
void mysmb_fireball_step_object(struct mysmb_game *game,mysmb_u8 slot)
{
    record(game,'F',slot);
    if(mutation!=0U) {game->ram[0x756U]=0U;game->ram[0x74eU]=0U;}
}
void mysmb_fireball_check_bubble(struct mysmb_game *game,mysmb_u8 slot)
{record(game,'B',slot);}
void mysmb_fireball_relative_bubble_position(struct mysmb_game *game,mysmb_u8 slot)
{record(game,'R',slot);}
void mysmb_fireball_get_bubble_offscreen_bits(struct mysmb_game *game,mysmb_u8 slot)
{record(game,'O',slot);}
void mysmb_fireball_draw_bubble(struct mysmb_game *game,mysmb_u8 slot)
{record(game,'D',slot);}

int main(void)
{
    static struct mysmb_game game;
    unsigned int status,y,state,crouch,input,busy,counter,timer,spawn;
    for(status=0U;status<4U;++status)
    for(y=0U;y<3U;++y)
    for(state=0U;state<4U;++state)
    for(crouch=0U;crouch<2U;++crouch)
    for(input=0U;input<4U;++input)
    for(busy=0U;busy<2U;++busy)
    for(counter=0U;counter<2U;++counter)
    for(timer=0U;timer<2U;++timer) {
        memset(game.ram,0,sizeof(game.ram));calls=0U;order[0]='\0';
        game.ram[0x756U]=(mysmb_u8)status;game.ram[0xb5U]=(mysmb_u8)y;
        game.ram[0x1dU]=(mysmb_u8)state;game.ram[0x714U]=(mysmb_u8)crouch;
        game.ram[0xaU]=(input&1U)!=0U?0x40U:0U;
        game.ram[0xdU]=(input&2U)!=0U?0x40U:0U;
        game.ram[0x6ceU]=counter!=0U?0xffU:0U;
        game.ram[0x24U+counter]=(mysmb_u8)busy;
        game.ram[0x70cU]=timer!=0U?0xffU:0U;
        game.ram[0x711U]=0xa5U;game.ram[0x781U]=0x5aU;
        game.ram[0xffU]=0x11U;game.ram[0x74eU]=1U;
        spawn=status>=2U && y==1U && state!=3U && crouch==0U && input==1U && busy==0U;
        mysmb_fireball_step(&game);
        if(strcmp(order,status>=2U?"FF":"")!=0) return 1;
        if(status>=2U && (slots[0]!=0U || slots[1]!=1U)) return 2;
        if(spawn) {
            if(game.ram[0x24U+counter]!=2U || game.ram[0xffU]!=0x20U ||
               game.ram[0x711U]!=(timer!=0U?255U:0U) ||
               game.ram[0x781U]!=(timer!=0U?254U:255U) ||
               game.ram[0x6ceU]!=(counter!=0U?0U:1U)) return 3;
        } else if(game.ram[0x24U+counter]!=busy || game.ram[0xffU]!=0x11U ||
                  game.ram[0x711U]!=0xa5U || game.ram[0x781U]!=0x5aU ||
                  game.ram[0x6ceU]!=(counter!=0U?255U:0U)) return 4;
    }
    memset(game.ram,0,sizeof(game.ram));calls=0U;order[0]='\0';
    game.ram[0x756U]=2U;game.ram[0x74eU]=1U;mutation=1U;
    mysmb_fireball_step(&game);
    if(strcmp(order,"FFBRODBRODBROD")!=0) return 5;
    for(counter=2U;counter<14U;++counter)
        if(slots[counter]!=(mysmb_u8)(2U-(counter-2U)/4U)) return 6;
    if(game.ram[8U]!=0U || failures!=0U) return 7;
    calls=0U;order[0]='\0';mutation=0U;
    mysmb_fireball_step(&game);
    if(strcmp(order,"BRODBRODBROD")!=0 || failures!=0U) return 8;
    return 0;
}
