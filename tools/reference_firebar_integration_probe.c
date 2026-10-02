/* Actual Firebar position, OAM and injury returns, without child substitution. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 512u
#define LIMIT 524288u
static int ready(core_machine *machine)
{
    core_run_result result;unsigned int n;
    for(n=0u;n<LIMIT;++n){
        if(machine->pc==0x8181u)return 1;
        if(core_machine_debug_step(machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid)return 0;
    }
    return 0;
}
int main(int argc,char **argv)
{
    static core_machine baseline;
    static const unsigned char xs[8]={0u,0x10u,0x70u,0x80u,0x90u,0xe0u,0xf8u,0xffu};
    static const unsigned char ys[8]={0x20u,0x60u,0x80u,0x90u,0xf0u,0xf8u,8u,0xffu};
    unsigned char header[12]={'M','S','F','I',1u,0u,0u,0u,0u,2u,0u,0u};
    unsigned char record[4100],slot,oam=0u,draw_x=0u,loop=0u,guard=0u;
    core_driver *driver=NULL;core_driver_options options={0u,LIB_FALSE};
    core_run_result result;FILE *file;time_t start=time(NULL);
    unsigned int n,i,steps,max_steps=0u,returns[4]={0u,0u,0u,0u};
    unsigned int visible=0u,restored=0u,injury_cases[3]={0u,0u,0u};
    int ok=1,injury_pending=0;
    if(argc!=3)return 64;
    if(core_driver_create(&driver,&options)!=LIB_STATUS_OK||
        !core_driver_set_media(driver,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(driver->machine))return 65;
    memcpy(&baseline,driver->machine,sizeof(baseline));
    file=fopen(argv[2],"wb");if(file==NULL)return 65;
    if(fwrite(header,1u,sizeof(header),file)!=sizeof(header))ok=0;
    for(n=0u;n<CASES&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        memcpy(driver->machine,&baseline,sizeof(baseline));memset(driver->machine->ram,0,2048u);
        slot=(unsigned char)(n%6u);
        driver->machine->ram[8u]=slot;driver->machine->ram[9u]=(unsigned char)n;
        driver->machine->ram[0x0016u+slot]=(unsigned char)((n/32u)%2u!=0u?0x1fu:0x1eu);
        driver->machine->ram[0x006eu+slot]=(unsigned char)(n>=256u?2u:1u+(n/64u)%2u);
        driver->machine->ram[0x0087u+slot]=n>=256u?0u:xs[n%8u];
        driver->machine->ram[0x00b6u+slot]=1u;
        driver->machine->ram[0x00cfu+slot]=n>=256u?0x80u:ys[(n/8u)%8u];
        driver->machine->ram[0x071au]=1u;driver->machine->ram[0x071bu]=2u;
        driver->machine->ram[0x071cu]=0x80u;driver->machine->ram[0x071du]=0x7fu;
        driver->machine->ram[0x00a0u+slot]=(unsigned char)(n%32u);
        driver->machine->ram[0x0058u+slot]=(unsigned char)(n*17u);
        driver->machine->ram[0x0388u+slot]=(unsigned char)(n*29u);
        driver->machine->ram[0x0034u+slot]=(unsigned char)(n%2u);
        driver->machine->ram[0x06cfu]=(unsigned char)((slot+1u)%6u);
        for(i=0u;i<6u;++i){
            driver->machine->ram[0x06e5u+i]=(unsigned char)(0x40u+i*32u);
            driver->machine->ram[0x0110u+i]=0x55u;driver->machine->ram[0x0125u+i]=0xaau;
        }
        driver->machine->ram[0x0756u]=(unsigned char)(n%3u);
        driver->machine->ram[0x0754u]=(unsigned char)(n%3u==0u?1u:0u);
        driver->machine->ram[0x0714u]=(unsigned char)((n/4u)%2u);
        driver->machine->ram[0x00b5u]=1u;
        driver->machine->ram[0x00ceu]=(unsigned char)(driver->machine->ram[0x00cfu+slot]-
            (driver->machine->ram[0x0754u]!=0u||driver->machine->ram[0x0714u]!=0u?0x18u:0u));
        driver->machine->ram[0x0207u]=n>=256u?0x7cu:(unsigned char)(n*13u);
        driver->machine->ram[0x079eu]=(unsigned char)((n/4u)%2u!=0u?4u:0u);
        driver->machine->ram[0x079fu]=(unsigned char)((n/8u)%2u!=0u?4u:0u);
        driver->machine->ram[0x0747u]=(unsigned char)((n/16u)%2u);
        driver->machine->ram[0x074eu]=(unsigned char)((n/64u)%4u);
        driver->machine->ram[0x0753u]=(unsigned char)((n/128u)%2u);
        driver->machine->ram[0x01feu]=0u;driver->machine->ram[0x01ffu]=0x80u;
        driver->machine->pc=0xcd3cu;driver->machine->x=slot;
        driver->machine->a=0x77u;driver->machine->y=0x44u;driver->machine->s=0xfdu;
        record[0]=slot;record[1]=0u;memcpy(record+4u,driver->machine->ram,2048u);injury_pending=0;
        for(steps=0u;steps<LIMIT&&driver->machine->pc!=0x8001u;++steps){
            if(driver->machine->pc==0xcd3fu){
                ++returns[0];
                if(driver->machine->x!=slot||driver->machine->a!=driver->machine->ram[0x03d1u])ok=0;
            }
            if(driver->machine->pc==0xcd6fu){
                ++returns[1];++visible;record[1]=1u;
                if(driver->machine->x!=slot||driver->machine->a!=driver->machine->ram[0x03aeu])ok=0;
            }
            if(driver->machine->pc==0xce08u){oam=driver->machine->y;draw_x=driver->machine->x;}
            if(driver->machine->pc==0xce0bu){
                ++returns[2];if(driver->machine->y!=oam||driver->machine->x!=draw_x)ok=0;
            }
            if(driver->machine->pc==0xce7fu){
                loop=driver->machine->ram[0u];guard=(unsigned char)(driver->machine->ram[0x079eu]!=0u);
                ++injury_cases[guard!=0u?0u:driver->machine->ram[0x0756u]==0u?1u:2u];injury_pending=1;
                if(driver->machine->x!=0u)ok=0;
            }
            if(driver->machine->pc==0xce82u){
                ++returns[3];if(!injury_pending||driver->machine->x!=slot)ok=0;
            }
            if(driver->machine->pc==0xce85u&&injury_pending){
                ++restored;if(!injury_pending||driver->machine->ram[0u]!=loop)ok=0;injury_pending=0;
            }
            if(driver->machine->pc==0xce8du){
                if(driver->machine->ram[6u]!=(unsigned char)(oam+4u)||driver->machine->x!=slot)ok=0;
            }
            if(!ok){printf("seam failure case=%u pc=%04x x=%02x slot=%02x loop=%02x saved=%02x guard=%u pending=%d\n",n,driver->machine->pc,driver->machine->x,slot,driver->machine->ram[0u],loop,guard,injury_pending);break;}
            if(core_machine_debug_step(driver->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid){ok=0;break;}
        }
        if(driver->machine->pc!=0x8001u||injury_pending)ok=0;if(steps>max_steps)max_steps=steps;
        record[2]=driver->machine->x;record[3]=driver->machine->y;
        memcpy(record+2052u,driver->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(driver);
    printf("cases=%u visible=%u offscreen/relative/draw/injury-returns=%u/%u/%u/%u restored-loops=%u maxsteps=%u\n",
        n,visible,returns[0],returns[1],returns[2],returns[3],restored,max_steps);
    printf("guard/death/demotion=%u/%u/%u\n",injury_cases[0],injury_cases[1],injury_cases[2]);
    if(n!=CASES||returns[0]!=CASES||returns[1]==0u||returns[2]==0u||returns[3]==0u||
        restored!=returns[3]||injury_cases[0]==0u||injury_cases[1]==0u||injury_cases[2]==0u)ok=0;
    return ok?0:66;
}
