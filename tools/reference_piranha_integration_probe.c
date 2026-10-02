/* Real piranha distance return and movement consumers. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 1920u
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
    static const unsigned char speeds[16]={1u,1u,255u,1u,255u,1u,1u,1u,1u,1u,1u,0u,128u,127u,1u,254u};
    static const unsigned char deltas[16]={0u,0u,0u,0u,0u,0u,32u,33u,224u,223u,255u,64u,64u,64u,33u,0u};
    unsigned char header[12]={'M','S','P','I',1u,0u,0u,0u,0x80u,7u,0u,0u};
    unsigned char record[4100],slot,kind,low,high,borrow;
    unsigned int n,k,i,steps,maxsteps=0u,returns=0u,signs[2]={0u},borrows[2]={0u};
    unsigned int near[2]={0u},endpoints=0u,reversals=0u,negations=0u;
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
        kind=(unsigned char)(n>=1536u);k=kind==0u?n%256u:(n-1536u)%64u;
        slot=(unsigned char)(kind==0u?n/256u:(n-1536u)/64u);
        memcpy(d->machine,&baseline,sizeof(baseline));memset(d->machine->ram,0,2048u);
        d->machine->ram[8u]=slot;d->machine->ram[0x0016u+slot]=0x0du;
        d->machine->ram[0x0086u]=(unsigned char)(k*13u);
        d->machine->ram[0x0087u+slot]=(unsigned char)(d->machine->ram[0x0086u]+k);
        d->machine->ram[0x006du]=1u;
        borrow=(unsigned char)(d->machine->ram[0x0087u+slot]<d->machine->ram[0x0086u]);
        high=(unsigned char)(k/64u==0u?0u:k/64u==1u?0xffu:k/64u==2u?1u:0x80u);
        d->machine->ram[0x006eu+slot]=(unsigned char)(1u+borrow+high);
        d->machine->ram[0x0058u+slot]=1u;
        d->machine->ram[9u]=(unsigned char)(k/4u%2u);
        d->machine->ram[0x0747u]=(unsigned char)(k/8u%2u);
        d->machine->ram[0x00cfu+slot]=0x80u;
        d->machine->ram[0x0417u+slot]=0x7fu;
        d->machine->ram[0x0434u+slot]=0x81u;
        if(kind!=0u){
            unsigned int m=k%16u;unsigned char next,speed;
            d->machine->ram[0x001eu+slot]=(unsigned char)(m==0u?1u:0u);
            d->machine->ram[0x078au+slot]=(unsigned char)(m==1u?1u:0u);
            d->machine->ram[0x00a0u+slot]=(unsigned char)(m==3u||m==4u||m==15u?255u:0u);
            d->machine->ram[0x0058u+slot]=speeds[m];
            d->machine->ram[0x0086u]=0x80u;d->machine->ram[0x0087u+slot]=(unsigned char)(0x80u+deltas[m]);
            d->machine->ram[0x006du]=4u;d->machine->ram[0x006eu+slot]=(unsigned char)(m==14u?3u:4u);
            d->machine->ram[9u]=(unsigned char)(k/16u%2u);
            d->machine->ram[0x0747u]=(unsigned char)(k/32u%2u);
            d->machine->ram[0x00cfu+slot]=(unsigned char)(k/8u%2u!=0u?255u:0x80u);
            speed=d->machine->ram[0x00a0u+slot]!=0u?speeds[m]:(unsigned char)(0u-speeds[m]);
            next=(unsigned char)(d->machine->ram[0x00cfu+slot]+speed);
            d->machine->ram[0x0417u+slot]=(unsigned char)(next+k/4u%2u);
            d->machine->ram[0x0434u+slot]=d->machine->ram[0x0417u+slot];
        }
        d->machine->ram[0u]=0xa5u;d->machine->ram[0x03c5u+slot]=0xc3u;
        for(i=0x109u;i<=0x139u;++i)d->machine->ram[i]=0x55u;
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        d->machine->pc=0xd3b0u;d->machine->x=slot;d->machine->s=0xfdu;
        d->machine->a=0x77u;d->machine->y=0x44u;
        record[0]=kind;record[1]=slot;memcpy(record+4u,d->machine->ram,2048u);
        borrow=(unsigned char)(d->machine->ram[0x0087u+slot]<d->machine->ram[0x0086u]);
        low=(unsigned char)(d->machine->ram[0x0087u+slot]-d->machine->ram[0x0086u]);
        high=(unsigned char)(d->machine->ram[0x006eu+slot]-d->machine->ram[0x006du]-borrow);
        for(steps=0u;steps<LIMIT&&d->machine->pc!=0x8001u;++steps){
            if(d->machine->pc==0xd3c4u){
                ++returns;++signs[(high&0x80u)!=0u];++borrows[borrow];
                if(d->machine->x!=slot||d->machine->ram[0u]!=low||d->machine->a!=high||
                   (d->machine->p&0x80u)!=(high&0x80u)||
                   (d->machine->p&1u)!=(unsigned int)(d->machine->ram[0x006eu+slot]>=(unsigned int)d->machine->ram[0x006du]+borrow))ok=0;
            }
            if(d->machine->pc==0xd3cfu){
                if(d->machine->ram[0u]!=(unsigned char)((high&0x80u)!=0u?0u-low:low))ok=0;
            }
            if(d->machine->pc==0xd3d3u)++near[(d->machine->p&1u)!=0u];
            if(d->machine->pc==0xd3c6u)++negations;
            if(d->machine->pc==0xd3d5u)++reversals;
            if(d->machine->pc==0xd401u)++endpoints;
            if(!ok){printf("seam failure case=%u pc=%04x\n",n,d->machine->pc);break;}
            if(core_machine_debug_step(d->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid){ok=0;break;}
        }
        if(d->machine->pc!=0x8001u||d->machine->x!=slot)ok=0;if(steps>maxsteps)maxsteps=steps;
        record[2]=d->machine->a;record[3]=d->machine->y;memcpy(record+2052u,d->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(d);
    printf("cases=%u distance-returns=%u sign-clear/set=%u/%u borrow-clear/set=%u/%u maxsteps=%u\n",n,returns,signs[0],signs[1],borrows[0],borrows[1],maxsteps);
    printf("near/far=%u/%u negations=%u reversals=%u endpoint-stops=%u\n",near[0],near[1],negations,reversals,endpoints);
    if(n!=CASES||returns<1536u||signs[0]==0u||signs[1]==0u||borrows[0]==0u||borrows[1]==0u||near[0]==0u||near[1]==0u||negations==0u||reversals==0u||endpoints==0u)ok=0;
    return ok?0:66;
}
