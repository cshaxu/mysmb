#include "game/objects.h"
#include <stdio.h>
#include <string.h>
static struct mysmb_game game;
static unsigned char expected[2048];
static unsigned int cases,failures;
static void tail_expected(unsigned int type,unsigned int status)
{
    expected[0x23U]=1U;expected[0x14U]=1U;expected[0x49fU]=3U;
    expected[0x3caU]=0x20U;expected[0xfeU]=2U;
    expected[0x39U]=(unsigned char)(type<2U?(status<2U?status:status/2U):type);
}
static void compare(void)
{
    ++cases;
    if(memcmp(game.ram,expected,sizeof(expected))!=0) ++failures;
}
int main(void)
{
    unsigned int type,status,slot,y;
    for(type=0U;type<256U;++type) for(status=0U;status<256U;++status) {
        memset(&game,0xa5,sizeof(game));
        game.ram[0x39U]=(unsigned char)type;game.ram[0x756U]=(unsigned char)status;
        memcpy(expected,game.ram,sizeof(expected));tail_expected(type,status);
        mysmb_objects_initialize_power_up(&game);compare();
    }
    for(slot=0U;slot<2U;++slot) for(y=0U;y<256U;++y)
    for(type=0U;type<4U;++type) for(status=0U;status<3U;++status) {
        memset(&game,0xa5,sizeof(game));
        game.ram[0x76U+slot]=(unsigned char)(0xffU-slot);
        game.ram[0x8fU+slot]=(unsigned char)(y^0x5aU);
        game.ram[0xd7U+slot]=(unsigned char)y;
        game.ram[0x39U]=(unsigned char)type;game.ram[0x756U]=(unsigned char)status;
        memcpy(expected,game.ram,sizeof(expected));tail_expected(type,status);
        expected[0x1bU]=0x2eU;expected[0x73U]=(unsigned char)(0xffU-slot);
        expected[0x8cU]=(unsigned char)(y^0x5aU);expected[0xbbU]=1U;
        expected[0xd4U]=(unsigned char)((y+248U)%256U);
        mysmb_objects_start_power_up(&game,(mysmb_u8)slot);compare();
    }
    printf("%u power-up initialization cases, %u failures\n",cases,failures);
    return failures?1:0;
}
