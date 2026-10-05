/* Neutral compositor ABI regression for the real large-model DOS compiler. */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "game/ppu_frame.h"
void mysmb_ppu_frame_reference(const struct mysmb_game *,struct mysmb_ppu_frame *);
static struct mysmb_game game,before;
static struct mysmb_ppu_frame actual,reference;
static mysmb_u8 chr[8192];
static unsigned long random_state=1UL;
static mysmb_u8 random_byte(void)
{
    random_state=random_state*1664525UL+1013904223UL;
    return (mysmb_u8)(random_state>>24U);
}
int main(void)
{
    unsigned int n,i,t;
    actual.pixels=(mysmb_u8 MYSMB_PPU_FRAME_FAR *)_fmalloc(61440U);
    reference.pixels=(mysmb_u8 MYSMB_PPU_FRAME_FAR *)_fmalloc(61440U);
    if(actual.pixels==0 || reference.pixels==0)return 1;
    memset(&game,0,sizeof(game));
    for(i=0U;i<8192U;++i)chr[i]=random_byte();
    for(n=0U;n<128U;++n) {
        game.chr_data=n%17U==0U?0:chr;
        game.chr_data_size=n%19U==0U?(mysmb_u16)(n*31U%8192U):8192U;
        for(t=0U;t<2U;++t)for(i=0U;i<1024U;++i)game.name_table[t][i]=random_byte();
        for(i=0U;i<32U;++i)game.palette[i]=random_byte();
        for(i=0U;i<256U;++i)game.visible_oam[i]=random_byte();
        game.visible_ppu_control_0=random_byte();game.visible_ppu_mask=random_byte();
        game.visible_scroll_x=random_byte();game.visible_scroll_y=random_byte();
        game.visible_ppu_name_table=random_byte();game.visible_sprite0_split=random_byte()&1U;
        before=game;
        mysmb_ppu_frame_build(&game,&actual);
        mysmb_ppu_frame_reference(&game,&reference);
        if(memcmp(&game,&before,sizeof(game)) || memcmp(actual.pixels,reference.pixels,61440U)) {
            printf("FAIL case %u\n",n);return 2;
        }
    }
    _ffree(actual.pixels);_ffree(reference.pixels);
    printf("PASS 128 full frames state unchanged\n");return 0;
}
