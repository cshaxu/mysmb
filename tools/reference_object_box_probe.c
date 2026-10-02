/* Bounded M2 T64 S33 original-ROM entry matrix; no ROM modifications. */
#include <stdio.h>
#include <string.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 60u
#define LIMIT 524288u
static const unsigned short entries[5] = {0xe22du,0xe236u,0xe243u,0xe24cu,0xe273u};
static unsigned char visited[65536];
static const unsigned short branch_pc[5]={0xe234u,0xe25fu,0xe263u,0xe26eu,0xe27au};
static unsigned int branch_taken[5],branch_fallthrough[5];
static int ready(core_machine *m)
{
    core_run_result r; unsigned int n;
    for(n=0u;n<LIMIT;++n) {
        if(m->pc==0x8181u) return 1;
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid) return 0;
    }
    return 0;
}
static void prepare(core_machine *m,unsigned int kind,unsigned int n)
{
    static const unsigned char xs[12]={0x70u,0x80u,0x90u,0xc0u,0xf8u,0xffu,
        0u,0x30u,0x40u,0x50u,0x60u,0x78u};
    static const unsigned char pages[12]={1u,1u,1u,1u,1u,1u,2u,2u,1u,1u,1u,1u};
    static const unsigned char masks[6]={0u,4u,8u,0x44u,0x48u,0xffu};
    unsigned char slot=(unsigned char)(n%(kind==0u?2u:(kind==1u?9u:6u)));
    unsigned int obj=kind==0u?7u+slot:(kind==1u?9u+slot:1u+slot);
    memset(m->ram,0xa5,2048u);
    m->ram[8u]=slot;
    m->ram[0x071au]=1u;m->ram[0x071bu]=1u;
    m->ram[0x071cu]=0x80u;m->ram[0x071du]=0xffu;
    m->ram[0x03d1u]=masks[n%6u];
    m->ram[0x006du+obj]=pages[n];m->ram[0x0086u+obj]=xs[n];
    m->ram[0x0499u+obj]=(unsigned char)n;
    m->ram[0x03aeu]=0xf7u;m->ram[0x03b9u]=0xe9u;
    m->ram[0x03afu]=0xf7u;m->ram[0x03bau]=0xe9u;
    m->ram[0x03b3u]=0xf7u;m->ram[0x03beu]=0xe9u;
    m->ram[0x01feu]=0u;m->ram[0x01ffu]=0x80u;
    m->a=0x77u;m->x=slot;m->y=0x22u;m->s=0xfdu;m->pc=entries[kind];
}
int main(int argc,char **argv)
{
    unsigned char head[8]={'M','S','B','X',1u,CASES,0u,0u};
    unsigned char rec[4098];
    core_driver *d=NULL;core_driver_options options={0u,LIB_FALSE};
    core_run_result r;FILE *f;unsigned int kind,n,step,pc,b;int ok=1;
    if(argc!=3)return 64;
    if(core_driver_create(&d,&options)!=LIB_STATUS_OK||
        !core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine)) return 65;
    f=fopen(argv[2],"wb");if(f==NULL)return 65;
    if(fwrite(head,1u,8u,f)!=8u)ok=0;
    for(kind=0u;kind<5u&&ok;++kind)for(n=0u;n<12u&&ok;++n) {
        prepare(d->machine,kind,n);
        rec[0]=(unsigned char)kind;rec[1]=d->machine->x;
        memcpy(rec+2u,d->machine->ram,2048u);
        for(step=0u;step<LIMIT&&d->machine->pc!=0x8001u;++step) {
            pc=d->machine->pc;
            visited[d->machine->pc]=1u;
            if(core_machine_debug_step(d->machine,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)break;
            for(b=0u;b<5u;++b)if(pc==branch_pc[b]) {
                if(d->machine->pc==pc+2u)++branch_fallthrough[b];else ++branch_taken[b];
            }
        }
        if(d->machine->pc!=0x8001u)ok=0;
        memcpy(rec+2050u,d->machine->ram,2048u);
        if(fwrite(rec,1u,sizeof(rec),f)!=sizeof(rec))ok=0;
    }
    if(fclose(f)!=0)ok=0;
    (void)core_driver_destroy(d);
    for(pc=0xe22du;pc<=0xe29bu;++pc)if(visited[pc])printf("%04x\n",pc);
    for(b=0u;b<5u;++b)printf("branch=%04x taken=%u fallthrough=%u\n",branch_pc[b],branch_taken[b],branch_fallthrough[b]);
    return ok?0:66;
}
