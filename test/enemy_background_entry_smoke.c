#include "game/objects.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>

/* Entry contract from EnemyToBGCollisionDet and EnemyJump. This tests
 * production children, but does not certify their complete ROM semantics. */
int main(void)
{
    static struct mysmb_game game;
    static unsigned char before[2048];
    static const unsigned char states[] = {0,1,5,0x20,0x40,0x80,0xa0,0xff};
    static const unsigned char tiles[] = {0,0x26,0xc2,0xc3,0x5f,0x60,0x51,0x23};
    unsigned int slot,id,y,state,speed,tile,wall,fall,solid,land;
    unsigned long rejected = 0UL, jumps = 0UL;

    memset(&game,0,sizeof(game));
    game.area_prg = mysmb_local_prg;
    game.area_prg_size = MYSMB_LOCAL_PRG_SIZE;
    for(slot=0;slot<6;++slot) for(id=0;id<54;++id)
    for(y=0;y<256;++y) for(state=0;state<sizeof(states);++state) {
        /* The wrapped Y gate permits exactly $06..$c1. All other
         * decisions here are from the source ID comparisons, not from
         * a copied C predicate or a production helper. */
        if((states[state]&0x20U)==0U && y>=6U && y<=193U &&
           !(id==18U && y<37U) &&
           (id<7U || id==14U || id==18U || id==46U)) continue;
        memset(game.ram,0xa5,sizeof(game.ram));
        game.ram[8]= (unsigned char)slot;
        game.ram[0x16+slot]=(unsigned char)id;
        game.ram[0x1eU + slot]=states[state];
        game.ram[0xcf+slot]=(unsigned char)y;
        memcpy(before,game.ram,sizeof(before));
        mysmb_objects_enemy_background_current(&game,(mysmb_u8)slot);
        if(memcmp(before,game.ram,sizeof(before))!=0) {
            printf("Rejected entry wrote RAM: slot=%u id=%u y=%u state=%u\n",
                   slot,id,y,(unsigned int)states[state]);
            return 1;
        }
        ++rejected;
    }
    for(slot=0;slot<6;++slot) for(speed=0;speed<256;++speed)
    for(tile=0;tile<sizeof(tiles);++tile) for(wall=0;wall<2;++wall) {
        memset(game.ram,0,sizeof(game.ram));
        game.ram[8]=(unsigned char)slot;
        game.ram[0x16+slot]=14;
        game.ram[0x87+slot]=0x40;
        game.ram[0xcf+slot]=0x6f;
        game.ram[0xa0+slot]=(unsigned char)speed;
        game.ram[0x434+slot]=0x55;
        game.ram[0x58+slot]=8;
        game.ram[0x46+slot]=1;
        /* Bottom: column 4, row $60. Side before landing: row $60;
         * side after landing: row $50. A wall below must only reverse
         * motion when the landing child has not moved the actor up. */
        game.ram[0x564]=tiles[tile];
        game.ram[0x565]=wall ? 0x51 : 0;
        fall=speed>=1U && speed<=253U;
        solid=tile>=6U;
        land=fall && solid;
        memcpy(before,game.ram,sizeof(before));
        /* The final side query selects block-buffer column 5. */
        before[6]=5;
        before[7]=5;
        if(land) {
            before[0xcf+slot]=0x68;
            before[0xa0+slot]=0xfd;
            before[0x434+slot]=0;
        }
        if(wall && !land) {
            before[0x58+slot]=0xf8;
            before[0x46+slot]=2;
        }
        mysmb_objects_enemy_background_current(&game,(mysmb_u8)slot);
        if(memcmp(before,game.ram,sizeof(before))!=0) {
            printf("Jump entry mismatch: slot=%u speed=%u tile=%u wall=%u\n",
                   slot,speed,(unsigned int)tiles[tile],wall);
            for(y=0;y<sizeof(before);++y) if(before[y]!=game.ram[y])
                printf("RAM %04x expected %02x actual %02x\n",y,
                       (unsigned int)before[y],(unsigned int)game.ram[y]);
            return 2;
        }
        ++jumps;
    }
    printf("Background entry: %lu rejected, %lu jump cases passed\n",rejected,jumps);
    return 0;
}
