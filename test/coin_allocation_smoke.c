#include "core/objects.h"
#include <stdio.h>
#include <string.h>

static mysmb_u8 expected[2048];
static unsigned int errors,calls;
void mysmb_objects_give_one_coin(struct mysmb_game *g)
{
    ++calls;
    if (memcmp(g->ram,expected,2048U) != 0) ++errors;
    /* The final tally must use the child's returned state, not a saved copy. */
    g->ram[0x748U] = 0xffU;
    g->ram[8U] = 4U;
}
int main(void)
{
    static struct mysmb_game g;
    unsigned int mask,carry,entry,block,value,i,slot,cases;
    mysmb_u8 result,flag;

    cases = 0U;
    for (mask = 0U; mask < 8U; ++mask)
    for (carry = 0U; carry < 2U; ++carry) {
        memset(&g,0,sizeof(g));
        for (i = 0U; i < 3U; ++i) g.ram[0x30U+i] = (mask & (1U<<i)) != 0U ? 0x80U : 0U;
        slot = (mask & 4U) == 0U ? 8U : ((mask & 2U) == 0U ? 7U : ((mask & 1U) == 0U ? 6U : 8U));
        memcpy(expected,g.ram,2048U);expected[0x6b7U]=(mysmb_u8)slot;
        flag=(mysmb_u8)carry;result=mysmb_objects_find_empty_misc_slot(&g,&flag);
        if (result!=slot || flag!=((mask&4U)!=0U?1U:carry) || memcmp(expected,g.ram,2048U)!=0) ++errors;
        ++cases;
        for (entry=0U;entry<2U;++entry)
        for (block=0U;block<2U;++block)
        for (value=0U;value<256U;++value) {
            memset(&g,0,sizeof(g));calls=0U;
            for (i=0U;i<3U;++i) g.ram[0x30U+i]=(mask&(1U<<i))!=0U?0x80U:0U;
            g.ram[0x76U+block]=0xfeU;g.ram[0x8fU+block]=(mysmb_u8)value;
            g.ram[0xd7U+block]=(mysmb_u8)value;g.ram[0x3eaU+block]=0xffU;
            g.ram[2U]=(mysmb_u8)value;g.ram[6U]=(mysmb_u8)value;
            g.ram[0x423U+slot]=0xa5U;g.ram[0x440U+slot]=0x5aU;
            g.ram[0x748U]=0x7fU;g.ram[8U]=0xfdU;
            memcpy(expected,g.ram,2048U);
            expected[0x6b7U]=(mysmb_u8)slot;expected[0x7aU+slot]=entry==0U?0xfeU:0xffU;
            expected[0x93U+slot]=(mysmb_u8)(entry==0U?(value|5U):((value*16U)|5U));
            expected[0xdbU+slot]=(mysmb_u8)(entry==0U?
                (value-17U+((mask&4U)!=0U?1U:carry)):(value+32U+((value&16U)!=0U?1U:0U)));
            expected[0xacU+slot]=0xfbU;expected[0xc2U+slot]=1U;
            expected[0x2aU+slot]=1U;expected[0xfeU]=1U;expected[8U]=(mysmb_u8)block;
            if (entry==0U) mysmb_objects_coin_block(&g,(mysmb_u8)block,(mysmb_u8)carry);
            else mysmb_objects_setup_jump_coin(&g,(mysmb_u8)block);
            expected[0x748U]=0U;expected[8U]=4U;
            if (calls!=1U || memcmp(expected,g.ram,2048U)!=0) ++errors;
            ++cases;
        }
    }
    printf("coin allocation: %u cases, %u errors\n",cases,errors);
    return errors!=0U;
}
