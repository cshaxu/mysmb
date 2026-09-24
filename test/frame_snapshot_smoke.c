#include "game/frame_snapshot.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    struct mysmb_frame_snapshot snapshot;
    const mysmb_u8 vertical_vram_command[] = {
        0x20U, 0x00U, 0x81U, 0x5aU, 0U
    };

    mysmb_game_initialize(&game);
    game.ppu_mask = 0x06U;
    game.visible_ppu_mask = 0x1eU;
    game.visible_scroll_y = 0x80U;
    mysmb_game_initialize_name_tables(&game);
    if (game.ppu_mask != 0x06U || game.ram[0x0778U] != 0x10U ||
        game.visible_ppu_mask != 0x1eU || game.visible_scroll_y != 0x80U)
        return 7;
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
    game.visible_ppu_control_0 = 0x90U;
    game.visible_ppu_mask = 0x1eU;
    game.visible_ppu_name_table = 2U;
    game.visible_scroll_x = 0x40U;
    game.visible_scroll_y = 0x80U;
    mysmb_frame_snapshot_capture(&game, &snapshot);
    if (snapshot.sequence != 42UL || snapshot.cpu_ram[0x0200U] != 0x12U ||
        snapshot.oam[0U] != 0x12U || snapshot.audio[0U] != 0x34U ||
        snapshot.name_table[1][0x03ffU] != 0x56U || snapshot.palette[3U] != 0x21U ||
        snapshot.ppu_control_0 != 0x90U || snapshot.ppu_mask != 0x1eU ||
        snapshot.ppu_name_table != 2U || snapshot.scroll_x != 0x40U ||
        snapshot.scroll_y != 0x80U || snapshot.ppu_address != 0x0a08U) return 1;
    if (snapshot.captured_fields != (MYSMB_FRAME_SNAPSHOT_CPU_RAM |
        MYSMB_FRAME_SNAPSHOT_NAME_TABLES | MYSMB_FRAME_SNAPSHOT_PALETTE |
        MYSMB_FRAME_SNAPSHOT_OAM | MYSMB_FRAME_SNAPSHOT_PPU_STATE |
        MYSMB_FRAME_SNAPSHOT_AUDIO) ||
        mysmb_frame_snapshot_is_complete(&snapshot) != 0U) return 2;
    snapshot.captured_fields = MYSMB_FRAME_SNAPSHOT_REQUIRED;
    snapshot.verified_fields = MYSMB_FRAME_SNAPSHOT_REQUIRED;
    if (mysmb_frame_snapshot_is_complete(&snapshot) == 0U) return 3;

    /* NMI WriteBufferToScreen derives $2000 d2 from a command's d7.  The
     * source mirror keeps that bit when the NMI restores output. */
    input.buttons = 0U;
    game.ppu_control_0 = 0x90U;
    game.ppu_mask = 0U;
    game.ram[0x0774U] = 0U;
    if (mysmb_game_apply_vram_commands(&game, vertical_vram_command,
            (mysmb_u16)sizeof(vertical_vram_command)) == 0U ||
        game.ppu_control_0 != 0x94U) return 4;
    mysmb_game_tick(&game, &input, &frame);
    mysmb_frame_snapshot_capture(&game, &snapshot);
    if (snapshot.ppu_control_0 != 0x94U || snapshot.ppu_mask != 0x1eU ||
        game.ram[0x0778U] != 0x14U || game.ram[0x0779U] != 0x1eU) return 5;
    game.ram[0x0774U] = 1U;
    mysmb_game_tick(&game, &input, &frame);
    mysmb_frame_snapshot_capture(&game, &snapshot);
    return snapshot.ppu_mask == 0x06U && game.ram[0x0779U] == 0x06U ? 0 : 6;
}
