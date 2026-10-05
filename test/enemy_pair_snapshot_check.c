#include "core/objects.h"
#include "core/world/world.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>
static unsigned char records[64][4098];
static unsigned int count,calls,failures;
static void compare(const unsigned char *a,const unsigned char *z)
{
    unsigned int i;
    for(i=0U;i<2048U;++i) {
        if(i>=0x100U&&i<0x200U&&(i<0x109U||i>0x139U))continue;
        if(a[i]!=z[i]) {
            printf("%04x original=%02x native=%02x\n",i,(unsigned int)z[i],(unsigned int)a[i]);
            ++failures;
        }
    }
}
static mysmb_u8 child(struct mysmb_game *g,unsigned int id,mysmb_u8 slot,mysmb_u8 arg)
{
    unsigned char *r;
    if(calls>=count){++failures;return 0U;}
    r=records[calls++];
    if((r[0]&15U)!=id)++failures;
    if(id==2U || id==3U || id==4U)if(arg!=r[1])++failures;
    if(id==4U && slot!=((r[0]>>4U)&7U))++failures;
    compare(g->ram,r+2U);
    memcpy(g->ram,r+2050U,2048U);
    return id==2U?(mysmb_u8)((r[0]>>7U)&1U):r[1];
}
mysmb_u8 mysmb_world_enemy_box_offset(struct mysmb_game *g)
{ return child(g,1U,0U,0U); }
mysmb_u8 mysmb_world_boxes_collide(struct mysmb_game *g,mysmb_u16 first,mysmb_u16 second)
{
    if(first!=0x4acU+(mysmb_u8)(g->ram[1U]*4U+4U) || second<0x4acU || second>0x5abU)++failures;
    return child((struct mysmb_game *)g,2U,0U,(mysmb_u8)(second-0x4acU));
}
void mysmb_world_shell_or_block_defeat(struct mysmb_game *g,mysmb_u8 s)
{ (void)child(g,3U,s,s); }
void mysmb_objects_setup_floatey_from_relative(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 a)
{ (void)child(g,4U,s,a); }
static int run_case(const char *snapshot_path,const char *calls_path)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    unsigned char h[8];FILE *f;
    count=0U;calls=0U;failures=0U;
    f=fopen(calls_path,"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8||memcmp(h,"MS!C\1",5)||h[5]>64U)return 66;
    count=h[5];if(fread(records,4098,count,f)!=count||fgetc(f)!=EOF)return 66;
    fclose(f);f=fopen(snapshot_path,"rb");if(!f)return 65;
    if(fread(h,1,8,f)!=8||memcmp(h,"MS!P\1",5)||
        fread(g.ram,1,2048,f)!=2048||fread(expected,1,2048,f)!=2048||fgetc(f)!=EOF)return 66;
    fclose(f);g.area_prg=mysmb_local_prg;g.area_prg_size=MYSMB_LOCAL_PRG_SIZE;
    mysmb_objects_step_enemy_collisions_current(&g,h[6]);compare(g.ram,expected);
    if(calls!=count)++failures;
    return failures?1:0;
}
int main(int argc,char **argv)
{
    FILE *f;char snapshot[1024],child_path[1024];unsigned int cases,failed;
    if(argc!=3)return 64;
    if(strcmp(argv[1],"--manifest")!=0)return run_case(argv[1],argv[2]);
    f=fopen(argv[2],"rb");if(!f)return 65;
    cases=0U;failed=0U;
    while(fscanf(f,"%1023s %1023s",snapshot,child_path)==2) {
        ++cases;if(run_case(snapshot,child_path)!=0)++failed;
    }
    if(ferror(f)) { fclose(f);return 66; }
    fclose(f);printf("enemy pair manifest: %u cases, %u failures\n",cases,failed);
    return failed?1:0;
}
