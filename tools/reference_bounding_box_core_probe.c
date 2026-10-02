/* Direct original-ROM BoundingBoxCore proof; ROM bytes are never patched. */
#include <stdio.h>
#include <string.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 3072u
#define LIMIT 524288u
static int ready(core_machine *m)
{
    core_run_result r; unsigned int n;
    for(n=0u;n<LIMIT;++n) {
        if(m->pc==0x8181u)return 1;
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;
    }
    return 0;
}
int main(int argc,char **argv)
{
    unsigned char head[12]={'M','S','B','C',1u,0u,0u,0u,0u,12u,0u,0u};
    unsigned char rec[4100],visited[66];
    static core_machine baseline;
    core_driver *d=NULL;core_driver_options options={0u,LIB_FALSE};
    core_run_result r;FILE *f;unsigned int n,i,steps,maxsteps=0u;int ok=1;
    unsigned char obj,rel,control,x,y;
    if(argc!=3)return 64;
    if(core_driver_create(&d,&options)!=LIB_STATUS_OK||
       !core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    memcpy(&baseline,d->machine,sizeof(baseline));
    f=fopen(argv[2],"wb");if(f==NULL)return 65;
    memset(visited,0,sizeof(visited));
    if(fwrite(head,1u,sizeof(head),f)!=sizeof(head))ok=0;
    for(n=0u;n<CASES&&ok;++n) {
        memcpy(d->machine,&baseline,sizeof(baseline));
        control=(unsigned char)(n/256u);x=(unsigned char)n;y=(unsigned char)(255u-x);
        obj=(unsigned char)(n%18u);rel=(unsigned char)(n%7u);
        for(i=0u;i<2048u;++i)d->machine->ram[i]=(unsigned char)(i*13u+n);
        d->machine->ram[0x0499u+obj]=control;
        d->machine->ram[0x03adu+rel]=x;d->machine->ram[0x03b8u+rel]=y;
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        d->machine->a=0x77u;d->machine->x=obj;d->machine->y=rel;
        d->machine->s=0xfdu;d->machine->pc=0xe29cu;
        rec[0]=obj;rec[1]=rel;memcpy(rec+4u,d->machine->ram,2048u);
        for(steps=0u;steps<LIMIT&&d->machine->pc!=0x8001u;++steps) {
            if(d->machine->pc>=0xe29cu&&d->machine->pc<=0xe2ddu)
                visited[d->machine->pc-0xe29cu]=1u;
            if(core_machine_debug_step(d->machine,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)break;
        }
        if(d->machine->pc!=0x8001u)ok=0;
        if(steps>maxsteps)maxsteps=steps;
        rec[2]=d->machine->x;rec[3]=d->machine->y;
        memcpy(rec+2052u,d->machine->ram,2048u);
        if(fwrite(rec,1u,sizeof(rec),f)!=sizeof(rec))ok=0;
    }
    if(fclose(f)!=0)ok=0;
    (void)core_driver_destroy(d);
    printf("cases=%u maxsteps=%u\n",n,maxsteps);
    for(i=0u;i<66u;++i)if(visited[i])printf("pc=%04x\n",0xe29cu+i);
    return ok?0:66;
}
