/* Actual small/large-platform descendant return and material proof. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 512u
#define LIMIT 524288u
static const unsigned short returns[12]={0xc950u,0xc953u,0xc956u,0xc959u,0xc95cu,0xc95fu,0xc968u,0xc96bu,0xc96eu,0xc971u,0xc97cu,0xc97fu};
static unsigned int observed[12],slot_diffs[12],handoffs[2],offset_returns,masks[16];
static int ready(core_machine *m)
{
    core_run_result r;unsigned int n;
    for(n=0u;n<LIMIT;++n){if(m->pc==0x8181u)return 1;
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;}
    return 0;
}
int main(int argc,char **argv)
{
    static core_machine baseline;
    static const unsigned char xs[8]={0u,0x10u,0x70u,0x80u,0x90u,0xf0u,0xf8u,0xffu};
    static const unsigned char ys[8]={0x10u,0x20u,0x40u,0x80u,0x90u,0xa0u,0xe0u,0xf8u};
    unsigned char head[12]={'M','S','P','L',1u,0u,0u,0u,0u,2u,0u,0u},rec[4100];
    core_driver *d=NULL;core_driver_options opts={0u,LIB_FALSE};core_run_result r;FILE *f;
    unsigned int n,i,k,step,pc,b,maxstep=0u,sum;unsigned char slot,box=0xffu;int ok=1;time_t start=time(NULL);
    if(argc!=3)return 64;
    if(core_driver_create(&d,&opts)!=LIB_STATUS_OK||
       !core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    memcpy(&baseline,d->machine,sizeof(baseline));f=fopen(argv[2],"wb");if(f==NULL)return 65;
    if(fwrite(head,1u,sizeof(head),f)!=sizeof(head))ok=0;
    for(n=0u;n<CASES&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        memcpy(d->machine,&baseline,sizeof(baseline));k=n/256u;slot=(unsigned char)(n%6u);box=0xffu;
        memset(d->machine->ram,0,2048u);
        d->machine->ram[8u]=slot;d->machine->ram[9u]=(unsigned char)n;
        d->machine->ram[0x071au]=1u;d->machine->ram[0x071bu]=2u;
        d->machine->ram[0x071cu]=0x80u;d->machine->ram[0x071du]=0x7fu;
        d->machine->ram[0x0747u]=(unsigned char)((n/8u)%2u);
        d->machine->ram[0x074eu]=(unsigned char)((n/16u)%4u);
        d->machine->ram[0x06ccu]=(unsigned char)((n/32u)%2u);
        d->machine->ram[0x0743u]=(unsigned char)((n/64u)%2u);
        for(i=0u;i<6u;++i){
            d->machine->ram[0x000fu+i]=1u;d->machine->ram[0x0016u+i]=0x26u;
            d->machine->ram[0x006eu+i]=1u;d->machine->ram[0x0087u+i]=0x90u;
            d->machine->ram[0x00b6u+i]=1u;d->machine->ram[0x00cfu+i]=0x80u;
            d->machine->ram[0x049au+i]=6u;d->machine->ram[0x06e5u+i]=(unsigned char)(0x40u+i*24u);
            d->machine->ram[0x03d2u+i]=(unsigned char)(0xa5u+i);}
        d->machine->ram[0x0016u+slot]=(unsigned char)(k==0u?0x2bu+n%2u:0x24u+n%7u);
        d->machine->ram[0x001eu+slot]=(unsigned char)(k==1u&&n%7u==0u?(slot+1u)%6u:0u);
        d->machine->ram[0x006eu+slot]=(unsigned char)(1u+(n/64u)%2u);
        d->machine->ram[0x0087u+slot]=xs[n%8u];d->machine->ram[0x00cfu+slot]=ys[(n/8u)%8u];
        d->machine->ram[0x049au+slot]=(unsigned char)(k==0u?4u:6u);
        d->machine->ram[0x0434u+slot]=(unsigned char)(n*17u);
        d->machine->ram[0x00a0u+slot]=(unsigned char)(n%3u==0u?0xffu:1u);
        d->machine->ram[0x0058u+slot]=0x90u;d->machine->ram[0x0401u+slot]=0x40u;
        sum=(unsigned int)d->machine->ram[0x0087u+slot]+4u;
        d->machine->ram[0x006du]=(unsigned char)(d->machine->ram[0x006eu+slot]+(sum>>8u));
        d->machine->ram[0x0086u]=(unsigned char)sum;d->machine->ram[0x00b5u]=1u;
        d->machine->ram[0x00ceu]=(unsigned char)(d->machine->ram[0x00cfu+slot]-0x20u+(n%4u));
        d->machine->ram[0x009fu]=(unsigned char)(n%4u==3u?0xfeu:1u);
        d->machine->ram[0x0754u]=0u;d->machine->ram[0x0499u]=0u;
        d->machine->ram[0x04acu]=(unsigned char)(sum-0x80u+2u);
        d->machine->ram[0x04aeu]=(unsigned char)(sum-0x80u+14u);
        d->machine->ram[0x04adu]=(unsigned char)(d->machine->ram[0x00ceu]+8u);
        d->machine->ram[0x04afu]=(unsigned char)(d->machine->ram[0x00ceu]+0x20u);
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        d->machine->a=0x77u;d->machine->x=slot;d->machine->y=0x44u;
        d->machine->s=0xfdu;d->machine->pc=k==0u?0xc94du:0xc965u;
        rec[0]=(unsigned char)k;rec[1]=slot;memcpy(rec+4u,d->machine->ram,2048u);
        for(step=0u;step<LIMIT&&d->machine->pc!=0x8001u;++step){
            pc=d->machine->pc;
            if(pc==0xdc5fu){box=d->machine->y;++offset_returns;
                if(box!=(unsigned char)(d->machine->x*4u+4u)||d->machine->a!=(d->machine->ram[0x03d1u]&15u)){ok=0;break;}
                ++masks[d->machine->a];}
            if(pc==0xe325u){++handoffs[k];if(d->machine->y!=box){ok=0;break;}}
            if(core_machine_debug_step(d->machine,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid){ok=0;break;}
            for(b=0u;b<12u;++b)if(d->machine->pc==returns[b]){
                ++observed[b];if(d->machine->x!=slot){++slot_diffs[b];ok=0;}}
        }
        if(d->machine->pc!=0x8001u)ok=0;if(step>maxstep)maxstep=step;
        rec[2]=d->machine->x;rec[3]=d->machine->y;
        memcpy(rec+2052u,d->machine->ram,2048u);
        if(fwrite(rec,1u,sizeof(rec),f)!=sizeof(rec))ok=0;
    }
    if(fclose(f)!=0)ok=0;(void)core_driver_destroy(d);
    printf("cases=%u maxsteps=%u box-offset-returns=%u geometry-handoffs=%u/%u\n",n,maxstep,offset_returns,handoffs[0],handoffs[1]);
    for(b=0u;b<12u;++b){
        printf("return=%04x observed=%u X-not-slot=%u\n",returns[b],observed[b],slot_diffs[b]);
        if(observed[b]!=256u||slot_diffs[b]!=0u)ok=0;
    }
    for(b=0u;b<16u;++b)if(masks[b])printf("source-low-mask=%x observed=%u\n",b,masks[b]);
    return ok?0:66;
}
