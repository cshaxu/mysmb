#include "platform/dos16/retained_background.h"
#include "ppu/frame.h"

/* Presentation is synchronous, so one small far scratch tile is sufficient
 * for the 16-bit ABI and avoids a conventional full-frame allocation. */
static mygames_kvm_u8 MYGAMES_KVM_FAR tile_slots[64];
/* 1,920 coordinates at two bytes each.  This bounded far staging replaces
 * four full scans of the PPU damage bitmap during a plane-ordered update. */
static mygames_kvm_u16 MYGAMES_KVM_FAR changed_tiles[1920];

int mysmb_dos16_retained_address(mygames_kvm_u16 x,mygames_kvm_u16 y,
    mygames_kvm_u8 *plane,mygames_kvm_u16 *offset)
{
    if(!plane || !offset || x>=MYSMB_DOS16_RETAINED_WIDTH ||
        y>=MYSMB_DOS16_RETAINED_HEIGHT)return 0;
    *plane=(mygames_kvm_u8)(x&3U);
    *offset=(mygames_kvm_u16)(y*MYSMB_DOS16_RETAINED_STRIDE+(x>>2U));
    return 1;
}
int mysmb_dos16_retained_tile_address(mygames_kvm_u8 table,mygames_kvm_u8 row,
    mygames_kvm_u8 column,mygames_kvm_u8 vertical_copy,mygames_kvm_u8 *plane,
    mygames_kvm_u16 *offset)
{
    if(table>=2U || row>=30U || column>=32U || vertical_copy>=2U)return 0;
    return mysmb_dos16_retained_address((mygames_kvm_u16)table*256U+column*8U,
        (mygames_kvm_u16)vertical_copy*240U+row*8U,plane,offset);
}
int mysmb_dos16_retained_background_apply(const struct mysmb_ppu_frame_view *view,
    mysmb_dos16_retained_tile_writer writer,void *context)
{
    struct mysmb_ppu_background_damage damage;
    mygames_kvm_u16 i;
    mygames_kvm_u8 table,row,column;
    if(!writer || !mysmb_ppu_frame_background_damage(view,&damage))return 0;
    for(i=0U;i<1920U;++i) {
        if((damage.tiles[i>>3U]&(mygames_kvm_u8)(1U<<(i&7U)))==0U)continue;
        table=(mygames_kvm_u8)(i/960U);
        row=(mygames_kvm_u8)((i%960U)/32U);
        column=(mygames_kvm_u8)(i&31U);
        if(!mysmb_ppu_frame_background_tile_slots(view,table,row,column,
            tile_slots,sizeof(tile_slots)) || !writer(context,table,row,column,tile_slots))return 0;
    }
    return 1;
}

int mysmb_dos16_retained_background_apply_planes(const struct mysmb_ppu_frame_view *view,
    mysmb_dos16_retained_plane_tile_writer writer,void *context)
{
    struct mysmb_ppu_background_damage damage;
    mygames_kvm_u16 i,count;
    mygames_kvm_u8 table,row,column,plane;
    if(!writer || !mysmb_ppu_frame_background_damage(view,&damage))return 0;
    if(!damage.count)return 1;
    count=0U;
    for(i=0U;i<1920U;++i)
        if((damage.tiles[i>>3U]&(mygames_kvm_u8)(1U<<(i&7U)))!=0U)
            changed_tiles[count++]=i;
    if(count!=damage.count)return 0;
    /* A tile begins on a four-pixel boundary, so each physical plane gets
     * its byte lane in a single complete pass.  Re-querying the immutable
     * prepared PPU output trades RAM for no storage and avoids thousands of
     * VGA sequencer writes on a full invalidation. */
    for(plane=0U;plane<4U;++plane)for(i=0U;i<count;++i) {
        mygames_kvm_u16 tile_index=changed_tiles[i];
        table=(mygames_kvm_u8)(tile_index/960U);
        row=(mygames_kvm_u8)((tile_index%960U)/32U);
        column=(mygames_kvm_u8)(tile_index&31U);
        if(!mysmb_ppu_frame_background_tile_slots(view,table,row,column,
            tile_slots,sizeof(tile_slots)) ||
            !writer(context,plane,table,row,column,tile_slots))return 0;
    }
    return 1;
}
