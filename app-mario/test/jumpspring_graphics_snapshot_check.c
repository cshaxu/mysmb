#include "core/oam/oam.h"
#include <stdio.h>
#include <string.h>
static struct mysmb_game game;
static unsigned char record[4098];
static unsigned long address_hits[2048];
int main(int argc,char **argv)
{
    unsigned int scenario, count, index, child, slot, byte, differences;
    unsigned int cases=0U,failures=0U;
    unsigned char header[8];
    FILE *stream;
    char path[1024];
    if(argc!=2) return 64;
    for(scenario=0U;scenario<32U;++scenario) {
        if(strlen(argv[1])+32U>=sizeof(path)) return 64;
        sprintf(path,"%s/jumpspring-%u.calls",argv[1],scenario);
        stream=fopen(path,"rb");
        if(stream==NULL) return 65;
        if(fread(header,1U,8U,stream)!=8U || memcmp(header,"MSJC\1",5U)!=0) return 66;
        count=header[5];
        for(index=0U;index<count;++index) {
            if(fread(record,1U,sizeof(record),stream)!=sizeof(record)) return 66;
            child=record[0];slot=record[1];
            if(child!=3U) continue;
            ++cases;
            memset(&game,0,sizeof(game));
            memcpy(game.ram,record+2U,2048U);
            (void)mysmb_objects_draw_normal_enemy_graphics(&game,(mysmb_u8)slot);
            differences=0U;
            for(byte=0U;byte<2048U;++byte) {
                if(byte>=0x100U && byte<0x200U) continue;
                if(game.ram[byte]!=record[2050U+byte]) {
                    address_hits[byte]++;
                    ++differences;
                    if(differences<=12U) printf("case=%u slot=%u addr=%04x rom=%02x C=%02x\n",scenario,slot,byte,record[2050U+byte],game.ram[byte]);
                }
            }
            if(differences!=0U) {++failures;printf("case=%u differences=%u\n",scenario,differences);}
        }
        if(fgetc(stream)!=EOF) return 66;
        fclose(stream);
    }
    if(cases!=32U) return 67;
    printf("child comparisons=%u differing=%u\n",cases,failures);
    for(byte=0U;byte<2048U;++byte) if(address_hits[byte]!=0U)
        printf("address=%04x hits=%lu\n",byte,address_hits[byte]);
    return failures==0U?0:1;
}
