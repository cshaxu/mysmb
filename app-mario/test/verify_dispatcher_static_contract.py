"""Lock the shared-C control order for ROM GameMode through ExitEng.

This is source-contract verification: route replay supplies the separate
original-ROM execution evidence.  It deliberately contains no ROM bytes.
"""
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def ordered(text, fragments):
    position = -1
    for fragment in fragments:
        next_position = text.find(fragment, position + 1)
        assert next_position >= 0, fragment
        position = next_position


def source(name):
    return (ROOT / "src" / "game" / name).read_text(encoding="utf-8")


def main():
    dispatcher = source("dispatcher.c")
    ordered(dispatcher, [
        "case 0U: mysmb_area_initialize(game); break;",
        "case 1U: mysmb_game_step_screen_routine(game); break;",
        "case 2U: mysmb_game_secondary_setup(game); break;",
        "case 3U: mysmb_game_core_routine(game); break;",
        "game->ram[0x06fcU] = game->ram[(mysmb_u16)(0x06fcU + game->ram[0x0753U])];",
        "mysmb_game_routines(game);",
        "if (game->ram[0x0772U] >= 3U)",
        "mysmb_game_engine(game);",
    ])
    engine = source("engine.c")
    ordered(engine, [
        "mysmb_game_engine_actors(game, &area_source);",
        "mysmb_oam_get_player_offscreen_bits(game);",
        "mysmb_oam_relative_player_position(game);",
        "mysmb_oam_render_player(game);",
        "mysmb_area_apply_block_replacements(game);",
        "mysmb_game_engine_blocks(game);",
        "mysmb_objects_step_misc(game);",
        "mysmb_game_process_cannons(game);",
        "mysmb_game_process_whirlpools(game);",
        "mysmb_objects_step_flagpole(game);",
        "(void)mysmb_game_run_timer(game);",
        "mysmb_area_step_palette_rotation(game);",
        "mysmb_game_cycle_player_palette(game);",
        "game->ram[MYSMB_FRAME_PREVIOUS_A_B_BUTTONS] =",
        "game->ram[MYSMB_FRAME_PLAYER_LEFT_RIGHT_BUTTONS] = 0U;",
        "mysmb_game_step_area_parser(game);",
    ])
    slots = source("engine_slots.c")
    ordered(slots, [
        "mysmb_fireball_step(game);",
        "for (slot = 0U; slot < 6U; ++slot)",
        "game->ram[0x0008U] = slot;",
        "mysmb_enemy_core_step_slot(game, source, slot);",
        "mysmb_objects_step_floatey_number(game, slot);",
        "game->ram[0x0008U] = 1U;",
        "mysmb_objects_step_block(game, 1U);",
        "game->ram[0x0008U] = 0U;",
        "mysmb_objects_step_block(game, 0U);",
    ])
    tail = source("engine_tail.c")
    ordered(tail, [
        "y_difference = (mysmb_u8)(game->ram[0x00b5U] - 2U);",
        "if ((y_difference & 0x80U) != 0U)",
        "mysmb_player_reset_palette(game);",
        "mysmb_game_get_area_music(game);",
        "mysmb_player_cycle_palette(game, color);",
        "if (game->ram[0x0773U] == 6U) return;",
        "if (game->ram[0x071fU] == 0U)",
        "game->ram[0x073dU] = difference;",
        "game->ram[0x0340U] = 0U;",
        "(void)mysmb_area_parser_task_step(game);",
    ])
    print("dispatcher static contract: passed")


if __name__ == "__main__":
    main()
