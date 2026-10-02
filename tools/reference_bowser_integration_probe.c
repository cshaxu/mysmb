/* Real Bowser distance/gravity/allocation/init returns and consumers. */
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
    static const unsigned char speeds[8]={0u,1u,2u,3u,0x7fu,0x80u,0xfcu,0xffu};
    unsigned char header[12]={'M','S','B','C',1u,0u,0u,0u,0u,6u,0u,0u};
    unsigned char record[4100],slot,kind,low=0u,high=0u,borrow,selected=0u,carry=0u;
    static const unsigned char dependency[9]={4u,4u,4u,5u,5u,5u,6u,6u,6u};
    unsigned int n,k,i,steps,maxsteps=0u,vertical=0u,init=0u,draw=0u,distance=0u,spawn=0u;
    unsigned int signs[2]={0u},allocations[2]={0u},blocked[3]={0u},slots[9]={0u};
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
        k=n%256u;slot=(unsigned char)(n/256u);kind=(unsigned char)(k%4u);
        memcpy(d->machine,&baseline,sizeof(baseline));memset(d->machine->ram,0,2048u);
        d->machine->ram[8u]=slot;d->machine->ram[0x0368u]=slot;
        d->machine->ram[0x0016u+slot]=45u;d->machine->ram[0x000fu+slot]=1u;
        d->machine->ram[0x00a0u+slot]=speeds[(k/4u)%8u];
        d->machine->ram[0x00b6u+slot]=1u;d->machine->ram[0x00cfu+slot]=(unsigned char)(0x60u+k/2u);
        d->machine->ram[0x0417u+slot]=(unsigned char)(k*29u);
        d->machine->ram[0x0434u+slot]=(unsigned char)(k*17u);
        d->machine->ram[0x006eu+slot]=(unsigned char)(k/16u%3u);
        d->machine->ram[0x0087u+slot]=(unsigned char)(0x70u+k/2u);
        d->machine->ram[0x006du]=1u;d->machine->ram[0x0086u]=(unsigned char)(k*13u);
        d->machine->ram[0x0046u+slot]=(unsigned char)(1u+k/4u%2u);
        d->machine->ram[0x06cfu]=(unsigned char)((slot+1u)%6u);
        d->machine->ram[0x0363u]=(unsigned char)(kind==2u?0x80u:k/32u%2u);
        d->machine->ram[0x0364u]=(unsigned char)(k/8u%2u);
        d->machine->ram[0x0365u]=(unsigned char)(k/8u%2u!=0u?1u:0xffu);
        d->machine->ram[0x0366u]=(unsigned char)(k/16u%2u!=0u?d->machine->ram[0x0087u+slot]:0x80u);
        d->machine->ram[0x06dcu]=(unsigned char)(0x11u+k/8u);
        d->machine->ram[0x078au+slot]=(unsigned char)(kind==1u?0u:kind==2u?1u:2u);
        d->machine->ram[0x0747u]=(unsigned char)(kind==3u);
        d->machine->ram[0x075fu]=(unsigned char)(kind==1u?5u+k/4u%3u:k/4u%8u);
        d->machine->ram[0x0790u]=(unsigned char)(k/16u%2u);
        d->machine->ram[0x06ccu]=(unsigned char)(k/8u%2u);
        d->machine->ram[0x07a7u+slot]=(unsigned char)(k/4u%4u);
        selected=(unsigned char)(k/4u%9u);d->machine->ram[0x07a8u]=selected;
        if(kind==1u&&k/4u%3u==1u)d->machine->ram[0x002au+selected]=1u;
        if(kind==1u&&k/4u%3u==2u)d->machine->ram[0x000fu+dependency[selected]]=1u;
        d->machine->ram[0x0770u]=2u;d->machine->ram[0x074eu]=1u;
        d->machine->ram[0x071au]=1u;d->machine->ram[0x071bu]=2u;
        d->machine->ram[0x071cu]=0x20u;d->machine->ram[0x071du]=0x1fu;
        d->machine->ram[9u]=(unsigned char)(k&0xfcu);
        for(i=0u;i<6u;++i){d->machine->ram[0x06e5u+i]=(unsigned char)(0x20u+24u*i);d->machine->ram[0x0110u+i]=0x55u;d->machine->ram[0x0125u+i]=0xaau;}
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        d->machine->pc=0xd065u;d->machine->x=slot;d->machine->s=0xfdu;
        d->machine->a=0x77u;d->machine->y=0x44u;
        record[0]=kind;record[1]=slot;memcpy(record+4u,d->machine->ram,2048u);
        for(steps=0u;steps<LIMIT&&d->machine->pc!=0x8001u;++steps){
            if(d->machine->pc==0xd0b5u){
                borrow=(unsigned char)(d->machine->ram[0x0087u+slot]<d->machine->ram[0x0086u]);
                low=(unsigned char)(d->machine->ram[0x0087u+slot]-d->machine->ram[0x0086u]);
                high=(unsigned char)(d->machine->ram[0x006eu+slot]-d->machine->ram[0x006du]-borrow);
            }
            if(d->machine->pc==0xd0b8u){++distance;++signs[(high&0x80u)!=0u];
                if(d->machine->x!=slot||d->machine->a!=high||d->machine->ram[0u]!=low||(d->machine->p&0x80u)!=(high&0x80u))ok=0;}
            if(d->machine->pc==0xd117u){++vertical;if(d->machine->x!=slot||d->machine->ram[0u]!=0x0fu||d->machine->ram[2u]!=2u)ok=0;}
            if(d->machine->pc==0xd124u){
                carry=(unsigned char)(d->machine->ram[0x002au+selected]==0u&&d->machine->ram[0x000fu+dependency[selected]]==0u);
                ++blocked[d->machine->ram[0x002au+selected]!=0u?1u:d->machine->ram[0x000fu+dependency[selected]]!=0u?2u:0u];
            }
            if(d->machine->pc==0xd127u){++spawn;++allocations[carry];++slots[selected];
                if(d->machine->x!=slot||d->machine->y!=selected||(d->machine->p&1u)!=carry)ok=0;}
            if(d->machine->pc==0xd145u){++init;if(d->machine->x!=slot||d->machine->a!=0u||d->machine->ram[0x00a0u+slot]!=0u||d->machine->ram[0x0434u+slot]!=0u)ok=0;}
            if(d->machine->pc==0xd17bu){++draw;if(d->machine->x!=slot)ok=0;}
            if(!ok){printf("seam failure case=%u pc=%04x x=%02x\n",n,d->machine->pc,d->machine->x);break;}
            if(core_machine_debug_step(d->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid){ok=0;break;}
        }
        if(d->machine->pc!=0x8001u)ok=0;if(steps>maxsteps)maxsteps=steps;
        record[2]=d->machine->a;record[3]=d->machine->x;memcpy(record+2052u,d->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(d);
    printf("cases=%u distance/vertical/spawn/init=%u/%u/%u/%u draw=%u maxsteps=%u signs=%u/%u allocation-carry=%u/%u blockers=%u/%u/%u\n",n,distance,vertical,spawn,init,draw,maxsteps,signs[0],signs[1],allocations[0],allocations[1],blocked[0],blocked[1],blocked[2]);
    for(i=0u;i<9u;++i){printf("allocation-slot=%u returns=%u\n",i,slots[i]);if(slots[i]==0u)ok=0;}
    if(n!=CASES||distance==0u||vertical==0u||spawn==0u||init==0u||draw!=CASES||signs[0]==0u||signs[1]==0u||allocations[0]==0u||allocations[1]==0u||blocked[1]==0u||blocked[2]==0u)ok=0;
    return ok?0:66;
}
