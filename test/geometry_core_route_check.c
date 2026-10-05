#include "core/world/world.h"
#include "core/objects.h"
#include <stdio.h>
#include <string.h>
int main(int argc,char **argv)
{
    static struct mysmb_game game;
    unsigned char head[12],rec[4102];FILE *f;
    unsigned int n,a,k,first,second,passed,failures=0U;
    mysmb_u8 hit=0U;
    if(argc!=2)return 64;f=fopen(argv[1],"rb");if(f==0)return 65;
    if(fread(head,1U,sizeof(head),f)!=sizeof(head)||
       memcmp(head,"MSGE\1\0\0\0\20\51\0\0",12U)!=0)return 66;
    for(n=0U;n<10512U;++n){
        if(fread(rec,1U,sizeof(rec),f)!=sizeof(rec))return 66;
        k=rec[0];if(k!=(n<10368U?n/2592U:4U))return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,rec+6U,2048U);
        first=k==1U?rec[1]:0U;second=rec[2];
        if(k==4U){
            mysmb_world_set_bounding_box(&game,0x04acU,game.ram[0x0499U],game.ram[0x03adU],game.ram[0x03b8U]);
            mysmb_world_set_bounding_box(&game,(mysmb_u16)(0x04acU+second),game.ram[0x0499U+second/4U],game.ram[0x03aeU],game.ram[0x03b9U]);
            if(rec[2054U]!=second/4U||rec[2055U]!=game.ram[0x03aeU]||rec[2056U]!=game.ram[0x03b9U])++failures;
        }
        if(k==2U)mysmb_objects_check_hammer_collision(&game,rec[1]);
        else if(k==3U)mysmb_world_fireball_enemy_collision(&game,rec[1]);
        else {
            hit=mysmb_world_boxes_collide(&game,(mysmb_u16)(0x04acU+first),(mysmb_u16)(0x04acU+second));
            passed=game.ram[7U]==1U?0U:(game.ram[7U]==0U?1U:2U);
            if(hit!=rec[5]||rec[3]!=(mysmb_u8)(first+passed)||rec[4]!=second)++failures;
        }
        /* CPU stack is excluded. Live scratch $06/$07 is always compared.
         * Producer-only scratch $00-$02 has an explicit argument seam above. */
        for(a=0U;a<2048U;++a)if(!(a>=0x100U&&a<0x200U)&&!(k==4U&&a<3U)&&game.ram[a]!=rec[2054U+a]){
            if(failures<16U)printf("case=%u kind=%u ram=%04x ROM=%02x C=%02x\n",n,k,a,rec[2054U+a],game.ram[a]);
            ++failures;
        }
    }
    if(fgetc(f)!=EOF)return 66;fclose(f);
    printf("checked=10512 core=5184 hammer=2592 fireball=2592 box-chain=144 failures=%u\n",failures);
    return failures!=0U;
}
