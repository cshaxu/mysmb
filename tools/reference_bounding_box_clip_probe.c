/* Bounded original-ROM screen-clipping entry proof; no ROM modifications. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 4096u
#define LIMIT 524288u
static const unsigned short branches[6]={0xe2f5u,0xe2fau,0xe301u,0xe30fu,0xe313u,0xe31au};
static unsigned int taken[6],fall[6];
static int ready(core_machine *m)
{
    core_run_result r;unsigned int n;
    for(n=0u;n<LIMIT;++n) {
        if(m->pc==0x8181u)return 1;
        if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;
    }
    return 0;
}
int main(int argc,char **argv)
{
    static core_machine baseline;
    static const unsigned char pages[8]={0u,1u,0x7fu,0xfeu,0xffu,2u,0xffu,0u};
    unsigned char head[12]={'M','S','C','L',1u,0u,0u,0u,0u,16u,0u,0u};
    unsigned char rec[4100],visited[71];
    core_driver *d=NULL;core_driver_options options={0u,LIB_FALSE};
    core_run_result r;FILE *f;unsigned int n,i,g,steps,pc,b,maxsteps=0u;int ok=1;
    unsigned char obj,offset,middle_page,object_page;
    time_t start=time(NULL);
    if(argc!=3)return 64;
    if(core_driver_create(&d,&options)!=LIB_STATUS_OK||
       !core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    memcpy(&baseline,d->machine,sizeof(baseline));
    f=fopen(argv[2],"wb");if(f==NULL)return 65;
    memset(visited,0,sizeof(visited));
    if(fwrite(head,1u,sizeof(head),f)!=sizeof(head))ok=0;
    for(n=0u;n<CASES&&ok;++n) {
        if(time(NULL)-start>120){ok=0;break;}
        memcpy(d->machine,&baseline,sizeof(baseline));
        g=n/256u;obj=(unsigned char)(n%18u);offset=(unsigned char)(obj*4u);
        for(i=0u;i<2048u;++i)d->machine->ram[i]=(unsigned char)(i*13u+n);
        d->machine->ram[8u]=(unsigned char)(n%9u);
        d->machine->ram[0x071au]=pages[g%8u];d->machine->ram[0x071cu]=(unsigned char)n;
        middle_page=(unsigned char)(pages[g%8u]+((n&255u)>=128u?1u:0u));
        switch(g%8u) {
        case 2u:object_page=(unsigned char)(middle_page+1u);break;
        case 3u:object_page=(unsigned char)(middle_page-1u);break;
        case 4u:object_page=255u;break;
        case 5u:object_page=0u;break;
        case 7u:object_page=pages[g%8u];break;
        default:object_page=middle_page;break;
        }
        d->machine->ram[0x006du+obj]=object_page;
        d->machine->ram[0x0086u+obj]=(unsigned char)(n*37u+g*17u);
        d->machine->ram[0x04acu+offset]=(unsigned char)(g<8u?n:255u-n);
        d->machine->ram[0x04aeu+offset]=(unsigned char)(n*53u+g*31u);
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        d->machine->a=0x77u;d->machine->x=obj;d->machine->y=offset;
        d->machine->s=0xfdu;d->machine->pc=0xe2deu;
        rec[0]=obj;rec[1]=d->machine->ram[8u];memcpy(rec+4u,d->machine->ram,2048u);
        for(steps=0u;steps<LIMIT&&d->machine->pc!=0x8001u;++steps) {
            pc=d->machine->pc;
            if(pc>=0xe2deu&&pc<=0xe324u)visited[pc-0xe2deu]=1u;
            if(core_machine_debug_step(d->machine,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)break;
            for(b=0u;b<6u;++b)if(pc==branches[b]) {
                if(d->machine->pc==pc+2u)++fall[b];else ++taken[b];
            }
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
    for(i=0u;i<71u;++i)if(visited[i])printf("pc=%04x\n",0xe2deu+i);
    for(b=0u;b<6u;++b)printf("branch=%04x taken=%u fallthrough=%u\n",branches[b],taken[b],fall[b]);
    return ok?0:66;
}
