#include "game/frame_snapshot.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_frame_snapshot snapshot;

    mysmb_game_initialize(&game);
    game.frame_number = 42UL;
    game.ram[0x0200U] = 0x12U;
    game.ram[0x00f1U] = 0x34U;
    game.name_table[1][0x03ffU] = 0x56U;
    game.palette[3U] = 0x21U;
    game.ppu_control_0 = 0x90U;
    game.ppu_mask = 0x1eU;
    game.ppu_name_table = 2U;
    game.scroll_x = 0x40U;
    game.scroll_y = 0x80U;
    mysmb_frame_snapshot_capture(&game, &snapshot);
    if (snapshot.sequence != 42UL || snapshot.cpu_ram[0x0200U] != 0x12U ||
        snapshot.oam[0U] != 0x12U || snapshot.audio[0U] != 0x34U ||
        snapshot.name_table[1][0x03ffU] != 0x56U || snapshot.palette[3U] != 0x21U ||
        snapshot.ppu_control_0 != 0x90U || snapshot.ppu_mask != 0x1eU ||
        snapshot.ppu_name_table != 2U || snapshot.scroll_x != 0x40U ||
        snapshot.scroll_y != 0x80U) return 1;
    if (snapshot.captured_fields != (MYSMB_FRAME_SNAPSHOT_CPU_RAM |
        MYSMB_FRAME_SNAPSHOT_NAME_TABLES | MYSMB_FRAME_SNAPSHOT_PALETTE |
        MYSMB_FRAME_SNAPSHOT_OAM | MYSMB_FRAME_SNAPSHOT_PPU_STATE |
        MYSMB_FRAME_SNAPSHOT_AUDIO) ||
        mysmb_frame_snapshot_is_complete(&snapshot) != 0U) return 2;
    snapshot.captured_fields = MYSMB_FRAME_SNAPSHOT_REQUIRED;
    snapshot.verified_fields = MYSMB_FRAME_SNAPSHOT_REQUIRED;
    return mysmb_frame_snapshot_is_complete(&snapshot) != 0U ? 0 : 3;
}
