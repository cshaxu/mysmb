/* Controlled original-ROM probe for M2 T64 S27 KillEnemyAboveBlock. */
#include <stdio.h>
#include <string.h>
#include "core/driver.h"
#include "core/machine.h"
#define ENTRY 0xe18bu
#define RETURN_PC 0x8001u
#define NMI_RETURN 0x8181u
#define RECORD_BYTES 4112u
#define CASES 4u
#define MAX_STEPS 524288u
static int ready(core_machine*m){core_run_result r;unsigned int n;for(n=0u;n<MAX_STEPS;++n){if(m->pc==NMI_RETURN)return 1;if(core_machine_debug_step(m,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)return 0;}return 0;}
static void prepare(core_machine*m,unsigned int n){static const unsigned char id[CASES]={0u,5u,13u,6u};static const unsigned char y[CASES]={0x20u,0x40u,0xfeu,0x60u};static const unsigned char state[CASES]={0u,0x80u,0x1fu,0xe0u};memset(m->ram,0,2048u);m->ram[0x0016u+2u]=id[n];m->ram[0x00cfu+2u]=y[n];m->ram[0x001eu+2u]=state[n];m->ram[0x01feu]=0u;m->ram[0x01ffu]=0x80u;m->a=0u;m->x=2u;m->y=0u;m->s=0xfdu;m->pc=ENTRY;}
int main(int argc,char**argv){static const unsigned char head[8]={'M','S','K','B',1u,CASES,0u,0u};core_driver*d;core_run_result r;unsigned char rec[RECORD_BYTES];FILE*f;unsigned int i,n;int ok;if(argc!=3)return 64;f=fopen(argv[2],"wb");if(f==NULL||fwrite(head,1u,sizeof(head),f)!=sizeof(head)){if(f!=NULL)fclose(f);return 65;}ok=1;for(i=0u;i<CASES&&ok;++i){d=NULL;if(core_driver_create(&d,&(core_driver_options){0u,LIB_FALSE})!=LIB_STATUS_OK||!core_driver_set_media(d,argv[1],LIB_STORAGE_MEDIUM_READONLY)||!ready(d->machine)){if(d!=NULL)(void)core_driver_destroy(d);ok=0;break;}prepare(d->machine,i);memset(rec,0,sizeof(rec));rec[0]=(unsigned char)ENTRY;rec[1]=(unsigned char)(ENTRY>>8u);rec[3]=d->machine->x;rec[11]=(unsigned char)i;memcpy(rec+16u,d->machine->ram,2048u);for(n=0u;n<MAX_STEPS&&d->machine->pc!=RETURN_PC;++n)if(core_machine_debug_step(d->machine,1u,1024u,&r)!=LIB_STATUS_OK||r.trap_valid)break;if(d->machine->pc!=RETURN_PC)ok=0;rec[6]=d->machine->a;rec[12]=(unsigned char)d->machine->pc;rec[13]=(unsigned char)(d->machine->pc>>8u);memcpy(rec+2064u,d->machine->ram,2048u);if(fwrite(rec,1u,sizeof(rec),f)!=sizeof(rec))ok=0;(void)core_driver_destroy(d);}if(fclose(f)!=0)ok=0;return ok?0:66;}
