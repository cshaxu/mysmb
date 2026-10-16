/* Neutral owner-local test of the actual DOS assembly, no game resources. */
#include "platform/dos16/slot_copy.h"
#include <stdio.h>

static unsigned char far source[63488];
static unsigned char far target[61442];
static const unsigned heights[]={1U,16U,17U,32U,208U,240U};
static const unsigned widths[]={0U,1U,3U,128U,255U,256U};

int main(void)
{
    unsigned i,h,w,y,x,rows,left,right,position,cases=0U;
    unsigned char expected;
    FILE *receipt;
    for(i=0U;i<sizeof(source);++i)source[i]=(unsigned char)(i*37U+(i>>2U));
    for(h=0U;h<sizeof(heights)/sizeof(heights[0]);++h)
        for(w=0U;w<sizeof(widths)/sizeof(widths[0]);++w) {
            rows=heights[h];left=widths[w];right=256U-left;
            for(i=0U;i<sizeof(target);++i)target[i]=0xccU;
            if(!mysmb_dos16_slot_rows_copy(source+1024U,source+37U,target+1U,
                left,right,rows))return 1;
            for(y=0U;y<rows;++y)for(x=0U;x<256U;++x) {
                position=(unsigned)(y*256U+(x<left?1024U+x:37U+x-left));
                expected=(unsigned char)(position*37U+(position>>2U));
                if(target[1U+y*256U+x]!=expected)return 2;
            }
            if(target[0]!=0xccU)return 3;
            for(i=(unsigned)(rows*256U+1U);i<sizeof(target);++i)
                if(target[i]!=0xccU)return 4;
            ++cases;
        }
    for(i=0U;i<sizeof(source);++i)
        if(source[i]!=(unsigned char)(i*37U+(i>>2U)))return 5;
    /* Every invalid-argument decision has this single test owner. */
    if(mysmb_dos16_slot_rows_copy(0,source,target,1U,255U,1U) ||
       mysmb_dos16_slot_rows_copy(source,source,0,1U,255U,1U) ||
       mysmb_dos16_slot_rows_copy(source,source,target,1U,255U,0U) ||
       mysmb_dos16_slot_rows_copy(source,source,target,1U,255U,241U) ||
       mysmb_dos16_slot_rows_copy(source,source,target,257U,0U,1U) ||
       mysmb_dos16_slot_rows_copy(source,source,target,0U,257U,1U) ||
       mysmb_dos16_slot_rows_copy(source,source,target,1U,1U,1U) ||
       mysmb_dos16_slot_rows_copy(source,0,target,1U,255U,1U) ||
       mysmb_dos16_slot_rows_copy(source,source,target,65535U,257U,1U))return 6;
    if(!mysmb_dos16_slot_rows_copy(source,0,target,256U,0U,1U))return 7;
    receipt=fopen("COPY.LOG","w");if(!receipt)return 8;
    fprintf(receipt,"valid=%u invalid=9 optional_second=1 exact=1\n",cases);
    return fclose(receipt)?9:0;
}
