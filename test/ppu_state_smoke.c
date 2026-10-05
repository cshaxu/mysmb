#include "ppu/state.h"
#include <string.h>

static struct mysmb_ppu_state state,expected;
static mysmb_io_u8 source[256];

int main(void)
{
    unsigned int i,fixture;
    for(fixture=0U;fixture<128U;++fixture) {
        memset(&state,0xa5,sizeof(state));
        memcpy(&expected,&state,sizeof(state));
        for(i=0U;i<256U;++i) {
            source[i]=(mysmb_io_u8)(i*37U+fixture*13U);
            expected.visible_oam[i]=source[i];
        }
        mysmb_ppu_state_submit_oam(&state,source);
        if(memcmp(&state,&expected,sizeof(state))!=0)return 1;
        for(i=0U;i<256U;++i)
            if(source[i]!=(mysmb_io_u8)(i*37U+fixture*13U))return 2;
    }
    return 0;
}
