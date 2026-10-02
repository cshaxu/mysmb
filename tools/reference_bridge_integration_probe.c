/* Real bridge gravity/init returns and Bowser drawing continuation. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 576u
#define LIMIT 524288u
static int ready(core_machine *m)
{
    core_run_result r;unsigned int n;
    for(n=0u;n<LIMIT;++n){
        if(m->pc==0x8181u)return 1;
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;
    }
    return 0;
}
int main(int argc,char **argv)
{
    static core_machine baseline;
    static const unsigned char speeds[8]={0u,1u,2u,3u,0x7fu,0x80u,0xfcu,0xffu};
    unsigned char header[12]={'M','S','B','I',1u,0u,0u,0u,0x40u,2u,0u,0u};
    unsigned char record[4100],slot,kind;
    unsigned int n,k,i,steps,maxsteps=0u,vertical=0u,init=0u,draw=0u;
    core_driver *d=NULL;core_driver_options opt={0u,LIB_FALSE};
    core_run_result result;FILE *file;time_t start=time(NULL);int ok=1;
    if(argc!=3)return 64;
    if(core_driver_create(&d,&opt)!=LIB_STATUS_OK||
        !core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    memcpy(&baseline,d->machine,sizeof(baseline));
    file=fopen(argv[2],"wb");if(!file)return 65;
    if(fwrite(header,1u,12u,file)!=12u)ok=0;
    for(n=0u;n<CASES&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        kind=(unsigned char)(n>=384u);k=kind==0u?n%64u:(n-384u)%32u;
        slot=(unsigned char)(kind==0u?n/64u:(n-384u)/32u);
        memcpy(d->machine,&baseline,sizeof(baseline));memset(d->machine->ram,0,2048u);
        d->machine->ram[8u]=slot;d->machine->ram[0x0368u]=slot;
        d->machine->ram[0x0016u+slot]=45u;d->machine->ram[0x000fu+slot]=1u;
        d->machine->ram[0x001eu+slot]=(unsigned char)(kind==0u?0x40u:0u);
        d->machine->ram[0x00a0u+slot]=speeds[k%8u];
        d->machine->ram[0x00b6u+slot]=1u;d->machine->ram[0x00cfu+slot]=(unsigned char)(0x70u+k);
        d->machine->ram[0x0417u+slot]=(unsigned char)(k*29u);
        d->machine->ram[0x0434u+slot]=(unsigned char)(k*17u);
        d->machine->ram[0x006eu+slot]=1u;d->machine->ram[0x0087u+slot]=0x90u;
        d->machine->ram[0x0046u+slot]=(unsigned char)(1u+k%2u);
        d->machine->ram[0x06cfu]=(unsigned char)((slot+1u)%6u);
        d->machine->ram[0x0363u]=(unsigned char)(k%2u);
        d->machine->ram[0x0364u]=(unsigned char)(k<30u?1u:2u);
        d->machine->ram[0x0369u]=(unsigned char)(k%15u);
        d->machine->ram[0x0300u]=(unsigned char)(k%4u*10u);
        d->machine->ram[0x0770u]=2u;d->machine->ram[0x074eu]=1u;
        d->machine->ram[0x071au]=1u;d->machine->ram[0x071bu]=2u;
        d->machine->ram[0x071cu]=0x20u;d->machine->ram[0x071du]=0x1fu;
        d->machine->ram[9u]=(unsigned char)k;
        for(i=0u;i<6u;++i){d->machine->ram[0x06e5u+i]=(unsigned char)(0x20u+24u*i);d->machine->ram[0x0110u+i]=0x55u;d->machine->ram[0x0125u+i]=0xaau;}
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        d->machine->pc=kind==0u?0xd00fu:0xcfecu;d->machine->x=slot;d->machine->s=0xfdu;
        d->machine->a=0x77u;d->machine->y=0x44u;
        record[0]=kind;record[1]=slot;memcpy(record+4u,d->machine->ram,2048u);
        for(steps=0u;steps<LIMIT&&d->machine->pc!=0x8001u;++steps){
            if(d->machine->pc==0xd012u){++vertical;if(d->machine->x!=slot||d->machine->ram[0u]!=0x0fu||d->machine->ram[2u]!=2u)ok=0;}
            if(d->machine->pc==0xd056u){++init;if(d->machine->x!=slot||d->machine->a!=0u||d->machine->ram[0x00a0u+slot]!=0u||d->machine->ram[0x0434u+slot]!=0u)ok=0;}
            if(d->machine->pc==0xd17bu){++draw;if(d->machine->x!=slot)ok=0;}
            if(!ok){printf("seam failure case=%u pc=%04x x=%02x\n",n,d->machine->pc,d->machine->x);break;}
            if(core_machine_debug_step(d->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid){ok=0;break;}
        }
        if(d->machine->pc!=0x8001u)ok=0;if(steps>maxsteps)maxsteps=steps;
        record[2]=d->machine->a;record[3]=d->machine->x;memcpy(record+2052u,d->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(d);
    printf("cases=%u vertical/init-returns=%u/%u actual-drawing=%u maxsteps=%u\n",n,vertical,init,draw,maxsteps);
    if(n!=CASES||vertical!=384u||init!=12u||draw!=CASES)ok=0;
    return ok?0:66;
}
