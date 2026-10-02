/* Actual Hammer Bro allocation/distance returns and movement integration. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 3072u
#define LIMIT 524288u

static int ready(core_machine *machine)
{
    core_run_result result;
    unsigned int n;
    for (n=0u;n<LIMIT;++n) {
        if (machine->pc==0x8181u) return 1;
        if (core_machine_debug_step(machine,1u,1024u,&result)!=LIB_STATUS_OK ||
            result.trap_valid) return 0;
    }
    return 0;
}

int main(int argc,char **argv)
{
    static core_machine baseline;
    static const unsigned char dependencies[9]={4u,4u,4u,5u,5u,5u,6u,6u,6u};
    unsigned char header[12]={'M','S','H','B',1u,0u,0u,0u,0u,12u,0u,0u};
    unsigned char record[4100],child_before[2048],expected,slot,selected,carry;
    unsigned char low=0u,high=0u,borrow=0u,diff_carry=0u;
    core_driver *driver=NULL;
    core_driver_options options={0u,LIB_FALSE};
    core_run_result result;
    FILE *file;
    unsigned int n,i,mode,block,steps,max_steps=0u,spawn_returns=0u,diff_returns=0u;
    unsigned int spawn_results[2]={0u,0u},diff_signs[2]={0u,0u},allocation[9]={0u};
    unsigned int blockers[3]={0u,0u,0u};
    int ok=1,spawn_pending=0,diff_pending=0;
    time_t start=time(NULL);
    if(argc!=3)return 64;
    if(core_driver_create(&driver,&options)!=LIB_STATUS_OK ||
        !core_driver_set_media(driver,argv[1],LIB_STORAGE_MEDIUM_READONLY) ||
        !ready(driver->machine))return 65;
    memcpy(&baseline,driver->machine,sizeof(baseline));
    file=fopen(argv[2],"wb");if(file==NULL)return 65;
    if(fwrite(header,1u,sizeof(header),file)!=sizeof(header))ok=0;
    for(n=0u;n<CASES&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        memcpy(driver->machine,&baseline,sizeof(baseline));
        memset(driver->machine->ram,0,2048u);
        slot=(unsigned char)(n/512u);mode=(n/128u)%4u;
        driver->machine->ram[8u]=slot;
        driver->machine->ram[9u]=(unsigned char)((n&8u)!=0u?0x40u:0u);
        driver->machine->ram[0x000fu+slot]=1u;
        driver->machine->ram[0x0016u+slot]=5u;
        driver->machine->ram[0x001eu+slot]=(unsigned char)(mode==3u?0x20u:mode==2u?n%2u:0u);
        driver->machine->ram[0x003cu+slot]=(unsigned char)(mode<2u?1u:0u);
        driver->machine->ram[0x03a2u+slot]=(unsigned char)(mode==1u?n%2u:0u);
        driver->machine->ram[0x03d1u]=(unsigned char)(mode==1u&&(n&2u)!=0u?4u:0u);
        driver->machine->ram[0x06ccu]=(unsigned char)((n/32u)%2u);
        driver->machine->ram[0x0796u+slot]=(unsigned char)((n/16u)%2u);
        driver->machine->ram[0x006eu+slot]=2u;
        driver->machine->ram[0x0087u+slot]=(unsigned char)((n&4u)!=0u?0xf8u:0x08u);
        driver->machine->ram[0x006du]=(unsigned char)(1u+(n/64u)%3u);
        driver->machine->ram[0x0086u]=(unsigned char)((n&1u)!=0u?0xffu:0u);
        driver->machine->ram[0x00b6u+slot]=1u;
        driver->machine->ram[0x00cfu+slot]=(unsigned char)(n*13u);
        driver->machine->ram[0x00a0u+slot]=(unsigned char)(n%2u!=0u?0xfeu:1u);
        driver->machine->ram[0x0434u+slot]=(unsigned char)(n*29u);
        driver->machine->ram[0x0417u+slot]=(unsigned char)(n*31u);
        driver->machine->ram[0x0401u+slot]=(unsigned char)(n*17u);
        driver->machine->ram[0x07a8u+slot]=(unsigned char)(n*7u);
        driver->machine->ram[0x07a9u+slot]=(unsigned char)n;
        driver->machine->ram[0x07a8u]=(unsigned char)(n%16u);
        selected=(unsigned char)(driver->machine->ram[0x07a8u]&7u);
        if(selected==0u)selected=(unsigned char)(driver->machine->ram[0x07a8u]&8u);
        block=(n/16u)%3u;
        if(block==1u)driver->machine->ram[0x002au+selected]=1u;
        if(block==2u)driver->machine->ram[0x000fu+dependencies[selected]]=1u;
        driver->machine->ram[0x01feu]=0u;driver->machine->ram[0x01ffu]=0x80u;
        driver->machine->pc=0xc9d8u;driver->machine->x=slot;
        driver->machine->a=0x77u;driver->machine->y=0x44u;driver->machine->s=0xfdu;
        record[0]=slot;record[1]=(unsigned char)mode;
        memcpy(record+4u,driver->machine->ram,2048u);
        spawn_pending=0;diff_pending=0;carry=0u;
        for(steps=0u;steps<LIMIT&&driver->machine->pc!=0x8001u;++steps){
            if(driver->machine->pc==0xba94u){
                spawn_pending=1;memcpy(child_before,driver->machine->ram,2048u);
                carry=(unsigned char)(child_before[0x002au+selected]==0u&&
                    child_before[0x000fu+dependencies[selected]]==0u);
                ++blockers[child_before[0x002au+selected]!=0u?1u:
                    child_before[0x000fu+dependencies[selected]]!=0u?2u:0u];
            }
            if(driver->machine->pc==0xc9ffu){
                if(!spawn_pending||driver->machine->x!=slot||driver->machine->y!=selected||
                    (driver->machine->p&1u)!=carry)ok=0;
                ++spawn_returns;++spawn_results[carry];++allocation[selected];spawn_pending=0;
                for(i=8u;i<2048u;++i){
                    if(i>=0x100u&&i<0x200u)continue;
                    expected=child_before[i];
                    if(carry!=0u){
                        if(i==0x06aeu+selected)expected=slot;
                        if(i==0x002au+selected)expected=0x90u;
                        if(i==0x04a2u+selected)expected=7u;
                    }
                    if(driver->machine->ram[i]!=expected)ok=0;
                }
            }
            if(driver->machine->pc==0xe143u){
                diff_pending=1;
                borrow=(unsigned char)(driver->machine->ram[0x0087u+slot]<driver->machine->ram[0x0086u]);
                low=(unsigned char)(driver->machine->ram[0x0087u+slot]-driver->machine->ram[0x0086u]);
                high=(unsigned char)(driver->machine->ram[0x006eu+slot]-driver->machine->ram[0x006du]-borrow);
                diff_carry=(unsigned char)((unsigned int)driver->machine->ram[0x006eu+slot]>=
                    (unsigned int)driver->machine->ram[0x006du]+borrow);
            }
            if(driver->machine->pc==0xca69u){
                if(!diff_pending||driver->machine->x!=slot||driver->machine->y!=1u||
                    driver->machine->a!=high||driver->machine->ram[0u]!=low||
                    (driver->machine->p&0x80u)!=(high&0x80u)||
                    (driver->machine->p&1u)!=diff_carry)ok=0;
                ++diff_returns;++diff_signs[(high&0x80u)!=0u];diff_pending=0;
            }
            if(!ok||core_machine_debug_step(driver->machine,1u,1024u,&result)!=LIB_STATUS_OK||
                result.trap_valid){ok=0;break;}
        }
        if(driver->machine->pc!=0x8001u||spawn_pending||diff_pending)ok=0;
        if(steps>max_steps)max_steps=steps;
        record[2]=driver->machine->x;record[3]=driver->machine->y;
        memcpy(record+2052u,driver->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(driver);
    printf("cases=%u spawn-returns=%u carry-clear/set=%u/%u diff-returns=%u signs=%u/%u maxsteps=%u\n",
        n,spawn_returns,spawn_results[0],spawn_results[1],diff_returns,diff_signs[0],diff_signs[1],max_steps);
    printf("allocation success/misc-blocked/enemy-blocked=%u/%u/%u\n",blockers[0],blockers[1],blockers[2]);
    for(i=0u;i<9u;++i){printf("hammer-slot=%u returns=%u\n",i,allocation[i]);if(allocation[i]==0u)ok=0;}
    if(n!=CASES||spawn_results[0]==0u||spawn_results[1]==0u||diff_signs[0]==0u||diff_signs[1]==0u)ok=0;
    return ok?0:66;
}
