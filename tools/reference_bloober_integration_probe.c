/* Real Bloober distance return and carry into the near-player ADC. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 3072u
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
    unsigned char header[12]={'M','S','B','I',1u,0u,0u,0u,0u,12u,0u,0u};
    unsigned char record[4100],slot,low=0u,high=0u,carry=0u,borrow,near_value=0u,near_carry=0u;
    core_driver *driver=NULL;core_driver_options options={0u,LIB_FALSE};
    core_run_result result;FILE *file;time_t start=time(NULL);
    unsigned int n,local,steps,max_steps=0u,returns=0u;
    unsigned int carries[2]={0u,0u},signs[2]={0u,0u},near_inputs[2]={0u,0u},sum;
    int ok=1,pending=0,near_pending=0;
    if(argc!=3)return 64;
    if(core_driver_create(&driver,&options)!=LIB_STATUS_OK||
        !core_driver_set_media(driver,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(driver->machine))return 65;
    memcpy(&baseline,driver->machine,sizeof(baseline));
    file=fopen(argv[2],"wb");if(file==NULL)return 65;
    if(fwrite(header,1u,sizeof(header),file)!=sizeof(header))ok=0;
    for(n=0u;n<CASES&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        local=n%512u;slot=(unsigned char)(n/512u);
        memcpy(driver->machine,&baseline,sizeof(baseline));memset(driver->machine->ram,0,2048u);
        driver->machine->ram[8u]=slot;driver->machine->ram[9u]=(unsigned char)(local%8u);
        driver->machine->ram[0x0016u+slot]=7u;driver->machine->ram[0x000fu+slot]=1u;
        driver->machine->ram[0x001eu+slot]=(unsigned char)(local>=256u&&local%32u==7u?0x20u:0u);
        driver->machine->ram[0x06ccu]=(unsigned char)((local/32u)%2u);
        driver->machine->ram[0x07a8u+slot]=(unsigned char)(local<256u||local%64u==63u?0u:local%64u);
        driver->machine->ram[0x0045u]=(unsigned char)(1u+local%2u);
        driver->machine->ram[0x0046u+slot]=(unsigned char)(1u+(local/2u)%2u);
        driver->machine->ram[0x006eu+slot]=(unsigned char)local;
        driver->machine->ram[0x006du]=(unsigned char)(local+(local>=256u?1u:0u));
        driver->machine->ram[0x0087u+slot]=(unsigned char)((local&2u)!=0u?0xf8u:8u);
        driver->machine->ram[0x0086u]=(unsigned char)((local&1u)!=0u?0xffu:0u);
        driver->machine->ram[0x00a0u+slot]=(unsigned char)(local<256u?2u:local%4u);
        driver->machine->ram[0x0796u+slot]=(unsigned char)(local<256u||local%64u==63u?0u:(local/4u)%2u);
        driver->machine->ram[0x00b6u+slot]=1u;driver->machine->ram[0x00cfu+slot]=(unsigned char)local;
        driver->machine->ram[0x00ceu]=(unsigned char)(local+0x10u+(local/4u)%2u);
        driver->machine->ram[0x0434u+slot]=(unsigned char)(local<256u||local%64u==63u?0u:(local/16u)%4u);
        driver->machine->ram[0x0058u+slot]=2u;driver->machine->ram[0x0417u+slot]=(unsigned char)(local*29u);
        driver->machine->ram[0x0110u+slot]=0x55u;driver->machine->ram[0x0125u+slot]=0xaau;
        driver->machine->ram[0x01feu]=0u;driver->machine->ram[0x01ffu]=0x80u;
        driver->machine->pc=0xcb89u;driver->machine->x=slot;
        driver->machine->a=0x77u;driver->machine->y=0x44u;driver->machine->s=0xfdu;
        /* The real movement JumpEngine ASL of ID 7 supplies C=0. */
        driver->machine->p=(unsigned char)(driver->machine->p&0xfeu);
        record[0]=slot;record[1]=(unsigned char)(local>=256u);
        memcpy(record+4u,driver->machine->ram,2048u);pending=0;near_pending=0;
        for(steps=0u;steps<LIMIT&&driver->machine->pc!=0x8001u;++steps){
            if(driver->machine->pc==0xe143u){
                if((slot&1u)!=0u)ok=0;
                pending=1;
                borrow=(unsigned char)(driver->machine->ram[0x0087u+slot]<driver->machine->ram[0x0086u]);
                low=(unsigned char)(driver->machine->ram[0x0087u+slot]-driver->machine->ram[0x0086u]);
                high=(unsigned char)(driver->machine->ram[0x006eu+slot]-driver->machine->ram[0x006du]-borrow);
                carry=(unsigned char)((unsigned int)driver->machine->ram[0x006eu+slot]>=
                    (unsigned int)driver->machine->ram[0x006du]+borrow);
            }
            if(driver->machine->pc==0xcba7u){
                if(!pending||driver->machine->x!=slot||driver->machine->y!=2u||
                    driver->machine->a!=high||driver->machine->ram[0u]!=low||
                    (driver->machine->p&1u)!=carry||(driver->machine->p&0x80u)!=(high&0x80u))ok=0;
                ++returns;++carries[carry];++signs[(high&0x80u)!=0u];pending=0;
            }
            if(driver->machine->pc==0xcc2bu){
                ++near_inputs[driver->machine->p&1u];
                sum=(unsigned int)driver->machine->ram[0x00cfu+slot]+0x10u+(driver->machine->p&1u);
                near_value=(unsigned char)sum;near_carry=(unsigned char)(sum>255u);near_pending=1;
            }
            if(driver->machine->pc==0xcc2du){
                if(!near_pending||driver->machine->a!=near_value||(driver->machine->p&1u)!=near_carry)ok=0;
                near_pending=0;
            }
            if(!ok||core_machine_debug_step(driver->machine,1u,1024u,&result)!=LIB_STATUS_OK||
                result.trap_valid){ok=0;break;}
        }
        if(driver->machine->pc!=0x8001u||pending||near_pending)ok=0;
        if(steps>max_steps)max_steps=steps;
        record[2]=driver->machine->x;record[3]=driver->machine->y;
        memcpy(record+2052u,driver->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(driver);
    printf("cases=%u distance-returns=%u carry-clear/set=%u/%u signs=%u/%u near-ADC-carry=%u/%u maxsteps=%u\n",
        n,returns,carries[0],carries[1],signs[0],signs[1],near_inputs[0],near_inputs[1],max_steps);
    if(n!=CASES||carries[0]==0u||carries[1]==0u||signs[0]==0u||signs[1]==0u||near_inputs[0]==0u||near_inputs[1]==0u)ok=0;
    return ok?0:66;
}
