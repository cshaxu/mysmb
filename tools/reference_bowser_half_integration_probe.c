/* Real Bowser half retainer/box returns and collision consumers. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 1536u
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
    unsigned char header[12]={'M','S','G','H',1u,0u,0u,0u,0u,6u,0u,0u};
    unsigned char record[4100],slot,kind,active=0u,relative;
    unsigned int n,k,i,steps,maxsteps=0u,retainer=0u,boxes=0u,draw=0u,collisions=0u,injury=0u;
    unsigned int masked[2]={0u},halves[2]={0u};
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
        kind=0u;k=n%256u;slot=(unsigned char)(n/256u);
        memcpy(d->machine,&baseline,sizeof(baseline));memset(d->machine->ram,0,2048u);
        d->machine->ram[8u]=slot;d->machine->ram[0x0368u]=slot;
        d->machine->ram[0x0016u+slot]=45u;d->machine->ram[0x000fu+slot]=1u;
        d->machine->ram[0x001eu+slot]=(unsigned char)(k/16u%3u==0u?0u:k/16u%3u==1u?0x20u:0x40u);
        d->machine->ram[0x00b6u+slot]=(unsigned char)(k/32u%2u+1u);
        d->machine->ram[0x00cfu+slot]=(unsigned char)(0x70u+k/4u);
        d->machine->ram[0x006eu+slot]=(unsigned char)(k/8u%3u);
        d->machine->ram[0x0087u+slot]=(unsigned char)(k*13u);
        d->machine->ram[0x0046u+slot]=(unsigned char)(1u+k/4u%2u);
        d->machine->ram[0x03c5u+slot]=(unsigned char)(k/8u%4u);
        d->machine->ram[0x06cfu]=(unsigned char)((slot+1u+k/64u%5u)%6u);
        d->machine->ram[0x0363u]=(unsigned char)((k/4u%2u)*0x80u+(k/8u%2u));
        d->machine->ram[0x0770u]=1u;d->machine->ram[0x000eu]=8u;d->machine->ram[0x074eu]=1u;
        d->machine->ram[0x071au]=1u;d->machine->ram[0x071bu]=2u;
        d->machine->ram[0x071cu]=0x20u;d->machine->ram[0x071du]=0x1fu;
        d->machine->ram[0x00b5u]=1u;d->machine->ram[0x00ceu]=d->machine->ram[0x00cfu+slot];
        d->machine->ram[0x006du]=1u;d->machine->ram[0x0086u]=d->machine->ram[0x0087u+slot];
        d->machine->ram[0x0756u]=(unsigned char)(k/4u%3u);d->machine->ram[0x0754u]=(unsigned char)(k/4u%3u==0u);
        d->machine->ram[0x079eu]=(unsigned char)(k/16u%2u!=0u?4u:0u);
        d->machine->ram[0x079fu]=(unsigned char)(k/64u%2u);
        relative=(unsigned char)(d->machine->ram[0x0087u+slot]-0x20u);
        d->machine->ram[0x04acu]=(unsigned char)(relative+(k/2u%2u!=0u?0x40u:2u));
        d->machine->ram[0x04aeu]=(unsigned char)(d->machine->ram[0x04acu]+12u);
        d->machine->ram[0x04adu]=(unsigned char)(d->machine->ram[0x00ceu]+4u);
        d->machine->ram[0x04afu]=(unsigned char)(d->machine->ram[0x00ceu]+20u);
        d->machine->ram[9u]=(unsigned char)k;
        for(i=0u;i<6u;++i){d->machine->ram[0x06e5u+i]=(unsigned char)(0x20u+24u*i);d->machine->ram[0x0110u+i]=0x55u;d->machine->ram[0x0125u+i]=0xaau;}
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        d->machine->pc=0xd17bu;d->machine->x=slot;d->machine->s=0xfdu;
        d->machine->a=0x77u;d->machine->y=0x44u;
        record[0]=kind;record[1]=slot;memcpy(record+4u,d->machine->ram,2048u);
        for(steps=0u;steps<LIMIT&&d->machine->pc!=0x8001u;++steps){
            if(d->machine->pc==0xd1bfu)active=d->machine->ram[8u];
            if(d->machine->pc==0xd1c2u){++retainer;++halves[d->machine->ram[0x036au]==1u?0u:1u];
                if(d->machine->x!=active||d->machine->ram[8u]!=active)ok=0;}
            if(d->machine->pc==0xd1ceu){++boxes;++masked[d->machine->ram[0x03d8u+active]!=0u];
                if(d->machine->x!=active||d->machine->ram[8u]!=active||d->machine->ram[0x049au+active]!=10u)ok=0;}
            if(d->machine->pc==0xd853u)++collisions;
            if(d->machine->pc==0xd92cu)++injury;
            if(d->machine->pc==0xd17bu)++draw;
            if(!ok){printf("seam failure case=%u pc=%04x x=%02x\n",n,d->machine->pc,d->machine->x);break;}
            if(core_machine_debug_step(d->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid){ok=0;break;}
        }
        if(d->machine->pc!=0x8001u||d->machine->x!=slot||d->machine->ram[8u]!=slot||d->machine->ram[0x036au]!=0u)ok=0;if(steps>maxsteps)maxsteps=steps;
        record[2]=d->machine->a;record[3]=d->machine->x;memcpy(record+2052u,d->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(d);
    printf("cases=%u retainer/box-returns=%u/%u draw=%u collision-tail=%u injury=%u maxsteps=%u front/rear=%u/%u masked-clear/set=%u/%u\n",n,retainer,boxes,draw,collisions,injury,maxsteps,halves[0],halves[1],masked[0],masked[1]);
    if(n!=CASES||retainer!=2u*CASES||boxes==0u||draw!=CASES||collisions!=boxes||injury==0u||masked[0]==0u||masked[1]==0u)ok=0;
    return ok?0:66;
}
