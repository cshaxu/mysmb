#include "game/oam/oam.h"
#include "game/objects.h"
#include "game/world/world.h"
#include "game/area.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>

static unsigned int failures;
static void compare(const unsigned char *actual,const unsigned char *expected)
{
    unsigned int i;
    for(i=8U;i<2048U;++i) {
        if(i>=0x100U && i<0x200U && (i<0x133U || i>0x139U)) continue;
        if(actual[i]!=expected[i]) {
            printf("%04x original=%02x native=%02x\n",i,
                (unsigned int)expected[i],(unsigned int)actual[i]);
            ++failures;
        }
    }
}
#ifdef MYSMB_CALLER_CHECK
static unsigned char children[16][4098];
static unsigned int child_count,child_calls;
static void child(struct mysmb_game *game,unsigned int id,mysmb_u8 slot)
{
    unsigned char *record;
    if(child_calls>=child_count) {++failures;return;}
    record=children[child_calls++];
    if(record[0]!=id || record[1]!=slot) ++failures;
    compare(game->ram,record+2U);
    memcpy(game->ram,record+2050U,2048U);
}
void mysmb_objects_give_one_coin(struct mysmb_game *g)
{child(g,1U,g->ram[8U]);}
#endif

int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char header[8];
    FILE *input;
    mysmb_u8 slot,entry,carry;
#ifdef MYSMB_CALLER_CHECK
    unsigned int i;
    if(argc!=3) return 64;
#else
    if(argc!=2) return 64;
#endif
    input=fopen(argv[1],"rb");if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MSQP\1",5)!=0 ||
       (header[5]!=1U && header[5]!=2U) || header[7]>1U ||
       fread(game.ram,1,2048,input)!=2048 || fread(expected,1,2048,input)!=2048 ||
       fgetc(input)!=EOF) {fclose(input);return 66;}
    fclose(input);
    slot=header[6];entry=header[5];carry=header[7];
#ifdef MYSMB_CALLER_CHECK
    input=fopen(argv[2],"rb");if(input==NULL) return 65;
    if(fread(header,1,8,input)!=8 || memcmp(header,"MSQC\1",5)!=0 ||
       header[5]>16U || header[6]!=0U || header[7]!=0U) {fclose(input);return 66;}
    child_count=header[5];
    for(i=0U;i<child_count;++i)
        if(fread(children[i],1,4098,input)!=4098) {fclose(input);return 66;}
    if(fgetc(input)!=EOF) {fclose(input);return 66;}fclose(input);
#endif
    game.area_prg=mysmb_local_prg;game.area_prg_size=MYSMB_LOCAL_PRG_SIZE;
    game.ppu.ppu_control_0=game.ram[0x778U];
    if(entry==1U) mysmb_objects_coin_block(&game,slot,carry);
    else mysmb_objects_setup_jump_coin(&game,slot);
#ifdef MYSMB_CALLER_CHECK
    if(child_calls!=child_count) ++failures;
#endif
    compare(game.ram,expected);
    return failures!=0U?1:0;
}
