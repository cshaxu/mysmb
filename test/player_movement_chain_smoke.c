#include "game/player.h"
#include <string.h>

static unsigned int dispatch_bad;
static unsigned int dispatch_count;
void mysmb_game_jump_engine_state(struct mysmb_game *game,
                                 mysmb_u16 ret, mysmb_u8 selector)
{
    if (ret != 0xb350U || selector != game->ram[0x001dU] ||
        game->ram[0x070bU] != 0U) ++dispatch_bad;
    ++dispatch_count;
}

static char calls[16];
static unsigned int count;
static mysmb_u8 mutate,force_seen,crouch_seen;
static void record(char c) {calls[count++]=c;calls[count]='\0';}
void mysmb_player_physics_sub(struct mysmb_game *game)
{
    record('P');crouch_seen=game->ram[0x714U];
    if(mutate==1U) game->ram[0x70bU]=1U;
    if(mutate==2U) {game->ram[0x70bU]=0U;game->ram[0x1dU]=0U;}
}
void mysmb_player_update_animation_speed(struct mysmb_game *game,mysmb_u8 buttons)
{
    (void)buttons;record('A');
    if(mutate==3U) {game->ram[0xcU]=2U;game->ram[0xceU]=0x13U;}
}
void mysmb_player_impose_friction(struct mysmb_game *game)
{record('F');force_seen=game->ram[0x709U];}
mysmb_u8 mysmb_player_move_horizontally(struct mysmb_game *game)
{
    record('H');force_seen=game->ram[0x709U];
    if(mutate==4U) game->ram[0xeU]=11U;
    return 0xfeU;
}
void mysmb_player_move_vertically(struct mysmb_game *game)
{record('V');force_seen=game->ram[0x709U];}
void mysmb_player_climb(struct mysmb_game *game) {(void)game;record('C');}

static void setup(struct mysmb_game *game)
{
    dispatch_bad = 0U;
    dispatch_count = 0U;
    memset(game->ram,0,sizeof(game->ram));count=0U;calls[0]='\0';mutate=0U;
    game->ram[0x789U]=0x5aU;game->ram[0x709U]=0x21U;game->ram[0x70aU]=0x42U;
    game->ram[0x9fU]=0xffU;game->ram[0xceU]=0x80U;game->ram[0x708U]=0x80U;
    game->ram[0x706U]=6U;game->ram[0x714U]=4U;
}
int main(void)
{
    static struct mysmb_game game;
    unsigned int size,state,flag,origin,y;
    static const char *sequence[4]={"PAFH","PHV","PHV","PC"};
    for(size=0U;size<2U;++size)
    for(state=0U;state<4U;++state)
    for(flag=0U;flag<256U;++flag) {
        setup(&game);game.ram[0x754U]=(mysmb_u8)size;game.ram[0x1dU]=(mysmb_u8)state;
        game.ram[0x70bU]=(mysmb_u8)flag;
        mysmb_player_movement_subs(&game);
        if (dispatch_bad != 0U || dispatch_count != (flag == 0U ? 1U : 0U))
            return 12;
        if(crouch_seen!=(size!=0U||state==0U?0U:4U)) return 1;
        if(strcmp(calls,flag!=0U?"P":sequence[state])!=0) return 2;
        if(game.ram[0x789U]!=(flag==0U && state!=3U?0x18U:0x5aU)) return 3;
        if(flag==0U && state!=3U && game.ram[0x6ffU]!=0xfeU) return 4;
    }
    setup(&game);mutate=1U;mysmb_player_movement_subs(&game);
    if(strcmp(calls,"P")!=0 || game.ram[0x789U]!=0x5aU) return 5;
    setup(&game);mutate=2U;game.ram[0x70bU]=1U;game.ram[0x1dU]=3U;
    mysmb_player_movement_subs(&game);if(strcmp(calls,"PAFH")!=0) return 6;
    setup(&game);mutate=3U;game.ram[0x1dU]=1U;game.ram[0x704U]=1U;
    mysmb_player_movement_subs(&game);
    if(strcmp(calls,"PAFHV")!=0 || game.ram[0x33U]!=2U || force_seen!=0x18U) return 7;
    setup(&game);game.ram[0x1dU]=2U;game.ram[0x704U]=1U;game.ram[0xceU]=0U;
    mysmb_player_movement_subs(&game);
    if(strcmp(calls,"PHV")!=0 || force_seen!=0x42U || game.ram[0x33U]!=0U) return 8;
    setup(&game);mutate=4U;game.ram[0x1dU]=1U;
    mysmb_player_movement_subs(&game);if(force_seen!=0x28U) return 9;
    for(origin=0U;origin<256U;++origin)
    for(y=0U;y<256U;++y) {
        setup(&game);game.ram[0x1dU]=1U;game.ram[0x708U]=(mysmb_u8)origin;game.ram[0xceU]=(mysmb_u8)y;
        mysmb_player_movement_subs(&game);
        if(force_seen!=(((origin+256U-y)%256U)>=6U?0x42U:0x21U)) return 10;
        setup(&game);game.ram[0x1dU]=1U;game.ram[0xaU]=0x80U;game.ram[0xdU]=0x80U;
        game.ram[0x708U]=(mysmb_u8)origin;game.ram[0xceU]=(mysmb_u8)y;
        mysmb_player_movement_subs(&game);if(force_seen!=0x21U) return 11;
    }
    return 0;
}
