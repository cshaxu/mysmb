/* Direct core and actual-caller ROM proof; no ROM bytes are modified. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 10512u
#define LIMIT 524288u
static const unsigned short branch_pc[14]={0xe333u,0xe338u,0xe33au,0xe342u,0xe347u,0xe352u,0xe35au,0xe362u,0xe367u,0xe369u,0xe36eu,0xe370u,0xe378u,0xe382u};
static unsigned int taken[14],fall[14],hammer_returns,fireball_returns,maxsteps;
static unsigned char visited[99];
static int ready(core_machine *m)
{
    core_run_result r;unsigned int n;
    for(n=0u;n<LIMIT;++n){if(m->pc==0x8181u)return 1;
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;}
    return 0;
}
static int run(core_machine *m,unsigned short entry,unsigned char x,unsigned char y)
{
    core_run_result r;unsigned int step,pc,b;
    m->ram[0x01feu]=0u;m->ram[0x01ffu]=0x80u;
    m->a=0x77u;m->x=x;m->y=y;m->s=0xfdu;m->pc=entry;
    for(step=0u;step<LIMIT&&m->pc!=0x8001u;++step){
        pc=m->pc;if(pc>=0xe325u&&pc<=0xe387u)visited[pc-0xe325u]=1u;
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;
        for(b=0u;b<14u;++b)if(pc==branch_pc[b]){
            if(m->pc==pc+2u)++fall[b];else ++taken[b];}
        if(pc==0xe34bu||pc==0xe35eu||pc==0xe37du||pc==0xe387u){
            if(m->pc>=0xd6d9u&&m->pc<=0xd735u)++fireball_returns;
            if(m->pc>=0xd7c4u&&m->pc<=0xd7ffu)++hammer_returns;}
    }
    if(step>maxsteps)maxsteps=step;
    return m->pc==0x8001u;
}
int main(int argc,char **argv)
{
    static core_machine baseline;
    static const unsigned char values[6]={0u,1u,0x7fu,0x80u,0xfeu,0xffu};
    unsigned char head[12]={'M','S','G','E',1u,0u,0u,0u,0x10u,0x29u,0u,0u};
    unsigned char rec[4102];core_driver *d=NULL;core_driver_options opts={0u,LIB_FALSE};
    FILE *f;unsigned int n,i,k,local,axis,rank,first,second,b;
    unsigned char slot,initial_x,initial_y;int ok=1;time_t start=time(NULL);
    if(argc!=3)return 64;
    if(core_driver_create(&d,&opts)!=LIB_STATUS_OK||
       !core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    memcpy(&baseline,d->machine,sizeof(baseline));f=fopen(argv[2],"wb");if(f==NULL)return 65;
    if(fwrite(head,1u,sizeof(head),f)!=sizeof(head))ok=0;
    for(n=0u;n<CASES&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        memcpy(d->machine,&baseline,sizeof(baseline));
        k=n<10368u?n/2592u:4u;local=n%2592u;axis=local/1296u;rank=local%1296u;
        slot=(unsigned char)(n%(k==3u?2u:9u));
        first=k==1u?n%18u:(k==3u?5u:0u);
        second=k==1u?(first+7u)%18u:(k==2u?9u+slot:(k==3u?7u+slot:1u+n%17u));
        for(i=0u;i<2048u;++i)d->machine->ram[i]=(unsigned char)(i*13u+n);
        d->machine->ram[8u]=slot;
        for(i=0u;i<2u;++i){d->machine->ram[0x04acu+first*4u+i]=0x20u;
            d->machine->ram[0x04aeu+first*4u+i]=0x30u;
            d->machine->ram[0x04acu+second*4u+i]=0x28u;
            d->machine->ram[0x04aeu+second*4u+i]=0x38u;}
        d->machine->ram[0x04acu+first*4u+axis]=values[rank%6u];rank/=6u;
        d->machine->ram[0x04aeu+first*4u+axis]=values[rank%6u];rank/=6u;
        d->machine->ram[0x04acu+second*4u+axis]=values[rank%6u];rank/=6u;
        d->machine->ram[0x04aeu+second*4u+axis]=values[rank%6u];
        if(k==2u){d->machine->ram[9u]=1u;d->machine->ram[0x0747u]=0u;
            d->machine->ram[0x03d6u]=0u;d->machine->ram[0x079fu]=1u;}
        if(k==3u){d->machine->ram[9u]=0u;d->machine->ram[0x0024u+slot]=1u;
            for(i=0u;i<5u;++i){d->machine->ram[0x000fu+i]=0u;d->machine->ram[0x001eu+i]=0u;}
            d->machine->ram[0x0013u]=1u;d->machine->ram[0x001au]=2u;d->machine->ram[0x03dcu]=0u;}
        if(k==4u){local=n-10368u;d->machine->ram[0x0499u]=(unsigned char)(local%3u);
            d->machine->ram[0x0499u+second]=(unsigned char)((local/3u)%12u);
            d->machine->ram[0x03adu]=(unsigned char)(local*37u);
            d->machine->ram[0x03b8u]=(unsigned char)(local*53u);
            d->machine->ram[0x03aeu]=(unsigned char)(local*37u+4u);
            d->machine->ram[0x03b9u]=(unsigned char)(local*53u+4u);}
        initial_x=(unsigned char)(k==0u?n%18u*4u:(k==1u?first*4u:(k==4u?second:slot)));
        initial_y=(unsigned char)(second*4u);
        rec[0]=(unsigned char)k;rec[1]=initial_x;rec[2]=initial_y;
        memcpy(rec+6u,d->machine->ram,2048u);
        if(k==4u){if(!run(d->machine,0xe29cu,0u,0u)||
            !run(d->machine,0xe29cu,(unsigned char)second,1u)){ok=0;break;}}
        ok=run(d->machine,k==1u?0xe327u:(k==2u?0xd7c4u:(k==3u?0xd6d9u:0xe325u)),initial_x,initial_y);
        rec[3]=d->machine->x;rec[4]=d->machine->y;rec[5]=d->machine->p&1u;
        memcpy(rec+2054u,d->machine->ram,2048u);
        if(fwrite(rec,1u,sizeof(rec),f)!=sizeof(rec))ok=0;
    }
    if(fclose(f)!=0)ok=0;(void)core_driver_destroy(d);
    printf("cases=%u maxsteps=%u hammer-returns=%u fireball-returns=%u\n",n,maxsteps,hammer_returns,fireball_returns);
    for(i=0u;i<99u;++i)if(visited[i])printf("pc=%04x\n",0xe325u+i);
    for(b=0u;b<14u;++b)printf("branch=%04x taken=%u fallthrough=%u\n",branch_pc[b],taken[b],fall[b]);
    return ok?0:66;
}
