#include "app/game_snapshot.h"
#include <string.h>

void mysmb_game_snapshot_fingerprint(const struct mysmb_game *game,
    mysmb_io_u8 *fingerprint)
{
    mysmb_snapshot_put32(fingerprint,mysmb_snapshot_crc(game->area_prg,game->area_prg_size));
    mysmb_snapshot_put32(fingerprint+4,mysmb_snapshot_crc(game->chr_data,game->chr_data_size));
    mysmb_snapshot_put32(fingerprint+8,mysmb_snapshot_crc(game->title_data,game->title_data_size));
    mysmb_snapshot_put32(fingerprint+12,mysmb_snapshot_crc(game->title_icon_data,game->title_icon_data_size));
}
int mysmb_game_snapshot_capture(const struct mysmb_game *game,
    struct mysmb_io_snapshot *snapshot,const mysmb_io_u8 *fingerprint)
{
    mysmb_io_u8 *out;
    unsigned int i;
    out=snapshot->payload;
    mysmb_snapshot_put32(out,game->frame_number);out+=4;
#define BYTE(field) *out++=game->field
#define ARRAY(field) memcpy(out,game->field,sizeof(game->field));out+=sizeof(game->field)
    BYTE(startup_phase);ARRAY(ram);ARRAY(name_table);ARRAY(visible_oam);
    BYTE(oam_dma_primed);ARRAY(palette);
    BYTE(ppu_control_0);BYTE(ppu_mask);BYTE(ppu_name_table);BYTE(scroll_x);BYTE(scroll_y);
    BYTE(visible_ppu_control_0);BYTE(visible_ppu_mask);BYTE(visible_ppu_name_table);
    BYTE(visible_scroll_x);BYTE(visible_scroll_y);BYTE(visible_sprite0_split);
    BYTE(apu_delta_counter_load);BYTE(apu_channel_enable);BYTE(apu_frame_counter);
    ARRAY(apu_registers);BYTE(apu_write_count);
    for (i=0U;i<MYSMB_APU_WRITE_CAPACITY;++i) {
        *out++=game->apu_writes[i].index;*out++=game->apu_writes[i].value;
    }
    BYTE(area_command_count);
    for (i=0U;i<16U;++i) {
        *out++=game->area_commands[i].column;*out++=game->area_commands[i].row;
        *out++=game->area_commands[i].page;*out++=game->area_commands[i].dispatch_id;
    }
#undef BYTE
#undef ARRAY
    /* Roots compute immutable identity once,not once per rendered frame. */
    memcpy(snapshot->fingerprint,fingerprint,16U);
    return out==snapshot->payload+MYSMB_SNAPSHOT_CORE_BYTES;
}
int mysmb_game_snapshot_valid(const struct mysmb_game *game,
    const struct mysmb_io_snapshot *snapshot)
{
    mysmb_io_u8 fingerprint[16];
    const mysmb_io_u8 *in;
    unsigned int i;
    mysmb_game_snapshot_fingerprint(game,fingerprint);
    in=snapshot->payload;
    if (memcmp(fingerprint,snapshot->fingerprint,16U)!=0 || in[4]!=4U ||
        in[4357]>1U || in[4400]>1U || in[4428]>MYSMB_APU_WRITE_CAPACITY ||
        in[4557]>16U) return 0;
    for (i=0U;i<in[4428];++i)
        if (in[4429U+i*2U]>=24U) return 0;
    return 1;
}
int mysmb_game_snapshot_restore(struct mysmb_game *game,
    const struct mysmb_io_snapshot *snapshot)
{
    const mysmb_io_u8 *in;
    unsigned int i;
    if (!mysmb_game_snapshot_valid(game,snapshot)) return 0;
    in=snapshot->payload;
    /* Validation precedes all writes. Immutable resources stay bound. */
    game->frame_number=mysmb_snapshot_get32(in);in+=4;
#define BYTE(field) game->field=*in++
#define ARRAY(field) memcpy(game->field,in,sizeof(game->field));in+=sizeof(game->field)
    BYTE(startup_phase);ARRAY(ram);ARRAY(name_table);ARRAY(visible_oam);
    BYTE(oam_dma_primed);ARRAY(palette);
    BYTE(ppu_control_0);BYTE(ppu_mask);BYTE(ppu_name_table);BYTE(scroll_x);BYTE(scroll_y);
    BYTE(visible_ppu_control_0);BYTE(visible_ppu_mask);BYTE(visible_ppu_name_table);
    BYTE(visible_scroll_x);BYTE(visible_scroll_y);BYTE(visible_sprite0_split);
    BYTE(apu_delta_counter_load);BYTE(apu_channel_enable);BYTE(apu_frame_counter);
    ARRAY(apu_registers);BYTE(apu_write_count);
    for (i=0U;i<MYSMB_APU_WRITE_CAPACITY;++i) {
        game->apu_writes[i].index=*in++;game->apu_writes[i].value=*in++;
    }
    BYTE(area_command_count);
    for (i=0U;i<16U;++i) {
        game->area_commands[i].column=*in++;game->area_commands[i].row=*in++;
        game->area_commands[i].page=*in++;game->area_commands[i].dispatch_id=*in++;
    }
#undef BYTE
#undef ARRAY
    return 1;
}
mysmb_io_u8 mysmb_game_snapshot_running(const struct mysmb_game *game,
    const struct mysmb_frame *frame)
{
    return (mysmb_io_u8)(frame->operating_mode==1U &&
        frame->operating_mode_task==3U && !mysmb_game_is_paused(game));
}
