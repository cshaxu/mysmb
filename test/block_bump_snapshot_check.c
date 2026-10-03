#include "game/blocks/bump.h"
#include "game/objects.h"
#include "game/frame_root.h"
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
            printf("%04x original=%02x native=%02x\n",i,(unsigned int)expected[i],(unsigned int)actual[i]);
            ++failures;
        }
    }
}
#ifdef MYSMB_CALLER_CHECK
/* Caller-only boundary; real-child ROM proof uses the shared route checker. */
void mysmb_game_jump_engine_state(struct mysmb_game *g,mysmb_u16 ret,
                                  mysmb_u8 selector)
{
    unsigned int offset;
    if(ret!=0xbdbfU || selector>=9U) {++failures;return;}
    offset=(unsigned int)(ret-0x8000U)+1U+2U*selector;
    g->ram[4U]=(mysmb_u8)ret;g->ram[5U]=(mysmb_u8)(ret>>8U);
    g->ram[6U]=g->area_prg[offset];g->ram[7U]=g->area_prg[offset+1U];
}
static unsigned char children[16][4098];
static unsigned int child_count,child_calls;
static unsigned char *child(struct mysmb_game *g,unsigned int id)
{
    unsigned char *r;
    if(child_calls>=child_count) {++failures;return children[0];}
    r=children[child_calls++];
    if(r[0]!=id) ++failures;
    compare(g->ram,r+2U);memcpy(g->ram,r+2050U,2048U);return r;
}
void mysmb_blocks_check_top(struct mysmb_game *g,mysmb_u8 slot,mysmb_u8 low,mysmb_u8 row)
{
    if(low!=g->ram[6U] || row!=g->ram[2U]) ++failures;
    if(child(g,1U)[1]!=slot) ++failures;
}
void mysmb_objects_start_power_up(struct mysmb_game *g,mysmb_u8 slot)
{ if(child(g,2U)[1]!=slot) ++failures; }
void mysmb_objects_coin_block(struct mysmb_game *g,mysmb_u8 slot,mysmb_u8 carry)
{ if(carry!=0U) ++failures;if(child(g,3U)[1]!=slot) ++failures; }
void mysmb_objects_start_vine(struct mysmb_game *g,mysmb_u8 enemy,mysmb_u8 slot)
{ if(enemy!=5U || slot!=g->ram[0x3eeU]) ++failures;if(child(g,4U)[1]!=enemy) ++failures; }
#endif
#ifdef MYSMB_CHILD_DIAGNOSTIC
int main(int argc,char **argv)
{
    static struct mysmb_game g;
    static unsigned char record[4098];
    unsigned char header[8];
    unsigned int i,before;
    FILE *f;
    if(argc!=2) return 64;
    f=fopen(argv[1],"rb");if(f==NULL) return 65;
    if(fread(header,1,8,f)!=8 || memcmp(header,"MSKC\1",5)!=0 || header[5]>16U) return 66;
    for(i=0U;i<header[5];++i) {
        if(fread(record,1,4098,f)!=4098) return 66;
        memset(&g,0,sizeof(g));memcpy(g.ram,record+2U,2048U);
        g.area_prg=mysmb_local_prg;g.area_prg_size=MYSMB_LOCAL_PRG_SIZE;
        g.ppu_control_0=g.ram[0x778U];before=failures;
        switch(record[0]) {
        case 1U: mysmb_blocks_check_top(&g,record[1],g.ram[6U],g.ram[2U]);break;
        case 2U: mysmb_objects_start_power_up(&g,record[1]);break;
        case 3U: mysmb_objects_coin_block(&g,record[1],0U);break;
        case 4U: mysmb_objects_start_vine(&g,record[1],g.ram[0x3eeU]);break;
        default: return 66;
        }
        compare(g.ram,record+2050U);
        if(failures!=before) printf("child %u id %u differs\n",i,(unsigned int)record[0]);
    }
    if(fgetc(f)!=EOF) return 66;
    fclose(f);return failures?1:0;
}
#else
int main(int argc,char **argv)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    unsigned char header[8];
    FILE *f;
#ifdef MYSMB_CALLER_CHECK
    unsigned int i;
    if(argc!=3) return 64;
    f=fopen(argv[2],"rb");if(f==NULL) return 65;
    if(fread(header,1,8,f)!=8 || memcmp(header,"MSKC\1",5)!=0 || header[5]>16U) return 66;
    child_count=header[5];
    for(i=0;i<child_count;++i) if(fread(children[i],1,4098,f)!=4098) return 66;
    if(fgetc(f)!=EOF) return 66;
    fclose(f);
#else
    if(argc!=2) return 64;
#endif
    f=fopen(argv[1],"rb");if(f==NULL) return 65;
    if(fread(header,1,8,f)!=8 || memcmp(header,"MSKP\1",5)!=0) return 66;
    memset(&g,0,sizeof(g));
    if(fread(g.ram,1,2048,f)!=2048 || fread(expected,1,2048,f)!=2048 || fgetc(f)!=EOF) return 66;
    fclose(f);g.area_prg=mysmb_local_prg;g.area_prg_size=MYSMB_LOCAL_PRG_SIZE;
    g.ppu_control_0=g.ram[0x778U];
    mysmb_blocks_bump(&g,header[6]);compare(g.ram,expected);
#ifdef MYSMB_CALLER_CHECK
    if(child_calls!=child_count) ++failures;
#endif
    return failures?1:0;
}

#endif
