/* Real normal/defeated/jumping enemy movement descendants and return ABI. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 9216u
#define LIMIT 524288u

static int ready(core_machine *machine)
{
    core_run_result result;
    unsigned int n;
    for(n=0u;n<LIMIT;++n){
        if(machine->pc==0x8181u)return 1;
        if(core_machine_debug_step(machine,1u,1024u,&result)!=LIB_STATUS_OK||
            result.trap_valid)return 0;
    }
    return 0;
}

int main(int argc,char **argv)
{
    static core_machine baseline;
    static const unsigned short entries[3]={0xca77u,0xcae5u,0xcaf9u};
    static const unsigned short return_pcs[4]={0xca9bu,0xcac4u,0xcae8u,0xcafcu};
    static const unsigned char speeds[4]={0x18u,0xe8u,0x7fu,0x80u};
    static const unsigned char timers[4]={0u,1u,0x0eu,0xffu};
    static const unsigned char vertical_speeds[4]={3u,0xf9u,0x7fu,0x80u};
    static const unsigned char adders[4]={0u,0xe8u,0u,0x18u};
    unsigned char header[12]={'M','S','E','M',1u,0u,0u,0u,0u,36u,0u,0u};
    unsigned char record[4100],slot,state,kind,temp_speed=0u,displacement=0u;
    core_driver *driver=NULL;
    core_driver_options options={0u,LIB_FALSE};
    core_run_result result;
    FILE *file;
    unsigned int n,i,j,local,variant,steps,max_steps=0u,returns[4]={0u,0u,0u,0u};
    unsigned int force_counts[3]={0u,0u,0u},index,integer,fraction,erases=0u;
    int ok=1,horizontal_pending=0;
    time_t start=time(NULL);
    if(argc!=3)return 64;
    if(core_driver_create(&driver,&options)!=LIB_STATUS_OK||
        !core_driver_set_media(driver,argv[1],LIB_STORAGE_MEDIUM_READONLY)||
        !ready(driver->machine))return 65;
    memcpy(&baseline,driver->machine,sizeof(baseline));
    file=fopen(argv[2],"wb");if(file==NULL)return 65;
    if(fwrite(header,1u,sizeof(header),file)!=sizeof(header))ok=0;
    for(n=0u;n<CASES&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        kind=(unsigned char)(n<6144u?0u:n<7680u?1u:2u);
        local=kind==0u?n:kind==1u?n-6144u:n-7680u;
        slot=(unsigned char)(local/(kind==0u?1024u:256u));
        state=(unsigned char)local;variant=kind==0u?(local/256u)%4u:local%4u;
        memcpy(driver->machine,&baseline,sizeof(baseline));
        memset(driver->machine->ram,0,2048u);
        for(i=0u;i<6u;++i){
            driver->machine->ram[0x0110u+i]=0x55u;
            driver->machine->ram[0x0125u+i]=0xaau;
        }
        driver->machine->ram[8u]=slot;driver->machine->ram[9u]=(unsigned char)(variant%2u);
        driver->machine->ram[0x000fu+slot]=1u;
        driver->machine->ram[0x0016u+slot]=(unsigned char)(local%3u==0u?6u:local%3u==1u?0x2eu:5u);
        driver->machine->ram[0x001eu+slot]=state;
        driver->machine->ram[0x0058u+slot]=speeds[variant];
        driver->machine->ram[0x0046u+slot]=2u;
        driver->machine->ram[0x006eu+slot]=(unsigned char)(local%3u==0u?0u:local%3u==1u?1u:0xffu);
        driver->machine->ram[0x0087u+slot]=(unsigned char)(local*13u);
        driver->machine->ram[0x0401u+slot]=(unsigned char)(local*31u);
        driver->machine->ram[0x00b6u+slot]=1u;
        driver->machine->ram[0x00cfu+slot]=(unsigned char)(local*7u);
        driver->machine->ram[0x00a0u+slot]=vertical_speeds[variant];
        driver->machine->ram[0x0417u+slot]=(unsigned char)(local*29u);
        driver->machine->ram[0x0434u+slot]=(unsigned char)(local*11u);
        driver->machine->ram[0x0796u+slot]=timers[(variant+local/16u)%4u];
        driver->machine->ram[0x076au]=(unsigned char)((local/32u+variant)%2u);
        driver->machine->ram[0x078au+slot]=0x80u;
        driver->machine->ram[0x03c5u+slot]=0x77u;
        driver->machine->ram[0x01feu]=0u;driver->machine->ram[0x01ffu]=0x80u;
        driver->machine->pc=entries[kind];driver->machine->x=slot;
        driver->machine->a=0x77u;driver->machine->y=0x44u;driver->machine->s=0xfdu;
        record[0]=kind;record[1]=slot;memcpy(record+4u,driver->machine->ram,2048u);
        horizontal_pending=0;
        for(steps=0u;steps<LIMIT&&driver->machine->pc!=0x8001u;++steps){
            if(driver->machine->pc==0xc998u)++erases;
            if(driver->machine->pc==0xcac1u){
                index=(state&0x40u)!=0u&&driver->machine->ram[0x0016u+slot]!=0x2eu?1u:0u;
                if((record[4u+0x0058u+slot]&0x80u)!=0u)index+=2u;
                temp_speed=(unsigned char)(record[4u+0x0058u+slot]+adders[index]);
                if(driver->machine->ram[0x0058u+slot]!=temp_speed)ok=0;
                integer=temp_speed>>4u;if(integer>=8u)integer|=0xf0u;
                fraction=(unsigned char)(temp_speed<<4u);
                displacement=(unsigned char)(integer+
                    ((unsigned int)driver->machine->ram[0x0401u+slot]+fraction>255u?1u:0u));
                horizontal_pending=1;
            }
            for(j=0u;j<4u;++j)if(driver->machine->pc==return_pcs[j]){
                ++returns[j];if(driver->machine->x!=slot)ok=0;
                if(j==1u){
                    if(!horizontal_pending||driver->machine->a!=displacement||
                        driver->machine->ram[0x0058u+slot]!=temp_speed)ok=0;
                    horizontal_pending=0;
                }else{
                    unsigned char force=(unsigned char)(j==3u?0x1cu:state==5u?0x20u:0x3du);
                    if(driver->machine->ram[0u]!=force||driver->machine->ram[2u]!=3u)ok=0;
                    ++force_counts[force==0x1cu?0u:force==0x20u?1u:2u];
                }
            }
            if(!ok||core_machine_debug_step(driver->machine,1u,1024u,&result)!=LIB_STATUS_OK||
                result.trap_valid){ok=0;break;}
        }
        if(driver->machine->pc!=0x8001u||horizontal_pending)ok=0;
        if(steps>max_steps)max_steps=steps;
        record[2]=driver->machine->x;record[3]=driver->machine->y;
        memcpy(record+2052u,driver->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(driver);
    printf("cases=%u maxsteps=%u erase-calls=%u\n",n,max_steps,erases);
    for(i=0u;i<4u;++i){printf("return=%04x observed=%u\n",return_pcs[i],returns[i]);if(returns[i]==0u)ok=0;}
    printf("gravity-forces 1c/20/3d=%u/%u/%u\n",force_counts[0],force_counts[1],force_counts[2]);
    if(n!=CASES||erases==0u)ok=0;
    return ok?0:66;
}
