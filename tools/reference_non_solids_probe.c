/* Controlled original-ROM probe for M2 T64 S30 ChkForNonSolids. */
#include <stdio.h>
#include <string.h>
#include "core/driver.h"
#include "core/machine.h"
#define ENTRY 0xe1b5u
#define RETURN_PC 0x8001u
#define NMI_RETURN 0x8181u
#define RECORD_BYTES 16u
#define CASES 8u
#define MAX_STEPS 524288u
static int ready(core_machine*m){core_run_result r;unsigned int n;for(n=0u;n<MAX_STEPS;++n){if(m->pc==NMI_RETURN)return 1;if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;}return 0;}
int main(int argc,char**argv){static const unsigned char values[CASES]={0x26u,0xc2u,0xc3u,0x5fu,0x60u,0u,0x23u,0x61u};static const unsigned char head[8]={'M','S','N','S',1u,CASES,0u,0u};core_driver*d;core_run_result r;unsigned char rec[RECORD_BYTES];FILE*f;unsigned int i,n;int ok;if(argc!=3)return 64;f=fopen(argv[2],"wb");if(f==NULL||fwrite(head,1u,sizeof(head),f)!=sizeof(head)){if(f!=NULL)fclose(f);return 65;}ok=1;for(i=0u;i<CASES&&ok;++i){d=NULL;if(core_driver_create(&d,&(core_driver_options){0u,LIB_FALSE})!=LIB_STATUS_OK||!core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine)){if(d!=NULL)(void)core_driver_destroy(d);ok=0;break;}memset(d->machine->ram,0,2048u);d->machine->ram[0x01feu]=0u;d->machine->ram[0x01ffu]=0x80u;d->machine->a=values[i];d->machine->x=0u;d->machine->y=0u;d->machine->s=0xfdu;d->machine->pc=ENTRY;memset(rec,0,sizeof(rec));rec[0]=(unsigned char)ENTRY;rec[1]=(unsigned char)(ENTRY>>8u);rec[2]=values[i];rec[3]=(unsigned char)i;for(n=0u;n<MAX_STEPS&&d->machine->pc!=RETURN_PC;++n)if(core_machine_debug_step(d->machine,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)break;if(d->machine->pc!=RETURN_PC)ok=0;rec[8]=d->machine->a;rec[9]=d->machine->p;rec[10]=(unsigned char)d->machine->pc;rec[11]=(unsigned char)(d->machine->pc>>8u);if(fwrite(rec,1u,sizeof(rec),f)!=sizeof(rec))ok=0;(void)core_driver_destroy(d);}if(fclose(f)!=0)ok=0;return ok?0:66;}