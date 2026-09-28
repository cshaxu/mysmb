#include "game/enemy/init.h"
#include "game/objects.h"
#include <string.h>
#include <stdio.h>
int main(void)
{
    static struct mysmb_game game;
    unsigned char expected[2048];
    unsigned int slot,type,status,cases,failures;
    cases=0U;failures=0U;
    for(slot=0U;slot<6U;++slot) for(type=0U;type<4U;++type)
    for(status=0U;status<3U;++status) {
        memset(&game,0xa5,sizeof(game));
        game.ram[0x16U+slot]=0x2eU;game.ram[0x39U]=(mysmb_u8)type;
        game.ram[0x756U]=(mysmb_u8)status;
        memcpy(expected,game.ram,2048U);
        /* CheckpointEnemyID reaches PwrUpJmp through the original vector. */
        expected[4U]=0x81U;expected[5U]=0xc2U;
        expected[6U]=0x60U;expected[7U]=0xbcU;
        expected[0x23U]=1U;expected[0x14U]=1U;expected[0x49fU]=3U;
        expected[0x3caU]=0x20U;expected[0xfeU]=2U;
        if(type<2U) expected[0x39U]=(mysmb_u8)(status==2U?1U:status);
        mysmb_enemy_checkpoint_loaded(&game,(mysmb_u8)slot);
        if(memcmp(game.ram,expected,2048U)!=0) ++failures;
        ++cases;
    }
    printf("%u residual initialization edges, %u failures\n",cases,failures);
    return failures?1:0;
}
