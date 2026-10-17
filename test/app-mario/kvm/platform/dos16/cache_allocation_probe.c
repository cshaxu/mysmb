/* DOS-only integration probe. Production main/root are compiled separately
 * with symbol substitutions; no implementation file is included here.
 * Faults deny allocations, never fabricate an allocation success. */
#include <dos.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "platform/dos16/dos16_root.h"
#define MK_FP(segment,offset) ((void far *)(((unsigned long)(segment)<<16)|(unsigned)(offset)))

struct allocation {void far *pointer;unsigned bytes;unsigned char near_heap;};
struct census {unsigned long free_bytes,largest,psp_bytes;unsigned valid;};
static struct allocation blocks[16];
static unsigned mode,live,errors,denials,near_attempts,far_attempts,fit_count,bands;
static unsigned retained[3],near_a,exited,observed;
static unsigned long peak,requested,largest_fit[2];
static struct census before,during,after;
int cache_product_main(void);

static void memory_census(struct census *out)
{
    union REGS in,regs;
    struct SREGS segments;
    unsigned segment,next,owner,size,count=0,type;
    unsigned char far *mcb;
    memset(out,0,sizeof(*out));memset(&in,0,sizeof(in));
    segread(&segments);in.h.ah=0x52;
    intdosx(&in,&regs,&segments);
    segment=*(unsigned far *)MK_FP(segments.es,regs.x.bx-2U);
    out->psp_bytes=((unsigned long)*(unsigned far *)MK_FP(_psp-1U,3)+1UL)*16UL;
    while(segment<0xa000U && ++count<4096U) {
        mcb=(unsigned char far *)MK_FP(segment,0);
        type=mcb[0];if(type!=0x4dU && type!=0x5aU)return;
        owner=*(unsigned far *)(mcb+1);size=*(unsigned far *)(mcb+3);
        if(!owner) {
            out->free_bytes+=(unsigned long)size*16UL;
            if((unsigned long)size*16UL>out->largest)out->largest=(unsigned long)size*16UL;
        }
        if(type==0x5aU){out->valid=1;return;}
        next=segment+size+1U;if(next<=segment)return;segment=next;
    }
}
static void track(void far *p,unsigned bytes,unsigned near_heap)
{
    unsigned i;
    if(!p)return;
    for(i=0;i<16U;++i)if(!blocks[i].pointer) {
        blocks[i].pointer=p;blocks[i].bytes=bytes;blocks[i].near_heap=(unsigned char)near_heap;
        ++live;requested+=bytes;if(requested>peak)peak=requested;return;
    }
    ++errors;
}
static void untrack(void far *p,unsigned near_heap)
{
    unsigned i;
    if(!p)return;
    for(i=0;i<16U;++i)if(blocks[i].pointer==p) {
        if(blocks[i].near_heap!=near_heap)++errors;
        requested-=blocks[i].bytes;blocks[i].pointer=0;--live;return;
    }
    ++errors;
}
void near * cdecl cache_nmalloc(size_t bytes)
{
    void near *p;
    if(bytes==MYSMB_PPU_CHR_DECODED_BYTES) {
        ++near_attempts;
        if(mode==1U || mode==4U){++denials;return 0;}
    }
    p=_nmalloc(bytes);
    /* A null near pointer cast may become DS:0000, not a null far pointer. */
    if(p)track((void far *)p,bytes,1U);
    return p;
}
void far * cdecl cache_fmalloc(size_t bytes)
{
    void far *p;
    if(bytes==MYSMB_PPU_CHR_DECODED_BYTES)++far_attempts;
    if((mode==1U && bytes==MYSMB_PPU_CHR_DECODED_BYTES) ||
        (mode==2U && bytes==MYSMB_PPU_BACKGROUND_BYTES) ||
        (mode==3U && bytes==MYSMB_PPU_BACKGROUND_SECOND_BYTES)) {
        ++denials;return 0;
    }
    p=_fmalloc(bytes);track(p,bytes,0U);return p;
}
void cdecl cache_nfree(void near *p){untrack((void far *)p,1U);_nfree(p);}
void cdecl cache_ffree(void far *p){untrack(p,0U);_ffree(p);}
int cdecl cache_intdos(union REGS *in,union REGS *out)
{
    int result=intdos(in,out);
    if(in->h.ah==0x48U && in->x.bx==0xffffU) {
        if(fit_count<2U)largest_fit[fit_count]=(unsigned long)out->x.bx*16UL;
        ++fit_count,bands;
        if((mode==5U && fit_count==1U) || (mode==6U && fit_count==2U)) {out->x.bx=0U;++denials;}
    }
    return result;
}
static struct mysmb_dos16_root *observed_root;
static int (*original_palette)(void *,const struct mysmb_palette_video_source *);
static int (*original_rows)(void *,mygames_kvm_u16,mygames_kvm_u16,
    struct mygames_kvm_video_band *);
static int observe_rows(void *context,mygames_kvm_u16 first,mygames_kvm_u16 rows,
    struct mygames_kvm_video_band *band)
{
    if(!original_rows(context,first,rows,band))return 0;
    if(band->pixels!=observed_root->ppu_frame.pixels){++errors;return 0;}
    ++bands;return 1;
}
static int observe_palette(void *context,const struct mysmb_palette_video_source *source)
{
    struct mysmb_palette_video_source copy=*source;
    original_rows=source->rows.read_rows;copy.rows.read_rows=observe_rows;
    return original_palette(context,&copy);
}
void cache_observed_step(struct mysmb_dos16_root *root)
{
    if(root->present_palette_rows!=observe_palette) {
        observed_root=root;original_palette=root->present_palette_rows;
        root->present_palette_rows=observe_palette;
    }
    mysmb_dos16_root_step(root);
    if(root->ppu_cache_attempted && !observed) {
        observed=1U;memory_census(&during);
        retained[0]=root->ppu_workspace.decoded!=0;
        retained[1]=root->ppu_workspace.bg!=0;
        retained[2]=root->ppu_workspace.bg_second!=0;
        near_a=root->ppu_cache_near;exited=root->control.exit_requested;
        /* Bounded diagnostic only; capture the root's decision before exit. */
        root->control.exit_requested=1U;
    }
}
int main(void)
{
    unsigned i,result;
    char far *tail=(char far *)MK_FP(_psp,0x81);
    FILE *log;
    for(i=0;i<*(unsigned char far *)MK_FP(_psp,0x80);++i)
        if(tail[i]>='0' && tail[i]<='6'){mode=(unsigned)(tail[i]-'0');break;}
    /* This probe owns its numeric option, not the product option parser. */
    *(unsigned char far *)MK_FP(_psp,0x80)=0U;
    memory_census(&before);
    result=(unsigned)cache_product_main();
    memory_census(&after);
    log=fopen("CACHE.LOG","a");if(!log)return 90;
    fprintf(log,"mode=%u result=%u observed=%u A=%u B=%u C=%u nearA=%u exit=%u live=%u errors=%u denied=%u near_try=%u far_try=%u bands=%u peak=%lu\n",
        mode,result,observed,retained[0],retained[1],retained[2],near_a,
        exited,live,errors,denials,near_attempts,far_attempts,bands,peak);
    fprintf(log,"before valid=%u psp=%lu free=%lu largest=%lu\n",before.valid,before.psp_bytes,before.free_bytes,before.largest);
    fprintf(log,"during valid=%u psp=%lu free=%lu largest=%lu\n",during.valid,during.psp_bytes,during.free_bytes,during.largest);
    fprintf(log,"after valid=%u psp=%lu free=%lu largest=%lu\n",after.valid,after.psp_bytes,after.free_bytes,after.largest);
    fprintf(log,"fit count=%u B=%lu C=%lu\n",fit_count,largest_fit[0],largest_fit[1]);
    fclose(log);
    return !observed || live || errors || !before.valid || !during.valid || !after.valid?91:result;
}
