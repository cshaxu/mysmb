/* Actual shared-child observer only; this file never enters a product. */
#include "core/oam/oam.h"
#include <stdio.h>
#include <string.h>
static FILE *calls;
static unsigned int failures,observed;
static unsigned char record[4098];
void __real_mysmb_oam_get_enemy_offscreen_bits(struct mysmb_game *,mysmb_u8);
int mysmb_test_offscreen_open(const char *path)
{
    unsigned char header[8];
    calls=fopen(path,"rb");
    return calls&&fread(header,1U,8U,calls)==8U&&
        memcmp(header,"MSOC\1\0\0\0",8U)==0;
}
static void compare_state(const struct mysmb_game *g,unsigned int offset,
    const char *phase)
{
    unsigned int i;
    for(i=0U;i<2048U;++i){
        /* Combined original roots reach minimum SP F2: writes F3-FF. */
        if(i>=0x1f3U&&i<=0x1ffU)continue;
        if(g->ram[i]!=record[offset+i]){
            if(failures<10U)printf("child=%u %s RAM=%04x ROM=%02x C=%02x\n",
                observed,phase,i,record[offset+i],g->ram[i]);
            ++failures;
        }
    }
}
void __wrap_mysmb_oam_get_enemy_offscreen_bits(struct mysmb_game *g,mysmb_u8 slot)
{
    if(calls){
        if(fread(record,1U,sizeof(record),calls)!=sizeof(record)){
            ++failures;printf("Unexpected native offscreen child call\n");
        }else{
            if(slot!=record[0]){++failures;printf("Original/native child slot differs\n");}
            compare_state(g,2U,"input");
            __real_mysmb_oam_get_enemy_offscreen_bits(g,slot);
            compare_state(g,2050U,"return");++observed;return;
        }
    }
    __real_mysmb_oam_get_enemy_offscreen_bits(g,slot);
}
unsigned int mysmb_test_offscreen_finish(void)
{
    if(!calls)return 0U;
    if(fgetc(calls)!=EOF){++failures;printf("Missing actual native offscreen child call\n");}
    fclose(calls);calls=0;
    printf("offscreen-child-calls=%u differences=%u\n",observed,failures);
    return failures;
}
