/* Real fireball scan, hit, init and floating-score return consumers. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "core/driver.h"
#include "core/machine.h"
#define CASES 3584u
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
    static unsigned char prg[32768];
    static const unsigned short seams[4]={0xd72cu,0xd741u,0xd764u,0xd7bfu};
    static const unsigned char ids[16]={0u,1u,2u,5u,6u,7u,8u,9u,10u,12u,13u,14u,17u,20u,21u,45u};
    static const unsigned char health[4]={0u,1u,2u,0xffu};
    static const unsigned char ys[8]={0u,1u,0x78u,0x80u,0xe6u,0xe7u,0xf0u,0xffu};
    unsigned char header[12]={'M','S','F','H',1u,0u,0u,0u,0u,14u,0u,0u};
    unsigned char record[4100],slot,kind,previous_opcode,target,fireball;
    unsigned int n,k,i,b,steps,maxsteps=0u,observed[4]={0u},multi=0u,hits,geometry=0u;
    core_driver *d=NULL;core_driver_options opt={0u,LIB_FALSE};
    core_run_result result;FILE *file;time_t start=time(NULL);int ok=1;
    if(argc!=3)return 64;
    file=fopen(argv[1],"rb");
    if(!file||fseek(file,16L,SEEK_SET)!=0||fread(prg,1u,sizeof(prg),file)!=sizeof(prg))return 65;
    fclose(file);
    if(core_driver_create(&d,&opt)!=LIB_STATUS_OK||
        !core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine))return 65;
    memcpy(&baseline,d->machine,sizeof(baseline));
    file=fopen(argv[2],"wb");if(!file)return 65;
    if(fwrite(header,1u,12u,file)!=12u)ok=0;
    for(n=0u;n<CASES&&ok;++n){
        if(time(NULL)-start>120){ok=0;break;}
        kind=(unsigned char)(n>=3072u);k=kind==0u?n%512u:(n-3072u)%256u;
        slot=(unsigned char)(kind==0u?n/512u:(n-3072u)/256u);
        fireball=(unsigned char)(kind==0u?k%2u:slot);hits=0u;
        memcpy(d->machine,&baseline,sizeof(baseline));memset(d->machine->ram,0,2048u);
        d->machine->ram[8u]=fireball;d->machine->ram[1u]=slot;
        d->machine->ram[0x071au]=1u;d->machine->ram[0x071cu]=(unsigned char)(k*3u);
        d->machine->ram[0x0086u]=(unsigned char)(k*7u);d->machine->ram[0x006du]=1u;
        d->machine->ram[0x0483u]=health[k/16u%4u];
        d->machine->ram[0x075fu]=(unsigned char)(kind==0u?k/64u:k/32u);
        d->machine->ram[0x074eu]=(unsigned char)(k/8u%2u);
        d->machine->ram[0x06cbu]=0x55u;
        for(i=0u;i<6u;++i){
            d->machine->ram[0x000fu+i]=1u;d->machine->ram[0x0016u+i]=ids[k%16u];
            d->machine->ram[0x001eu+i]=(unsigned char)(kind==0u?k*13u:k/16u%4u==1u?0x20u:k/16u%4u==2u?2u:0u);
            d->machine->ram[0x006eu+i]=(unsigned char)(k/128u%3u);
            d->machine->ram[0x0087u+i]=(unsigned char)(k*13u+i*7u);
            d->machine->ram[0x00cfu+i]=ys[k/16u%8u];
            d->machine->ram[0x00b6u+i]=1u;
            d->machine->ram[0x0058u+i]=0x41u;d->machine->ram[0x00a0u+i]=0x42u;
            d->machine->ram[0x0434u+i]=0x43u;
            b=0x04b0u+i*4u;
            d->machine->ram[b]=(unsigned char)(kind!=0u&&k/64u%2u!=0u?0xb0u:0x78u);
            d->machine->ram[b+1u]=0x78u;d->machine->ram[b+2u]=(unsigned char)(d->machine->ram[b]+16u);
            d->machine->ram[b+3u]=0x88u;
        }
        if(kind==0u&&k>=256u){
            target=(unsigned char)((slot+1u)%6u);
            d->machine->ram[0x000fu+slot]=(unsigned char)(0x80u|target);
            d->machine->ram[0x0016u+target]=(unsigned char)(k<384u?45u:2u);
        }
        if(kind!=0u){
            d->machine->ram[0x0024u+slot]=(unsigned char)(k/16u==13u?0u:k/16u==14u?0x80u:1u);
            d->machine->ram[9u]=(unsigned char)(k/16u==15u?1u:0u);
            for(i=0u;i<5u;++i){
                if(k/16u==11u)d->machine->ram[0x000fu+i]=0u;
                if(k/16u==12u)d->machine->ram[0x03d8u+i]=1u;
            }
            b=0x04c8u+slot*4u;d->machine->ram[b]=0x80u;d->machine->ram[b+1u]=0x80u;
            d->machine->ram[b+2u]=0x88u;d->machine->ram[b+3u]=0x88u;
        }
        for(i=0x109u;i<=0x139u;++i)d->machine->ram[i]=0x55u;
        d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;
        d->machine->pc=kind==0u?0xd73eu:0xd6d9u;d->machine->x=slot;d->machine->s=0xfdu;
        d->machine->a=0x77u;d->machine->y=0x44u;
        previous_opcode=0u;
        record[0]=kind;record[1]=slot;memcpy(record+4u,d->machine->ram,2048u);
        for(steps=0u;steps<LIMIT&&d->machine->pc!=0x8001u;++steps){
            for(i=0u;i<4u;++i)if(previous_opcode==0x60u&&d->machine->pc==seams[i]){
                ++observed[i];
                if(i==0u){++hits;if(d->machine->ram[0x0024u+fireball]!=0x80u)ok=0;}
                if(i==1u&&(d->machine->x!=d->machine->ram[8u]||d->machine->a!=d->machine->ram[0x03aeu]))ok=0;
                if(i==2u&&(d->machine->a!=0u||d->machine->ram[0x00a0u+d->machine->x]!=0u||d->machine->ram[0x0434u+d->machine->x]!=0u))ok=0;
                if(i==3u){
                    target=d->machine->x;
                    if(target!=d->machine->ram[1u]||d->machine->a!=d->machine->ram[0x03aeu]||
                       d->machine->ram[0x012cu+target]!=0x30u||
                       d->machine->ram[0x011eu+target]!=d->machine->ram[0x00cfu+target]||
                       d->machine->ram[0x0117u+target]!=d->machine->ram[0x03aeu])ok=0;
                }
            }
            if(kind!=0u&&d->machine->pc==0xe327u){++geometry;
                if(d->machine->y!=(unsigned char)(0x1cu+fireball*4u))ok=0;
            }
            if(!ok){printf("seam failure case=%u pc=%04x x=%02x\n",n,d->machine->pc,d->machine->x);break;}
            previous_opcode=d->machine->pc>=0x8000u?prg[d->machine->pc-0x8000u]:0u;
            if(core_machine_debug_step(d->machine,1u,1024u,&result)!=LIB_STATUS_OK||result.trap_valid){ok=0;break;}
        }
        if(d->machine->pc!=0x8001u)ok=0;
        if(hits>1u)++multi;if(steps>maxsteps)maxsteps=steps;
        record[2]=d->machine->a;record[3]=d->machine->x;memcpy(record+2052u,d->machine->ram,2048u);
        if(fwrite(record,1u,sizeof(record),file)!=sizeof(record))ok=0;
    }
    if(fclose(file)!=0)ok=0;(void)core_driver_destroy(d);
    printf("cases=%u maxsteps=%u geometry=%u multi-hit-scans=%u\n",n,maxsteps,geometry,multi);
    for(i=0u;i<4u;++i){printf("return=%04x observed=%u\n",seams[i],observed[i]);if(observed[i]==0u)ok=0;}
    if(n!=CASES||multi==0u||geometry==0u)ok=0;
    return ok?0:66;
}
