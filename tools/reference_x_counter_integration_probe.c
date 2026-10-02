/* Actual X-counter horizontal returned A and outer green flight consumers. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 4608u
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
    static const unsigned char primary_values[4]={0u,1u,0xfeu,0xffu};
    static const unsigned char endpoint_values[3]={0u,0x13u,0xffu};
    unsigned char header[12]={'M','S','X','C',1u,0u,0u,0u,0u,18u,0u,0u};
    unsigned char record[4100],slot,kind,saved=0u,speed=0u,displacement=0u,direction=0u;
    core_driver *driver=NULL;core_driver_options options={0u,LIB_FALSE};
    core_run_result result;FILE *file;time_t start=time(NULL);
    unsigned int n,local,steps,max_steps=0u,returns=0u,saves=0u;
    unsigned int directions[2]={0u,0u},signs[3]={0u,0u,0u},integer,fraction;
    int ok=1,pending=0;
    if(argc!=3)return 64;
    if(core_driver_create(&driver,&options)!=LIB_STATUS_OK||
        !core_driver_set_media(driver,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(driver->machine))return 65;
    memcpy(&baseline,driver->machine,sizeof(baseline));
    file=fopen(argv[2],"wb");if(file==NULL)return 65;
    if(fwrite(header,1u,sizeof(header),file)!=sizeof(header))ok=0;
    for(n=0u;n<CASES&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        kind=(unsigned char)(n<3072u?0u:1u);local=kind==0u?n:n-3072u;
        slot=(unsigned char)(local/(kind==0u?512u:256u));
        memcpy(driver->machine,&baseline,sizeof(baseline));memset(driver->machine->ram,0,2048u);
        driver->machine->ram[8u]=slot;
        driver->machine->ram[9u]=(unsigned char)(((local/32u)%4u)|((local/128u)%2u)*0x40u);
        driver->machine->ram[0x0058u+slot]=(unsigned char)local;
        driver->machine->ram[0x00a0u+slot]=(unsigned char)(kind==0u?(local/256u)%2u*2u:primary_values[(local/64u)%4u]);
        if(kind==1u&&local%32u<3u)driver->machine->ram[0x0058u+slot]=endpoint_values[local%32u];
        driver->machine->ram[0x006eu+slot]=(unsigned char)(local%3u==0u?0u:local%3u==1u?1u:0xffu);
        driver->machine->ram[0x0087u+slot]=(unsigned char)(local*13u);
        driver->machine->ram[0x0401u+slot]=(unsigned char)(local*31u);
        driver->machine->ram[0x00cfu+slot]=(unsigned char)(local*17u);
        driver->machine->ram[0x0110u+slot]=0x55u;driver->machine->ram[0x0125u+slot]=0xaau;
        driver->machine->ram[0x01feu]=0u;driver->machine->ram[0x01ffu]=0x80u;
        driver->machine->pc=kind==0u?0xcb66u:0xcb25u;
        driver->machine->x=slot;driver->machine->a=0x77u;driver->machine->y=0x44u;driver->machine->s=0xfdu;
        record[0]=kind;record[1]=slot;memcpy(record+4u,driver->machine->ram,2048u);pending=0;
        for(steps=0u;steps<LIMIT&&driver->machine->pc!=0x8001u;++steps){
            if(driver->machine->pc==0xcb66u){
                saved=driver->machine->ram[0x0058u+slot];
                direction=(unsigned char)((driver->machine->ram[0x00a0u+slot]&2u)!=0u?1u:2u);
                speed=direction==1u?saved:(unsigned char)(0u-saved);
            }
            if(driver->machine->pc==0xcb7eu){
                if(driver->machine->ram[0x0058u+slot]!=speed||
                    driver->machine->ram[0x0046u+slot]!=direction||driver->machine->x!=slot)ok=0;
                integer=speed>>4u;if(integer>=8u)integer|=0xf0u;
                fraction=(unsigned char)(speed<<4u);
                displacement=(unsigned char)(integer+
                    ((unsigned int)driver->machine->ram[0x0401u+slot]+fraction>255u?1u:0u));
                pending=1;
            }
            if(driver->machine->pc==0xcb81u){
                if(!pending||driver->machine->x!=slot||driver->machine->a!=displacement||
                    driver->machine->ram[0x0058u+slot]!=speed)ok=0;
                ++returns;++directions[direction-1u];
                ++signs[displacement==0u?0u:(displacement&0x80u)!=0u?2u:1u];
            }
            if(driver->machine->pc==0xcb83u){
                if(!pending||driver->machine->ram[0u]!=displacement)ok=0;
                ++saves;
            }
            if(driver->machine->pc==0xcb86u){
                if(!pending||driver->machine->ram[0x0058u+slot]!=saved)ok=0;
                pending=0;
            }
            if(!ok||core_machine_debug_step(driver->machine,1u,1024u,&result)!=LIB_STATUS_OK||
                result.trap_valid){ok=0;break;}
        }
        if(driver->machine->pc!=0x8001u||pending)ok=0;
        if(steps>max_steps)max_steps=steps;
        record[2]=driver->machine->x;record[3]=driver->machine->y;
        memcpy(record+2052u,driver->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(driver);
    printf("cases=%u returns=%u result-saves=%u directions=%u/%u zero/positive/negative=%u/%u/%u maxsteps=%u\n",
        n,returns,saves,directions[0],directions[1],signs[0],signs[1],signs[2],max_steps);
    if(n!=CASES||returns!=CASES||saves!=CASES||signs[0]==0u||signs[1]==0u||signs[2]==0u)ok=0;
    return ok?0:66;
}
