cmake_minimum_required(VERSION 3.20)

project(mysmb LANGUAGES C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(MYSMB_WIN32_ARCH "host" CACHE STRING "Win32 target label: x86, x64, or host")
set_property(CACHE MYSMB_WIN32_ARCH PROPERTY STRINGS host x86 x64)
set(MYSMB_ROM_PATH "" CACHE FILEPATH "Owner-local SMB1 NROM image")
set(MYSMB_ASM_PATH "" CACHE FILEPATH "Owner-local reviewed SMBDIS listing")
set(MYSMB_OPENNT_CL16 "" CACHE FILEPATH "Owner-local OpenNT 16-bit cl16.exe")
set(MYSMB_DOS_RUNTIME_DIR "" CACHE PATH "Owner-local reviewed 16-bit large-model runtime directory")

set(MYSMB_GAME_SOURCES src/game/boot.c src/game/dispatcher.c src/game/engine.c src/game/engine_slots.c src/game/engine_tail.c src/game/frame_root.c src/game/title_modes.c src/game/terminal_modes.c src/game/game.c src/game/audio.c src/game/area.c src/game/status.c src/game/area/block_metatile.c src/game/enemy/stream.c src/game/enemy/group.c src/game/enemy/init.c src/game/enemy/init_targets.c src/game/enemy/loop.c src/game/enemy/core.c src/game/enemy/dispatch_targets.c src/game/enemy/movement.c src/game/enemy/frenzy.c src/game/player.c src/game/objects.c src/game/fireball/fireball_spawn.c src/game/fireball/fireball_core.c src/game/world/movement.c src/game/world/gravity.c src/game/world/collision.c src/game/world/block_buffer.c src/game/world/bounding_box.c src/game/world/geometry.c src/game/bridge.c src/game/oam/bullet_bill_gfx.c src/game/oam/hammer_gfx.c src/game/oam/firebar_gfx.c src/game/oam/vine_gfx.c src/game/oam/sprite_stacker.c src/game/oam/sprite_dump.c src/game/enemy_bounds.c src/game/oam/power_up_gfx.c src/game/oam/object_position.c src/game/oam/player_gfx.c src/game/oam/fireball_gfx.c src/game/oam/block_gfx.c src/game/oam/goomba_gfx.c src/game/fireball/bubble.c src/game/oam/piranha_gfx.c src/game/oam/cheep_gfx.c src/game/oam/bloober_gfx.c src/game/oam/podoboo_gfx.c src/game/oam/normal_enemy_gfx.c src/game/oam/spiny_gfx.c src/game/oam/hammer_bro_gfx.c src/game/oam/bowser_gfx.c src/game/oam/bowser_flame_gfx.c src/game/endgame_objects.c src/game/oam/flagpole_gfx.c src/game/oam/small_platform_gfx.c src/game/render.c src/game/ppu_frame.c src/game/frame_snapshot.c)
list(APPEND MYSMB_GAME_SOURCES src/game/player/terrain.c src/game/player/terrain_metatiles.c src/game/player/climbing.c src/game/player/pipe_entry.c src/game/player/impede.c src/game/world/metatiles.c)
list(APPEND MYSMB_GAME_SOURCES src/game/area/block_buffer.c)
list(APPEND MYSMB_GAME_SOURCES src/game/area/area_data.c)
list(APPEND MYSMB_GAME_SOURCES src/game/whirlpool.c)
list(APPEND MYSMB_GAME_SOURCES src/game/cannon.c)
list(APPEND MYSMB_GAME_SOURCES src/game/timer.c)
list(APPEND MYSMB_GAME_SOURCES src/game/jumpspring.c)
list(APPEND MYSMB_GAME_SOURCES src/game/vine.c)
list(APPEND MYSMB_GAME_SOURCES src/game/hammer.c)
list(APPEND MYSMB_GAME_SOURCES src/game/coin.c)
list(APPEND MYSMB_GAME_SOURCES src/game/misc.c src/game/score.c src/game/power_up_init.c src/game/power_up.c)
list(APPEND MYSMB_GAME_SOURCES src/game/blocks/head.c src/game/blocks/bump.c src/game/blocks/chunks.c src/game/blocks/lifetime.c src/game/blocks/replacement.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/lifecycle.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/normal.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/special_callers.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/platform_callers.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/podoboo.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/hammer_bro.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/paratroopa.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/x_counter.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/green_paratroopa.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/bloober.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/bullet_bill.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/swimming_cheep.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/firebar.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/flying_cheep.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/lakitu.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/bowser.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/bowser_flame.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/fireworks.c src/game/oam/fireworks_gfx.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/star_flag.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/piranha.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/balance_platform.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/platform.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/actor_slots.c)
list(APPEND MYSMB_GAME_SOURCES src/game/world/fireball_enemy.c)
list(APPEND MYSMB_GAME_SOURCES src/game/world/fireball_hit.c)
list(APPEND MYSMB_GAME_SOURCES src/game/world/hammer_collision.c)
list(APPEND MYSMB_GAME_SOURCES src/game/world/powerup_collision.c src/game/world/player_enemy_collision.c)
list(APPEND MYSMB_GAME_SOURCES src/game/world/enemy_collision.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/platform_collision.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/platform_position.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/firebar_children.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/distance.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/background.c src/game/enemy/jump_terrain.c)
list(APPEND MYSMB_GAME_SOURCES src/game/enemy/side_collision.c)
list(APPEND MYSMB_GAME_SOURCES src/game/scroll.c)
list(APPEND MYSMB_GAME_SOURCES src/game/entry.c)
list(APPEND MYSMB_GAME_SOURCES src/game/player_control.c)
list(APPEND MYSMB_GAME_SOURCES src/game/player_transition.c)
list(APPEND MYSMB_GAME_SOURCES src/game/player_modes.c)
list(APPEND MYSMB_GAME_SOURCES src/game/player_end_level.c)
list(APPEND MYSMB_GAME_SOURCES src/game/player_movement.c)
add_library(mysmb_game STATIC ${MYSMB_GAME_SOURCES})
target_include_directories(mysmb_game PUBLIC src)

if(MSVC)
    target_compile_options(mysmb_game PRIVATE /W4 /WX)
else()
    target_compile_options(mysmb_game PRIVATE -Wall -Wextra -Werror -pedantic)
endif()

add_executable(mysmb_core_smoke test/core_smoke.c)
target_link_libraries(mysmb_core_smoke PRIVATE mysmb_game)
add_executable(mysmb_ram_cold_start_smoke test/ram_cold_start_smoke.c)
target_link_libraries(mysmb_ram_cold_start_smoke PRIVATE mysmb_game)
add_executable(mysmb_reset_root_smoke test/reset_root_smoke.c)
target_link_libraries(mysmb_reset_root_smoke PRIVATE mysmb_game)
add_executable(mysmb_boot_nmi_boundary_smoke test/boot_nmi_boundary_smoke.c)
target_link_libraries(mysmb_boot_nmi_boundary_smoke PRIVATE mysmb_game)
add_executable(mysmb_name_table_init_smoke test/name_table_init_smoke.c)
target_link_libraries(mysmb_name_table_init_smoke PRIVATE mysmb_game)
add_executable(mysmb_vram_address_table_smoke test/vram_address_table_smoke.c)
target_link_libraries(mysmb_vram_address_table_smoke PRIVATE mysmb_game)
add_executable(mysmb_joypad_vram_chain_smoke test/joypad_vram_chain_smoke.c)
target_link_libraries(mysmb_joypad_vram_chain_smoke PRIVATE mysmb_game)
add_executable(mysmb_pseudorandom_smoke test/pseudorandom_smoke.c)
target_link_libraries(mysmb_pseudorandom_smoke PRIVATE mysmb_game)
add_executable(mysmb_timer_root_smoke test/timer_root_smoke.c)
target_link_libraries(mysmb_timer_root_smoke PRIVATE mysmb_game)
add_executable(mysmb_pause_root_smoke test/pause_root_smoke.c)
target_link_libraries(mysmb_pause_root_smoke PRIVATE mysmb_game)
add_executable(mysmb_sprite_root_smoke test/sprite_root_smoke.c)
target_link_libraries(mysmb_sprite_root_smoke PRIVATE mysmb_game)
add_executable(mysmb_top_score_root_smoke test/top_score_root_smoke.c)
target_link_libraries(mysmb_top_score_root_smoke PRIVATE mysmb_game)
add_executable(mysmb_status_arithmetic_smoke test/status_arithmetic_smoke.c)
target_link_libraries(mysmb_status_arithmetic_smoke PRIVATE mysmb_game)
target_link_libraries(mysmb_pseudorandom_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_music_smoke test/area_music_smoke.c)
target_link_libraries(mysmb_area_music_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_entry_smoke test/area_entry_smoke.c)
target_link_libraries(mysmb_area_entry_smoke PRIVATE mysmb_game)
add_executable(mysmb_music_header_smoke test/music_header_smoke.c)
target_link_libraries(mysmb_music_header_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_parser_column_smoke test/area_parser_column_smoke.c)
target_link_libraries(mysmb_area_parser_column_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_parser_terminal_slot_smoke test/area_parser_terminal_slot_smoke.c)
target_link_libraries(mysmb_area_parser_terminal_slot_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_special_object_smoke test/area_special_object_smoke.c)
target_link_libraries(mysmb_area_special_object_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_rope_object_smoke test/area_rope_object_smoke.c)
target_link_libraries(mysmb_area_rope_object_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_coin_row_smoke test/area_coin_row_smoke.c)
target_link_libraries(mysmb_area_coin_row_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_castle_column_smoke test/area_castle_column_smoke.c)
target_link_libraries(mysmb_area_castle_column_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_block_row_column_smoke test/area_block_row_column_smoke.c)
target_link_libraries(mysmb_area_block_row_column_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_cannon_smoke test/area_cannon_smoke.c)
target_link_libraries(mysmb_area_cannon_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_staircase_smoke test/area_staircase_smoke.c)
target_link_libraries(mysmb_area_staircase_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_jumpspring_smoke test/area_jumpspring_smoke.c)
target_link_libraries(mysmb_area_jumpspring_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_item_block_smoke test/area_item_block_smoke.c)
target_link_libraries(mysmb_area_item_block_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_pipe_tail_smoke test/area_pipe_tail_smoke.c)
target_link_libraries(mysmb_area_pipe_tail_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_block_address_smoke test/area_block_address_smoke.c)
target_link_libraries(mysmb_area_block_address_smoke PRIVATE mysmb_game)
add_executable(mysmb_block_buffer_core_smoke test/block_buffer_core_smoke.c)
target_link_libraries(mysmb_block_buffer_core_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_parser_boundary_smoke test/area_parser_boundary_smoke.c)
target_link_libraries(mysmb_area_parser_boundary_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_loop_command_smoke test/area_loop_command_smoke.c)
target_link_libraries(mysmb_area_loop_command_smoke PRIVATE mysmb_game)
add_executable(mysmb_game_entry_dispatch_smoke test/game_entry_dispatch_smoke.c src/game/dispatcher.c)
target_include_directories(mysmb_game_entry_dispatch_smoke PRIVATE src)
add_executable(mysmb_engine_caller_smoke test/engine_caller_smoke.c src/game/engine.c)
target_include_directories(mysmb_engine_caller_smoke PRIVATE src)
add_executable(mysmb_engine_tail_smoke test/engine_tail_smoke.c src/game/engine_tail.c src/game/player_modes.c)
target_include_directories(mysmb_engine_tail_smoke PRIVATE src)
add_executable(mysmb_engine_slots_smoke test/engine_slots_smoke.c src/game/engine_slots.c)
target_include_directories(mysmb_engine_slots_smoke PRIVATE src)
add_executable(mysmb_engine_environment_smoke test/engine_environment_smoke.c src/game/whirlpool.c)
target_include_directories(mysmb_engine_environment_smoke PRIVATE src)
add_executable(mysmb_cannon_smoke test/cannon_smoke.c src/game/cannon.c)
target_include_directories(mysmb_cannon_smoke PRIVATE src)
add_executable(mysmb_cannon_children_smoke test/cannon_children_smoke.c src/game/enemy/core.c src/game/enemy/lifecycle.c src/game/oam/bullet_bill_gfx.c)
target_include_directories(mysmb_cannon_children_smoke PRIVATE src)
add_executable(mysmb_enemy_dispatch_smoke test/enemy_dispatch_smoke.c src/game/enemy/core.c src/game/enemy/lifecycle.c)
target_include_directories(mysmb_enemy_dispatch_smoke PRIVATE src)
add_executable(mysmb_enemy_loop_smoke test/enemy_loop_smoke.c src/game/enemy/loop.c)
target_include_directories(mysmb_enemy_loop_smoke PRIVATE src)
add_executable(mysmb_normal_enemy_movement_smoke test/normal_enemy_movement_smoke.c src/game/enemy/movement.c src/game/world/gravity.c)
target_include_directories(mysmb_normal_enemy_movement_smoke PRIVATE src)
add_executable(mysmb_normal_enemy_caller_smoke test/normal_enemy_caller_smoke.c src/game/enemy/normal.c)
target_include_directories(mysmb_normal_enemy_caller_smoke PRIVATE src)
add_executable(mysmb_enemy_background_caller_smoke test/enemy_background_caller_smoke.c src/game/enemy/background.c src/game/enemy/jump_terrain.c src/game/enemy/distance.c)
target_include_directories(mysmb_enemy_background_caller_smoke PRIVATE src)
add_executable(mysmb_enemy_side_caller_smoke test/enemy_side_caller_smoke.c src/game/enemy/side_collision.c)
target_include_directories(mysmb_enemy_side_caller_smoke PRIVATE src)
add_executable(mysmb_area_helper_smoke test/area_helper_smoke.c)
target_link_libraries(mysmb_area_helper_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_hole_underpart_smoke test/area_hole_underpart_smoke.c)
target_link_libraries(mysmb_area_hole_underpart_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_initialize_smoke test/area_initialize_smoke.c)
target_link_libraries(mysmb_area_initialize_smoke PRIVATE mysmb_game)
add_executable(mysmb_enemy_stream_smoke test/enemy_stream_smoke.c)
target_link_libraries(mysmb_enemy_stream_smoke PRIVATE mysmb_game)
add_executable(mysmb_enemy_no_init_smoke test/enemy_no_init_smoke.c)
target_link_libraries(mysmb_enemy_no_init_smoke PRIVATE mysmb_game)
add_executable(mysmb_enemy_init_handoff_smoke test/enemy_init_handoff_smoke.c src/game/enemy/init.c)
target_include_directories(mysmb_enemy_init_handoff_smoke PRIVATE src)
add_executable(mysmb_enemy_init_snapshot_check test/enemy_init_snapshot_check.c src/game/enemy/init.c)
target_include_directories(mysmb_enemy_init_snapshot_check PRIVATE src)
add_executable(mysmb_enemy_common_init_smoke test/enemy_common_init_smoke.c src/game/enemy/init_targets.c src/game/enemy/lifecycle.c)
target_include_directories(mysmb_enemy_common_init_smoke PRIVATE src)
add_executable(mysmb_lakitu_spiny_chain_smoke test/lakitu_spiny_chain_smoke.c)
target_link_libraries(mysmb_lakitu_spiny_chain_smoke PRIVATE mysmb_game)
add_executable(mysmb_firebar_initialization_smoke test/firebar_initialization_smoke.c src/game/enemy/init_targets.c src/game/enemy/lifecycle.c)
target_include_directories(mysmb_firebar_initialization_smoke PRIVATE src)
add_executable(mysmb_flying_fish_initialization_smoke test/flying_fish_initialization_smoke.c)
target_link_libraries(mysmb_flying_fish_initialization_smoke PRIVATE mysmb_game)
add_executable(mysmb_bowser_flame_initialization_smoke test/bowser_flame_initialization_smoke.c)
target_link_libraries(mysmb_bowser_flame_initialization_smoke PRIVATE mysmb_game)
add_executable(mysmb_fireworks_initialization_smoke test/fireworks_initialization_smoke.c)
target_link_libraries(mysmb_fireworks_initialization_smoke PRIVATE mysmb_game)
add_executable(mysmb_bullet_swimming_fish_smoke test/bullet_swimming_fish_smoke.c)
target_link_libraries(mysmb_bullet_swimming_fish_smoke PRIVATE mysmb_game)
add_executable(mysmb_group_enemy_smoke test/group_enemy_smoke.c)
target_link_libraries(mysmb_group_enemy_smoke PRIVATE mysmb_game)
add_executable(mysmb_small_initializers_smoke test/small_initializers_smoke.c)
target_link_libraries(mysmb_small_initializers_smoke PRIVATE mysmb_game)
add_executable(mysmb_platform_initialization_smoke test/platform_initialization_smoke.c)
target_link_libraries(mysmb_platform_initialization_smoke PRIVATE mysmb_game)
add_executable(mysmb_retainer_call_chain_smoke test/retainer_call_chain_smoke.c src/game/enemy/dispatch_targets.c)
add_executable(mysmb_podoboo_movement_smoke test/podoboo_movement_smoke.c src/game/enemy/podoboo.c)
add_executable(mysmb_hammer_movement_caller_smoke test/hammer_movement_caller_smoke.c src/game/enemy/hammer_bro.c)
add_executable(mysmb_paratroopa_movement_smoke test/paratroopa_movement_smoke.c src/game/enemy/paratroopa.c)
add_executable(mysmb_green_counter_smoke test/green_counter_smoke.c src/game/enemy/green_paratroopa.c src/game/enemy/x_counter.c)
add_executable(mysmb_bloober_movement_smoke test/bloober_movement_smoke.c src/game/enemy/bloober.c src/game/enemy/distance.c)
add_executable(mysmb_bullet_movement_smoke test/bullet_movement_smoke.c src/game/enemy/bullet_bill.c)
add_executable(mysmb_swimming_cheep_movement_smoke test/swimming_cheep_movement_smoke.c src/game/enemy/swimming_cheep.c)
add_executable(mysmb_firebar_chain_smoke test/firebar_chain_smoke.c src/game/enemy/firebar.c)
add_executable(mysmb_lakitu_movement_smoke test/lakitu_movement_smoke.c src/game/enemy/lakitu.c)
add_executable(mysmb_bridge_collapse_smoke test/bridge_collapse_smoke.c src/game/bridge.c)
add_executable(mysmb_bowser_control_smoke test/bowser_control_smoke.c src/game/enemy/bowser.c)
add_executable(mysmb_bowser_graphics_smoke test/bowser_graphics_smoke.c src/game/oam/bowser_gfx.c)
target_include_directories(mysmb_bowser_graphics_smoke PRIVATE src)
add_executable(mysmb_bowser_flame_chain_smoke test/bowser_flame_chain_smoke.c src/game/enemy/bowser_flame.c src/game/oam/bowser_flame_gfx.c)
target_include_directories(mysmb_bowser_flame_chain_smoke PRIVATE src)
add_executable(mysmb_fireworks_lifetime_smoke test/fireworks_lifetime_smoke.c src/game/enemy/fireworks.c)
add_executable(mysmb_star_flag_smoke test/star_flag_smoke.c src/game/enemy/star_flag.c)
target_include_directories(mysmb_star_flag_smoke PRIVATE src)
add_executable(mysmb_piranha_movement_smoke test/piranha_movement_smoke.c src/game/enemy/piranha.c)
target_include_directories(mysmb_piranha_movement_smoke PRIVATE src)
add_executable(mysmb_firebar_spin_smoke test/firebar_spin_smoke.c src/game/enemy/firebar_children.c)
target_include_directories(mysmb_firebar_spin_smoke PRIVATE src)
add_executable(mysmb_balance_platform_smoke test/balance_platform_smoke.c src/game/enemy/balance_platform.c)
target_include_directories(mysmb_balance_platform_smoke PRIVATE src)
add_executable(mysmb_vertical_platform_smoke test/vertical_platform_smoke.c src/game/enemy/platform.c)
target_include_directories(mysmb_vertical_platform_smoke PRIVATE src)
add_executable(mysmb_horizontal_platform_smoke test/horizontal_platform_smoke.c src/game/enemy/platform.c)
target_include_directories(mysmb_horizontal_platform_smoke PRIVATE src)
add_executable(mysmb_lift_platform_smoke test/lift_platform_smoke.c src/game/enemy/platform.c)
target_include_directories(mysmb_lift_platform_smoke PRIVATE src)
add_executable(mysmb_offscreen_bounds_smoke test/offscreen_bounds_smoke.c src/game/enemy/actor_slots.c)
target_include_directories(mysmb_offscreen_bounds_smoke PRIVATE src)
target_include_directories(mysmb_fireworks_lifetime_smoke PRIVATE src)
target_include_directories(mysmb_bowser_control_smoke PRIVATE src)
target_include_directories(mysmb_bridge_collapse_smoke PRIVATE src)
target_include_directories(mysmb_lakitu_movement_smoke PRIVATE src)
add_executable(mysmb_flying_cheep_movement_smoke test/flying_cheep_movement_smoke.c src/game/enemy/flying_cheep.c)
target_include_directories(mysmb_flying_cheep_movement_smoke PRIVATE src)
target_include_directories(mysmb_firebar_chain_smoke PRIVATE src)
target_include_directories(mysmb_swimming_cheep_movement_smoke PRIVATE src)
target_include_directories(mysmb_bullet_movement_smoke PRIVATE src)
target_include_directories(mysmb_bloober_movement_smoke PRIVATE src)
target_include_directories(mysmb_green_counter_smoke PRIVATE src)
target_include_directories(mysmb_paratroopa_movement_smoke PRIVATE src)
target_include_directories(mysmb_hammer_movement_caller_smoke PRIVATE src)
target_include_directories(mysmb_podoboo_movement_smoke PRIVATE src)
add_executable(mysmb_special_actor_caller_smoke test/special_actor_caller_smoke.c src/game/enemy/special_callers.c)
target_include_directories(mysmb_special_actor_caller_smoke PRIVATE src)
add_executable(mysmb_platform_caller_smoke test/platform_caller_smoke.c src/game/enemy/platform_callers.c src/game/enemy/lifecycle.c)
target_include_directories(mysmb_platform_caller_smoke PRIVATE src)
target_include_directories(mysmb_retainer_call_chain_smoke PRIVATE src)
add_executable(mysmb_enemy_stream_boundary_smoke test/enemy_stream_boundary_smoke.c src/game/enemy/stream.c)
target_include_directories(mysmb_enemy_stream_boundary_smoke PRIVATE src)
add_executable(mysmb_parser_schedule_smoke test/parser_schedule_smoke.c)
target_link_libraries(mysmb_parser_schedule_smoke PRIVATE mysmb_game)
add_executable(mysmb_parser_buffer_commit_smoke test/parser_buffer_commit_smoke.c)
target_link_libraries(mysmb_parser_buffer_commit_smoke PRIVATE mysmb_game)
add_executable(mysmb_player_route_smoke test/player_route_smoke.c)
add_executable(mysmb_player_scroll_chain_smoke test/player_scroll_chain_smoke.c src/game/scroll.c)
add_executable(mysmb_player_entry_chain_smoke test/player_entry_chain_smoke.c src/game/entry.c)
add_executable(mysmb_player_control_chain_smoke test/player_control_chain_smoke.c src/game/player_control.c)
target_include_directories(mysmb_player_control_chain_smoke PRIVATE src)
add_executable(mysmb_player_transition_chain_smoke test/player_transition_chain_smoke.c src/game/player_transition.c)
add_executable(mysmb_player_modes_chain_smoke test/player_modes_chain_smoke.c src/game/player_modes.c)
target_include_directories(mysmb_player_modes_chain_smoke PRIVATE src)
add_executable(mysmb_player_end_level_chain_smoke test/player_end_level_chain_smoke.c src/game/player_end_level.c)
target_include_directories(mysmb_player_end_level_chain_smoke PRIVATE src)
add_executable(mysmb_player_movement_chain_smoke test/player_movement_chain_smoke.c src/game/player_movement.c)
target_include_directories(mysmb_player_movement_chain_smoke PRIVATE src)
add_executable(mysmb_player_climbing_chain_smoke test/player_climbing_chain_smoke.c)
target_include_directories(mysmb_player_climbing_chain_smoke PRIVATE src)
target_link_libraries(mysmb_player_climbing_chain_smoke PRIVATE mysmb_game)
add_executable(mysmb_player_physics_chain_smoke test/player_physics_chain_smoke.c)
target_include_directories(mysmb_player_physics_chain_smoke PRIVATE src)
target_link_libraries(mysmb_player_physics_chain_smoke PRIVATE mysmb_game)
add_executable(mysmb_player_animation_friction_chain_smoke test/player_animation_friction_chain_smoke.c)
add_executable(mysmb_fireball_dispatch_chain_smoke test/fireball_dispatch_chain_smoke.c src/game/fireball/fireball_spawn.c)
target_include_directories(mysmb_fireball_dispatch_chain_smoke PRIVATE src)
add_executable(mysmb_fireball_core_chain_smoke test/fireball_core_chain_smoke.c src/game/fireball/fireball_core.c)
target_include_directories(mysmb_fireball_core_chain_smoke PRIVATE src)
add_executable(mysmb_bubble_core_chain_smoke test/bubble_core_chain_smoke.c src/game/fireball/bubble.c)
target_include_directories(mysmb_bubble_core_chain_smoke PRIVATE src)
add_executable(mysmb_bubble_core_snapshot_check test/bubble_core_snapshot_check.c src/game/fireball/bubble.c)
target_include_directories(mysmb_bubble_core_snapshot_check PRIVATE src)
add_executable(mysmb_timer_chain_smoke test/timer_chain_smoke.c src/game/timer.c)
add_executable(mysmb_jumpspring_chain_smoke test/jumpspring_chain_smoke.c src/game/jumpspring.c)
add_executable(mysmb_vine_setup_smoke test/vine_setup_smoke.c)
add_executable(mysmb_vine_actor_smoke test/vine_actor_smoke.c src/game/vine.c)
add_executable(mysmb_hammer_chain_smoke test/hammer_chain_smoke.c src/game/hammer.c)
target_include_directories(mysmb_hammer_chain_smoke PRIVATE src)
add_executable(mysmb_coin_allocation_smoke test/coin_allocation_smoke.c src/game/coin.c)
target_include_directories(mysmb_coin_allocation_smoke PRIVATE src)
add_executable(mysmb_misc_lifetime_smoke test/misc_lifetime_smoke.c src/game/misc.c)
target_include_directories(mysmb_misc_lifetime_smoke PRIVATE src)
add_executable(mysmb_score_hud_smoke test/score_hud_smoke.c src/game/score.c)
target_include_directories(mysmb_score_hud_smoke PRIVATE src)
add_executable(mysmb_power_up_init_smoke test/power_up_init_smoke.c src/game/power_up_init.c)
target_include_directories(mysmb_power_up_init_smoke PRIVATE src)
add_executable(mysmb_power_up_actor_smoke test/power_up_actor_smoke.c src/game/power_up.c)
target_include_directories(mysmb_power_up_actor_smoke PRIVATE src)
add_executable(mysmb_block_head_smoke test/block_head_smoke.c src/game/blocks/head.c)
target_include_directories(mysmb_block_head_smoke PRIVATE src)
add_executable(mysmb_block_bump_smoke test/block_bump_smoke.c src/game/blocks/bump.c)
target_include_directories(mysmb_block_bump_smoke PRIVATE src)
add_executable(mysmb_block_chunks_smoke test/block_chunks_smoke.c src/game/blocks/chunks.c)
target_include_directories(mysmb_block_chunks_smoke PRIVATE src)
add_executable(mysmb_block_lifetime_smoke test/block_lifetime_smoke.c src/game/blocks/lifetime.c)
target_include_directories(mysmb_block_lifetime_smoke PRIVATE src)
add_executable(mysmb_block_replacement_smoke test/block_replacement_smoke.c src/game/blocks/replacement.c)
target_include_directories(mysmb_block_replacement_smoke PRIVATE src)
add_executable(mysmb_horizontal_movement_smoke test/horizontal_movement_smoke.c)
target_link_libraries(mysmb_horizontal_movement_smoke PRIVATE mysmb_game)
add_executable(mysmb_horizontal_snapshot_check test/horizontal_snapshot_check.c)
target_link_libraries(mysmb_horizontal_snapshot_check PRIVATE mysmb_game)
add_executable(mysmb_vertical_adapters_smoke test/vertical_adapters_smoke.c)
target_link_libraries(mysmb_vertical_adapters_smoke PRIVATE mysmb_game)
add_executable(mysmb_gravity_smoke test/gravity_smoke.c)
target_link_libraries(mysmb_gravity_smoke PRIVATE mysmb_game)
add_executable(mysmb_gravity_snapshot_check test/gravity_snapshot_check.c)
target_link_libraries(mysmb_gravity_snapshot_check PRIVATE mysmb_game)
add_executable(mysmb_power_up_init_snapshot_check test/power_up_init_snapshot_check.c src/game/power_up_init.c)
target_include_directories(mysmb_power_up_init_snapshot_check PRIVATE src)
add_executable(mysmb_power_up_init_dispatch_smoke test/power_up_init_dispatch_smoke.c)
target_link_libraries(mysmb_power_up_init_dispatch_smoke PRIVATE mysmb_game)

target_include_directories(mysmb_vine_actor_smoke PRIVATE src)
target_link_libraries(mysmb_vine_setup_smoke PRIVATE mysmb_game)
target_include_directories(mysmb_vine_setup_smoke PRIVATE src)
add_executable(mysmb_vine_setup_snapshot_check test/vine_setup_snapshot_check.c)
target_link_libraries(mysmb_vine_setup_snapshot_check PRIVATE mysmb_game)
target_include_directories(mysmb_vine_setup_snapshot_check PRIVATE src)
target_include_directories(mysmb_jumpspring_chain_smoke PRIVATE src)
target_include_directories(mysmb_timer_chain_smoke PRIVATE src)
target_include_directories(mysmb_player_animation_friction_chain_smoke PRIVATE src)
target_link_libraries(mysmb_player_animation_friction_chain_smoke PRIVATE mysmb_game)
add_executable(mysmb_player_animation_friction_snapshot_check test/player_animation_friction_snapshot_check.c)
target_include_directories(mysmb_player_animation_friction_snapshot_check PRIVATE src)
target_link_libraries(mysmb_player_animation_friction_snapshot_check PRIVATE mysmb_game)
add_executable(mysmb_player_physics_snapshot_check test/player_physics_snapshot_check.c)
target_include_directories(mysmb_player_physics_snapshot_check PRIVATE src)
target_link_libraries(mysmb_player_physics_snapshot_check PRIVATE mysmb_game)
add_executable(mysmb_player_climbing_snapshot_check test/player_climbing_snapshot_check.c)
target_include_directories(mysmb_player_climbing_snapshot_check PRIVATE src)
target_link_libraries(mysmb_player_climbing_snapshot_check PRIVATE mysmb_game)
add_executable(mysmb_player_modes_caller_check test/player_modes_snapshot_check.c src/game/player_modes.c)
target_compile_definitions(mysmb_player_modes_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
target_include_directories(mysmb_player_modes_caller_check PRIVATE src)
target_include_directories(mysmb_player_transition_chain_smoke PRIVATE src)
add_executable(mysmb_player_transition_caller_check test/player_transition_caller_check.c src/game/player_transition.c)
target_include_directories(mysmb_player_transition_caller_check PRIVATE src)
add_executable(mysmb_player_control_caller_check test/player_control_caller_check.c src/game/player_control.c)
target_include_directories(mysmb_player_control_caller_check PRIVATE src)
target_include_directories(mysmb_player_entry_chain_smoke PRIVATE src)
add_executable(mysmb_entrance_caller_snapshot_check test/entrance_caller_snapshot_check.c src/game/entry.c)
target_include_directories(mysmb_entrance_caller_snapshot_check PRIVATE src)
target_include_directories(mysmb_player_scroll_chain_smoke PRIVATE src)
add_executable(mysmb_scroll_snapshot_check test/scroll_snapshot_check.c src/game/scroll.c src/game/oam/object_position.c)
target_include_directories(mysmb_scroll_snapshot_check PRIVATE src)
target_link_libraries(mysmb_player_route_smoke PRIVATE mysmb_game)
add_executable(mysmb_player_friction_smoke test/player_friction_smoke.c)
target_link_libraries(mysmb_player_friction_smoke PRIVATE mysmb_game)
add_executable(mysmb_player_horizontal_carry_smoke test/player_horizontal_carry_smoke.c)
target_link_libraries(mysmb_player_horizontal_carry_smoke PRIVATE mysmb_game)
add_executable(mysmb_player_bounding_box_smoke test/player_bounding_box_smoke.c)
target_link_libraries(mysmb_player_bounding_box_smoke PRIVATE mysmb_game)
add_executable(mysmb_bounding_box_clip_smoke test/bounding_box_clip_smoke.c)
target_link_libraries(mysmb_bounding_box_clip_smoke PRIVATE mysmb_game)
add_executable(mysmb_bounding_box_core_smoke test/bounding_box_core_smoke.c)
target_link_libraries(mysmb_bounding_box_core_smoke PRIVATE mysmb_game)
add_executable(mysmb_geometry_core_smoke test/geometry_core_smoke.c)
target_link_libraries(mysmb_geometry_core_smoke PRIVATE mysmb_game)
add_executable(mysmb_geometry_actual_check test/geometry_actual_check.c)
target_link_libraries(mysmb_geometry_actual_check PRIVATE mysmb_game)
add_executable(mysmb_enemy_block_query_smoke test/enemy_block_query_smoke.c)
target_link_libraries(mysmb_enemy_block_query_smoke PRIVATE mysmb_game)
add_executable(mysmb_enemy_terrain_state_smoke test/enemy_terrain_state_smoke.c)
target_link_libraries(mysmb_enemy_terrain_state_smoke PRIVATE mysmb_game)
add_executable(mysmb_world_movement_smoke test/world_movement_smoke.c)
target_link_libraries(mysmb_world_movement_smoke PRIVATE mysmb_game)
add_executable(mysmb_hazard_collision_smoke test/hazard_collision_smoke.c)
target_link_libraries(mysmb_hazard_collision_smoke PRIVATE mysmb_game)
add_executable(mysmb_bullet_bill_smoke test/bullet_bill_smoke.c)
target_link_libraries(mysmb_bullet_bill_smoke PRIVATE mysmb_game)
add_executable(mysmb_paratroopa_smoke test/paratroopa_smoke.c)
target_link_libraries(mysmb_paratroopa_smoke PRIVATE mysmb_game)
add_executable(mysmb_lakitu_smoke test/lakitu_smoke.c)
target_link_libraries(mysmb_lakitu_smoke PRIVATE mysmb_game)
add_executable(mysmb_hammer_bro_smoke test/hammer_bro_smoke.c)
target_link_libraries(mysmb_hammer_bro_smoke PRIVATE mysmb_game)
add_executable(mysmb_hammer_bro_oam_smoke test/hammer_bro_oam_smoke.c)
target_link_libraries(mysmb_hammer_bro_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_enemy_collision_smoke test/enemy_collision_smoke.c)
target_link_libraries(mysmb_enemy_collision_smoke PRIVATE mysmb_game)
add_executable(mysmb_flying_cheep_smoke test/flying_cheep_smoke.c)
target_link_libraries(mysmb_flying_cheep_smoke PRIVATE mysmb_game)
add_executable(mysmb_firebar_smoke test/firebar_smoke.c)
target_link_libraries(mysmb_firebar_smoke PRIVATE mysmb_game)
add_executable(mysmb_bowser_smoke test/bowser_smoke.c)
target_link_libraries(mysmb_bowser_smoke PRIVATE mysmb_game)
add_executable(mysmb_vine_oam_smoke test/vine_oam_smoke.c)
target_link_libraries(mysmb_vine_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_six_sprite_stacker_smoke test/six_sprite_stacker_smoke.c)
target_link_libraries(mysmb_six_sprite_stacker_smoke PRIVATE mysmb_game)
add_executable(mysmb_sprite_dump_smoke test/sprite_dump_smoke.c)
target_link_libraries(mysmb_sprite_dump_smoke PRIVATE mysmb_game)
add_executable(mysmb_flagpole_gfx_smoke test/flagpole_gfx_smoke.c)
target_link_libraries(mysmb_flagpole_gfx_smoke PRIVATE mysmb_game)
add_executable(mysmb_bowser_oam_smoke test/bowser_oam_smoke.c)
target_link_libraries(mysmb_bowser_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_bowser_flame_oam_smoke test/bowser_flame_oam_smoke.c)
target_link_libraries(mysmb_bowser_flame_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_endgame_objects_smoke test/endgame_objects_smoke.c)
target_link_libraries(mysmb_endgame_objects_smoke PRIVATE mysmb_game)
add_executable(mysmb_flagpole_oam_smoke test/flagpole_oam_smoke.c)
target_link_libraries(mysmb_flagpole_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_retainer_oam_smoke test/retainer_oam_smoke.c)
target_link_libraries(mysmb_retainer_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_jumpspring_oam_smoke test/jumpspring_oam_smoke.c)
target_link_libraries(mysmb_jumpspring_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_jumpspring_graphics_snapshot_check
    test/jumpspring_graphics_snapshot_check.c)
target_link_libraries(mysmb_jumpspring_graphics_snapshot_check PRIVATE mysmb_game)
add_executable(mysmb_bowser_half_graphics_snapshot_check
    test/bowser_half_graphics_snapshot_check.c)
target_link_libraries(mysmb_bowser_half_graphics_snapshot_check PRIVATE mysmb_game)
add_executable(mysmb_platform_smoke test/platform_smoke.c)
target_link_libraries(mysmb_platform_smoke PRIVATE mysmb_game)
add_executable(mysmb_mode_smoke test/mode_smoke.c)
target_link_libraries(mysmb_mode_smoke PRIVATE mysmb_game)
add_executable(mysmb_oper_mode_dispatch_smoke test/oper_mode_dispatch_smoke.c)
target_link_libraries(mysmb_oper_mode_dispatch_smoke PRIVATE mysmb_game)
add_executable(mysmb_title_demo_smoke test/title_demo_smoke.c)
target_link_libraries(mysmb_title_demo_smoke PRIVATE mysmb_game)
add_executable(mysmb_screen_status_smoke test/screen_status_smoke.c)
target_link_libraries(mysmb_screen_status_smoke PRIVATE mysmb_game)
add_executable(mysmb_audio_smoke test/audio_smoke.c)
target_link_libraries(mysmb_audio_smoke PRIVATE mysmb_game)
add_executable(mysmb_end_to_end_smoke test/end_to_end_smoke.c)
target_link_libraries(mysmb_end_to_end_smoke PRIVATE mysmb_game)
add_executable(mysmb_ppu_frame_smoke test/ppu_frame_smoke.c)
target_link_libraries(mysmb_ppu_frame_smoke PRIVATE mysmb_game)
add_executable(mysmb_render_smoke test/render_smoke.c)
target_link_libraries(mysmb_render_smoke PRIVATE mysmb_game)
add_executable(mysmb_frame_snapshot_smoke test/frame_snapshot_smoke.c)
target_link_libraries(mysmb_frame_snapshot_smoke PRIVATE mysmb_game)
add_executable(mysmb_sprite_oam_smoke test/sprite_oam_smoke.c)
target_link_libraries(mysmb_sprite_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_player_oam_smoke test/player_oam_smoke.c)
target_link_libraries(mysmb_player_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_floatey_oam_smoke test/floatey_oam_smoke.c)
target_link_libraries(mysmb_floatey_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_misc_oam_smoke test/misc_oam_smoke.c)
target_link_libraries(mysmb_misc_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_jumping_coin_snapshot_check test/jumping_coin_snapshot_check.c)
target_link_libraries(mysmb_jumping_coin_snapshot_check PRIVATE mysmb_game)
add_executable(mysmb_rom_object_array_layout_smoke test/rom_object_array_layout_smoke.c)
target_link_libraries(mysmb_rom_object_array_layout_smoke PRIVATE mysmb_game)
add_executable(mysmb_fireball_oam_smoke test/fireball_oam_smoke.c)
target_link_libraries(mysmb_fireball_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_power_up_oam_smoke test/power_up_oam_smoke.c)
target_link_libraries(mysmb_power_up_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_block_oam_smoke test/block_oam_smoke.c)
target_link_libraries(mysmb_block_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_goomba_oam_smoke test/goomba_oam_smoke.c)
target_link_libraries(mysmb_goomba_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_normal_enemy_oam_smoke test/normal_enemy_oam_smoke.c)
target_link_libraries(mysmb_normal_enemy_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_bubble_oam_smoke test/bubble_oam_smoke.c)
target_link_libraries(mysmb_bubble_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_small_platform_oam_smoke test/small_platform_oam_smoke.c)
target_link_libraries(mysmb_small_platform_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_large_platform_graphics_smoke test/large_platform_graphics_smoke.c)
target_link_libraries(mysmb_large_platform_graphics_smoke PRIVATE mysmb_game)
add_executable(mysmb_large_platform_snapshot_check
    test/large_platform_snapshot_check.c)
target_link_libraries(mysmb_large_platform_snapshot_check PRIVATE mysmb_game)
add_executable(mysmb_piranha_oam_smoke test/piranha_oam_smoke.c)
target_link_libraries(mysmb_piranha_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_cheep_oam_smoke test/cheep_oam_smoke.c)
target_link_libraries(mysmb_cheep_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_bloober_oam_smoke test/bloober_oam_smoke.c)
target_link_libraries(mysmb_bloober_oam_smoke PRIVATE mysmb_game)
add_executable(mysmb_podoboo_oam_smoke test/podoboo_oam_smoke.c)
target_link_libraries(mysmb_podoboo_oam_smoke PRIVATE mysmb_game)
add_library(mysmb_text_frame STATIC src/platform/text/text_frame.c)
target_include_directories(mysmb_text_frame PUBLIC src)
target_link_libraries(mysmb_text_frame PUBLIC mysmb_game)
add_executable(mysmb_text_frame_smoke test/text_frame_smoke.c)
target_link_libraries(mysmb_text_frame_smoke PRIVATE mysmb_text_frame)
add_library(mysmb_vga_frame STATIC src/platform/vga/vga_frame.c)
target_include_directories(mysmb_vga_frame PUBLIC src)
target_link_libraries(mysmb_vga_frame PUBLIC mysmb_game)
add_executable(mysmb_vga_frame_smoke test/vga_frame_smoke.c)
target_link_libraries(mysmb_vga_frame_smoke PRIVATE mysmb_vga_frame)
add_library(mysmb_dos16_root STATIC src/platform/dos16/dos16_root.c)
target_include_directories(mysmb_dos16_root PUBLIC src)
target_link_libraries(mysmb_dos16_root PUBLIC mysmb_game mysmb_text_frame mysmb_vga_frame)
add_executable(mysmb_dos16_root_smoke test/dos16_root_smoke.c)
target_link_libraries(mysmb_dos16_root_smoke PRIVATE mysmb_dos16_root)

# A separately named input for the later OpenNT large-model DOS build.  It has
# no DOS platform code and must stay free of host headers.
add_library(mysmb_dos16_core OBJECT ${MYSMB_GAME_SOURCES})
target_include_directories(mysmb_dos16_core PRIVATE src)

if(MYSMB_OPENNT_CL16)
    set(MYSMB_OPENNT_OUTPUT_DIR "${CMAKE_BINARY_DIR}/opennt16")
    add_custom_target(mysmb_opennt16_core
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/boot.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/frame_root.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/title_modes.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/terminal_modes.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/game.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/audio.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/area.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/enemy/stream.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/enemy/init.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
                        -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/enemy/core.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/enemy/movement.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/enemy/normal.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/enemy/background.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/enemy/side_collision.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/enemy/frenzy.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/player.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/scroll.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/entry.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/player_control.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/player_transition.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/player_modes.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/player_end_level.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/player_movement.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/objects.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/bridge.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/oam/bullet_bill_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/oam/hammer_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/oam/firebar_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/oam/vine_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/enemy_bounds.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/oam/power_up_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/oam/object_position.c src/game/oam/block_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/oam/goomba_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/fireball/bubble.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/oam/piranha_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/oam/cheep_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/oam/bloober_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/oam/podoboo_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
            COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
                "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
                -Compiler "${MYSMB_OPENNT_CL16}"
                -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
                -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/oam/normal_enemy_gfx.c"
                -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/oam/spiny_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/oam/hammer_bro_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/oam/bowser_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/endgame_objects.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/oam/small_platform_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/render.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/frame_snapshot.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/platform/vga/vga_frame.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/platform/text/text_frame.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/platform/dos16/dos16_root.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        VERBATIM
    )
    if(MYSMB_DOS_RUNTIME_DIR)
        get_filename_component(MYSMB_OPENNT_LINK16 "${MYSMB_OPENNT_CL16}" DIRECTORY)
        set(MYSMB_OPENNT_LINK16 "${MYSMB_OPENNT_LINK16}/link16.exe")
        add_custom_target(mysmb_opennt16_dos
            COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
                "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Dos.ps1"
                -Compiler "${MYSMB_OPENNT_CL16}"
                -Linker "${MYSMB_OPENNT_LINK16}"
                -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
                -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}/dos"
                -RuntimeDirectory "${MYSMB_DOS_RUNTIME_DIR}"
                -SourceRoot "${CMAKE_CURRENT_SOURCE_DIR}/src"
            VERBATIM
        )
    endif()
endif()

if(WIN32)
    if(MYSMB_WIN32_ARCH STREQUAL "host")
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(MYSMB_WIN32_ARCH "x64")
        else()
            set(MYSMB_WIN32_ARCH "x86")
        endif()
    endif()

    add_executable(mysmb_win32 WIN32 src/platform/win32/main_win32.c)
    target_link_libraries(mysmb_win32 PRIVATE mysmb_game user32 gdi32)
    set_target_properties(mysmb_win32 PROPERTIES
        OUTPUT_NAME "mysmb-win32-${MYSMB_WIN32_ARCH}"
    )
endif()

enable_testing()
add_test(NAME mysmb.core-smoke COMMAND mysmb_core_smoke)
add_test(NAME mysmb.ram-cold-start-smoke COMMAND mysmb_ram_cold_start_smoke)
add_test(NAME mysmb.reset-root-smoke COMMAND mysmb_reset_root_smoke)
add_test(NAME mysmb.boot-nmi-boundary-smoke COMMAND mysmb_boot_nmi_boundary_smoke)
add_test(NAME mysmb.name-table-init-smoke COMMAND mysmb_name_table_init_smoke)
add_test(NAME mysmb.vram-address-table-smoke COMMAND mysmb_vram_address_table_smoke)
add_test(NAME mysmb.joypad-vram-chain-smoke COMMAND mysmb_joypad_vram_chain_smoke)
add_test(NAME mysmb.pseudorandom-smoke COMMAND mysmb_pseudorandom_smoke)
add_test(NAME mysmb.timer-root-smoke COMMAND mysmb_timer_root_smoke)
add_test(NAME mysmb.pause-root-smoke COMMAND mysmb_pause_root_smoke)
add_test(NAME mysmb.sprite-root-smoke COMMAND mysmb_sprite_root_smoke)
add_executable(mysmb_sprite_shuffle_smoke test/sprite_shuffle_smoke.c)
target_link_libraries(mysmb_sprite_shuffle_smoke PRIVATE mysmb_game)
add_test(NAME mysmb.sprite-shuffle-smoke COMMAND mysmb_sprite_shuffle_smoke)

add_test(NAME mysmb.top-score-root-smoke COMMAND mysmb_top_score_root_smoke)
add_test(NAME mysmb.status-arithmetic-smoke COMMAND mysmb_status_arithmetic_smoke)
add_test(NAME mysmb.area-music-smoke COMMAND mysmb_area_music_smoke)
add_test(NAME mysmb.area-entry-smoke COMMAND mysmb_area_entry_smoke)
add_test(NAME mysmb.music-header-smoke COMMAND mysmb_music_header_smoke)
add_test(NAME mysmb.area-parser-column-smoke COMMAND mysmb_area_parser_column_smoke)
add_test(NAME mysmb.area-parser-terminal-slot-smoke COMMAND mysmb_area_parser_terminal_slot_smoke)
add_test(NAME mysmb.area-special-object-smoke COMMAND mysmb_area_special_object_smoke)
add_test(NAME mysmb.area-rope-object-smoke COMMAND mysmb_area_rope_object_smoke)
add_test(NAME mysmb.area-coin-row-smoke COMMAND mysmb_area_coin_row_smoke)
add_test(NAME mysmb.area-castle-column-smoke COMMAND mysmb_area_castle_column_smoke)
add_test(NAME mysmb.area-block-row-column-smoke COMMAND mysmb_area_block_row_column_smoke)
add_test(NAME mysmb.area-cannon-smoke COMMAND mysmb_area_cannon_smoke)
add_test(NAME mysmb.area-staircase-smoke COMMAND mysmb_area_staircase_smoke)
add_test(NAME mysmb.area-jumpspring-smoke COMMAND mysmb_area_jumpspring_smoke)
add_test(NAME mysmb.area-item-block-smoke COMMAND mysmb_area_item_block_smoke)
add_test(NAME mysmb.area-pipe-tail-smoke COMMAND mysmb_area_pipe_tail_smoke)
add_test(NAME mysmb.area-block-address-smoke COMMAND mysmb_area_block_address_smoke)
add_test(NAME mysmb.block-buffer-core-smoke COMMAND mysmb_block_buffer_core_smoke)
add_test(NAME mysmb.area-parser-boundary-smoke COMMAND mysmb_area_parser_boundary_smoke)
add_test(NAME mysmb.area-loop-command-smoke COMMAND mysmb_area_loop_command_smoke)
add_test(NAME mysmb.game-entry-dispatch COMMAND mysmb_game_entry_dispatch_smoke)
add_test(NAME mysmb.engine-caller COMMAND mysmb_engine_caller_smoke)
add_test(NAME mysmb.engine-tail COMMAND mysmb_engine_tail_smoke)
add_test(NAME mysmb.engine-slots COMMAND mysmb_engine_slots_smoke)
add_test(NAME mysmb.engine-environment COMMAND mysmb_engine_environment_smoke)
add_test(NAME mysmb.cannon-dispatch COMMAND mysmb_cannon_smoke)
add_test(NAME mysmb.cannon-children COMMAND mysmb_cannon_children_smoke)
add_test(NAME mysmb.enemy-dispatch COMMAND mysmb_enemy_dispatch_smoke)
add_test(NAME mysmb.enemy-loop COMMAND mysmb_enemy_loop_smoke)
add_test(NAME mysmb.normal-enemy-movement COMMAND mysmb_normal_enemy_movement_smoke)
add_test(NAME mysmb.normal-enemy-caller COMMAND mysmb_normal_enemy_caller_smoke)
add_test(NAME mysmb.podoboo-movement COMMAND mysmb_podoboo_movement_smoke)
add_test(NAME mysmb.hammer-movement-caller COMMAND mysmb_hammer_movement_caller_smoke)
add_test(NAME mysmb.paratroopa-movement COMMAND mysmb_paratroopa_movement_smoke)
add_test(NAME mysmb.green-paratroopa-counters COMMAND mysmb_green_counter_smoke)
add_test(NAME mysmb.bloober-movement COMMAND mysmb_bloober_movement_smoke)
add_test(NAME mysmb.bullet-bill-movement COMMAND mysmb_bullet_movement_smoke)
add_test(NAME mysmb.swimming-cheep-movement COMMAND mysmb_swimming_cheep_movement_smoke)
add_test(NAME mysmb.firebar-chain COMMAND mysmb_firebar_chain_smoke)
add_test(NAME mysmb.lakitu-movement-distance COMMAND mysmb_lakitu_movement_smoke)
add_test(NAME mysmb.bridge-collapse-chain COMMAND mysmb_bridge_collapse_smoke)
add_test(NAME mysmb.bowser-control-chain COMMAND mysmb_bowser_control_smoke)
add_test(NAME mysmb.bowser-graphics-chain COMMAND mysmb_bowser_graphics_smoke)
add_test(NAME mysmb.bowser-flame-chain COMMAND mysmb_bowser_flame_chain_smoke)
add_test(NAME mysmb.fireworks-lifetime-chain COMMAND mysmb_fireworks_lifetime_smoke)
add_test(NAME mysmb.star-flag-chain COMMAND mysmb_star_flag_smoke)
add_test(NAME mysmb.piranha-movement-chain COMMAND mysmb_piranha_movement_smoke)
add_test(NAME mysmb.firebar-spin-chain COMMAND mysmb_firebar_spin_smoke)
add_test(NAME mysmb.balance-platform-chain COMMAND mysmb_balance_platform_smoke)
add_test(NAME mysmb.vertical-platform-chain COMMAND mysmb_vertical_platform_smoke)
add_test(NAME mysmb.horizontal-platform-chain COMMAND mysmb_horizontal_platform_smoke)
add_test(NAME mysmb.lift-platform-chain COMMAND mysmb_lift_platform_smoke)
add_test(NAME mysmb.offscreen-bounds-chain COMMAND mysmb_offscreen_bounds_smoke)
add_test(NAME mysmb.flying-cheep-movement COMMAND mysmb_flying_cheep_movement_smoke)
add_test(NAME mysmb.special-actor-caller COMMAND mysmb_special_actor_caller_smoke)
add_test(NAME mysmb.platform-caller COMMAND mysmb_platform_caller_smoke)
add_test(NAME mysmb.enemy-background-caller COMMAND mysmb_enemy_background_caller_smoke)
add_test(NAME mysmb.enemy-side-caller COMMAND mysmb_enemy_side_caller_smoke)
add_test(NAME mysmb.area-helper-smoke COMMAND mysmb_area_helper_smoke)
add_test(NAME mysmb.area-hole-underpart-smoke COMMAND mysmb_area_hole_underpart_smoke)
add_test(NAME mysmb.area-initialize-smoke COMMAND mysmb_area_initialize_smoke)
add_test(NAME mysmb.enemy-stream-smoke COMMAND mysmb_enemy_stream_smoke)
add_test(NAME mysmb.enemy-no-init COMMAND mysmb_enemy_no_init_smoke)
add_test(NAME mysmb.enemy-init-vector COMMAND mysmb_enemy_init_handoff_smoke)
add_test(NAME mysmb.enemy-common-init COMMAND mysmb_enemy_common_init_smoke)
add_test(NAME mysmb.lakitu-spiny-chain COMMAND mysmb_lakitu_spiny_chain_smoke)
add_test(NAME mysmb.firebar-initialization-chain COMMAND mysmb_firebar_initialization_smoke)
add_test(NAME mysmb.flying-fish-initialization-chain COMMAND mysmb_flying_fish_initialization_smoke)
add_test(NAME mysmb.bowser-flame-initialization-chain COMMAND mysmb_bowser_flame_initialization_smoke)
add_test(NAME mysmb.fireworks-initialization-chain COMMAND mysmb_fireworks_initialization_smoke)
add_test(NAME mysmb.bullet-swimming-fish-chain COMMAND mysmb_bullet_swimming_fish_smoke)
add_test(NAME mysmb.group-enemy-chain COMMAND mysmb_group_enemy_smoke)
add_test(NAME mysmb.small-initializers-frenzy-chain COMMAND mysmb_small_initializers_smoke)
add_test(NAME mysmb.platform-initialization-chain COMMAND mysmb_platform_initialization_smoke)
add_test(NAME mysmb.retainer-call-chain COMMAND mysmb_retainer_call_chain_smoke)
add_test(NAME mysmb.enemy-stream COMMAND mysmb_enemy_stream_boundary_smoke)
add_test(NAME mysmb.parser-schedule-smoke COMMAND mysmb_parser_schedule_smoke)
add_test(NAME mysmb.parser-buffer-commit-smoke COMMAND mysmb_parser_buffer_commit_smoke)
add_test(NAME mysmb.player-route-smoke COMMAND mysmb_player_route_smoke)
add_test(NAME mysmb.player-scroll-chain COMMAND mysmb_player_scroll_chain_smoke)
add_test(NAME mysmb.player-entry-chain COMMAND mysmb_player_entry_chain_smoke)
add_test(NAME mysmb.player-control-chain COMMAND mysmb_player_control_chain_smoke)
add_test(NAME mysmb.player-transition-chain COMMAND mysmb_player_transition_chain_smoke)
add_test(NAME mysmb.player-modes-chain COMMAND mysmb_player_modes_chain_smoke)
add_test(NAME mysmb.player-end-level-chain COMMAND mysmb_player_end_level_chain_smoke)
add_test(NAME mysmb.player-movement-chain COMMAND mysmb_player_movement_chain_smoke)
add_test(NAME mysmb.player-climbing-chain COMMAND mysmb_player_climbing_chain_smoke)
add_test(NAME mysmb.player-physics-chain COMMAND mysmb_player_physics_chain_smoke)
add_test(NAME mysmb.player-animation-friction-chain COMMAND mysmb_player_animation_friction_chain_smoke)
add_test(NAME mysmb.fireball-dispatch-chain COMMAND mysmb_fireball_dispatch_chain_smoke)
add_test(NAME mysmb.fireball-core-chain COMMAND mysmb_fireball_core_chain_smoke)
add_test(NAME mysmb.bubble-core-chain COMMAND mysmb_bubble_core_chain_smoke)
add_test(NAME mysmb.timer-chain COMMAND mysmb_timer_chain_smoke)
add_test(NAME mysmb.jumpspring-chain COMMAND mysmb_jumpspring_chain_smoke)
add_test(NAME mysmb.hammer-chain COMMAND mysmb_hammer_chain_smoke)
add_test(NAME mysmb.coin-allocation COMMAND mysmb_coin_allocation_smoke)
add_test(NAME mysmb.misc-lifetime COMMAND mysmb_misc_lifetime_smoke)
add_test(NAME mysmb.score-hud COMMAND mysmb_score_hud_smoke)
add_test(NAME mysmb.power-up-init COMMAND mysmb_power_up_init_smoke)
add_test(NAME mysmb.power-up-actor COMMAND mysmb_power_up_actor_smoke)
add_test(NAME mysmb.block-head COMMAND mysmb_block_head_smoke)
add_test(NAME mysmb.block-bump COMMAND mysmb_block_bump_smoke)
add_test(NAME mysmb.block-chunks COMMAND mysmb_block_chunks_smoke)
add_test(NAME mysmb.block-lifetime COMMAND mysmb_block_lifetime_smoke)
add_test(NAME mysmb.block-replacement COMMAND mysmb_block_replacement_smoke)
add_test(NAME mysmb.horizontal-movement COMMAND mysmb_horizontal_movement_smoke)
add_test(NAME mysmb.vertical-adapters COMMAND mysmb_vertical_adapters_smoke)
add_test(NAME mysmb.gravity COMMAND mysmb_gravity_smoke)
add_test(NAME mysmb.power-up-init-dispatch COMMAND mysmb_power_up_init_dispatch_smoke)
add_test(NAME mysmb.vine-setup COMMAND mysmb_vine_setup_smoke)
add_test(NAME mysmb.vine-actor COMMAND mysmb_vine_actor_smoke)
add_test(NAME mysmb.player-friction-smoke COMMAND mysmb_player_friction_smoke)
add_test(NAME mysmb.player-horizontal-carry-smoke COMMAND mysmb_player_horizontal_carry_smoke)
add_test(NAME mysmb.player-bounding-box-smoke COMMAND mysmb_player_bounding_box_smoke)
add_test(NAME mysmb.bounding-box-clip-smoke COMMAND mysmb_bounding_box_clip_smoke)
add_test(NAME mysmb.bounding-box-core-smoke COMMAND mysmb_bounding_box_core_smoke)
add_test(NAME mysmb.geometry-core-smoke COMMAND mysmb_geometry_core_smoke)
add_test(NAME mysmb.enemy-block-query-smoke COMMAND mysmb_enemy_block_query_smoke)
add_test(NAME mysmb.enemy-terrain-state-smoke COMMAND mysmb_enemy_terrain_state_smoke)
add_test(NAME mysmb.world-movement-smoke COMMAND mysmb_world_movement_smoke)
add_test(NAME mysmb.hazard-collision-smoke COMMAND mysmb_hazard_collision_smoke)
add_test(NAME mysmb.bullet-bill-smoke COMMAND mysmb_bullet_bill_smoke)
add_test(NAME mysmb.paratroopa-smoke COMMAND mysmb_paratroopa_smoke)
add_test(NAME mysmb.lakitu-smoke COMMAND mysmb_lakitu_smoke)
add_test(NAME mysmb.hammer-bro-smoke COMMAND mysmb_hammer_bro_smoke)
add_test(NAME mysmb.hammer-bro-oam-smoke COMMAND mysmb_hammer_bro_oam_smoke)
add_test(NAME mysmb.enemy-collision-smoke COMMAND mysmb_enemy_collision_smoke)
add_test(NAME mysmb.flying-cheep-smoke COMMAND mysmb_flying_cheep_smoke)
add_test(NAME mysmb.firebar-smoke COMMAND mysmb_firebar_smoke)
add_test(NAME mysmb.bowser-smoke COMMAND mysmb_bowser_smoke)
add_test(NAME mysmb.vine-oam-smoke COMMAND mysmb_vine_oam_smoke)
add_test(NAME mysmb.six-sprite-stacker-smoke COMMAND mysmb_six_sprite_stacker_smoke)
add_test(NAME mysmb.sprite-dump-smoke COMMAND mysmb_sprite_dump_smoke)
add_test(NAME mysmb.flagpole-gfx-smoke COMMAND mysmb_flagpole_gfx_smoke)
add_test(NAME mysmb.bowser-oam-smoke COMMAND mysmb_bowser_oam_smoke)
add_test(NAME mysmb.bowser-flame-oam-smoke COMMAND mysmb_bowser_flame_oam_smoke)
add_test(NAME mysmb.endgame-objects-smoke COMMAND mysmb_endgame_objects_smoke)
add_test(NAME mysmb.flagpole-oam-smoke COMMAND mysmb_flagpole_oam_smoke)
add_test(NAME mysmb.retainer-oam-smoke COMMAND mysmb_retainer_oam_smoke)
add_test(NAME mysmb.jumpspring-oam-smoke COMMAND mysmb_jumpspring_oam_smoke)
add_test(NAME mysmb.platform-smoke COMMAND mysmb_platform_smoke)
add_test(NAME mysmb.mode-smoke COMMAND mysmb_mode_smoke)
add_test(NAME mysmb.oper-mode-dispatch-smoke COMMAND mysmb_oper_mode_dispatch_smoke)
add_test(NAME mysmb.title-demo-smoke COMMAND mysmb_title_demo_smoke)
add_test(NAME mysmb.screen-status-smoke COMMAND mysmb_screen_status_smoke)
add_test(NAME mysmb.audio-smoke COMMAND mysmb_audio_smoke)
add_test(NAME mysmb.end-to-end-smoke COMMAND mysmb_end_to_end_smoke)
add_test(NAME mysmb.ppu-frame-smoke COMMAND mysmb_ppu_frame_smoke)
add_test(NAME mysmb.render-smoke COMMAND mysmb_render_smoke)
add_test(NAME mysmb.frame-snapshot-smoke COMMAND mysmb_frame_snapshot_smoke)
add_test(NAME mysmb.sprite-oam-smoke COMMAND mysmb_sprite_oam_smoke)
add_test(NAME mysmb.player-oam-smoke COMMAND mysmb_player_oam_smoke)
add_test(NAME mysmb.floatey-oam-smoke COMMAND mysmb_floatey_oam_smoke)
add_test(NAME mysmb.misc-oam-smoke COMMAND mysmb_misc_oam_smoke)
add_test(NAME mysmb.rom-object-array-layout-smoke COMMAND mysmb_rom_object_array_layout_smoke)
add_test(NAME mysmb.fireball-oam-smoke COMMAND mysmb_fireball_oam_smoke)
add_test(NAME mysmb.power-up-oam-smoke COMMAND mysmb_power_up_oam_smoke)
add_test(NAME mysmb.block-oam-smoke COMMAND mysmb_block_oam_smoke)
add_test(NAME mysmb.goomba-oam-smoke COMMAND mysmb_goomba_oam_smoke)
add_test(NAME mysmb.normal-enemy-oam-smoke COMMAND mysmb_normal_enemy_oam_smoke)
add_test(NAME mysmb.bubble-oam-smoke COMMAND mysmb_bubble_oam_smoke)
add_test(NAME mysmb.small-platform-oam-smoke COMMAND mysmb_small_platform_oam_smoke)
add_test(NAME mysmb.large-platform-graphics-smoke
         COMMAND mysmb_large_platform_graphics_smoke)
add_test(NAME mysmb.piranha-oam-smoke COMMAND mysmb_piranha_oam_smoke)
add_test(NAME mysmb.cheep-oam-smoke COMMAND mysmb_cheep_oam_smoke)
add_test(NAME mysmb.bloober-oam-smoke COMMAND mysmb_bloober_oam_smoke)
add_test(NAME mysmb.podoboo-oam-smoke COMMAND mysmb_podoboo_oam_smoke)
add_test(NAME mysmb.text-frame-smoke COMMAND mysmb_text_frame_smoke)
add_test(NAME mysmb.vga-frame-smoke COMMAND mysmb_vga_frame_smoke)
add_test(NAME mysmb.dos16-root-smoke COMMAND mysmb_dos16_root_smoke)

find_package(Python3 COMPONENTS Interpreter REQUIRED)
add_test(NAME mysmb.rom-codegen
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/test_smb_rom_codegen.py)
add_test(NAME mysmb.asm-index
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/test_smb_asm_index.py)
add_test(NAME mysmb.enemy-data-bindings-synthetic
         COMMAND ${Python3_EXECUTABLE} -B ${CMAKE_CURRENT_SOURCE_DIR}/test/test_smb_enemy_data_audit.py)
add_test(NAME mysmb.boot-codegen
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/test_smb_boot_codegen.py)
add_test(NAME mysmb.title-codegen
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/test_smb_title_codegen.py)
add_test(NAME mysmb.platform-purity
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/test_platform_purity.py)
add_test(NAME mysmb.static-analysis
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/test_smb_static_analysis.py)
add_test(NAME mysmb.listing-layout
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/test_smb_listing_layout.py)
add_test(NAME mysmb.listing-reconcile
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/test_smb_listing_reconcile.py)
add_test(NAME mysmb.complete-analysis
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/test_smb_complete_analysis.py)

if(MYSMB_ROM_PATH)
    set(MYSMB_LOCAL_ROM_DIR "${CMAKE_BINARY_DIR}/generated/smb1-local")
    add_custom_command(
        OUTPUT
            "${MYSMB_LOCAL_ROM_DIR}/smb1_local_rom.h"
            "${MYSMB_LOCAL_ROM_DIR}/smb1_local_rom.c"
            "${MYSMB_LOCAL_ROM_DIR}/smb1_local_map.txt"
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/smb_rom_codegen.py
            --rom "${MYSMB_ROM_PATH}" --output "${MYSMB_LOCAL_ROM_DIR}"
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tools/smb_rom_codegen.py "${MYSMB_ROM_PATH}"
        VERBATIM
    )
    add_custom_target(mysmb_local_rom DEPENDS
        "${MYSMB_LOCAL_ROM_DIR}/smb1_local_rom.h"
        "${MYSMB_LOCAL_ROM_DIR}/smb1_local_rom.c"
        "${MYSMB_LOCAL_ROM_DIR}/smb1_local_map.txt"
    )
    add_library(mysmb_local_rom_data OBJECT
        "${MYSMB_LOCAL_ROM_DIR}/smb1_local_rom.c"
    )
    add_dependencies(mysmb_local_rom_data mysmb_local_rom)
    target_include_directories(mysmb_local_rom_data PRIVATE "${MYSMB_LOCAL_ROM_DIR}")

    set(MYSMB_STATIC_BOOT_DIR "${MYSMB_LOCAL_ROM_DIR}/static")
    add_custom_command(
        OUTPUT
            "${MYSMB_STATIC_BOOT_DIR}/smb1_static_boot.h"
            "${MYSMB_STATIC_BOOT_DIR}/smb1_static_boot.c"
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/smb_boot_codegen.py
            --rom "${MYSMB_ROM_PATH}" --output "${MYSMB_STATIC_BOOT_DIR}"
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tools/smb_boot_codegen.py
                ${CMAKE_CURRENT_SOURCE_DIR}/tools/smb_rom_codegen.py
                "${MYSMB_ROM_PATH}"
        VERBATIM
    )
    add_custom_target(mysmb_static_boot DEPENDS
        "${MYSMB_STATIC_BOOT_DIR}/smb1_static_boot.h"
        "${MYSMB_STATIC_BOOT_DIR}/smb1_static_boot.c"
    )
    add_library(mysmb_static_boot_data OBJECT
        "${MYSMB_STATIC_BOOT_DIR}/smb1_static_boot.c"
    )
    add_dependencies(mysmb_static_boot_data mysmb_static_boot)
    target_include_directories(mysmb_static_boot_data PRIVATE "${MYSMB_STATIC_BOOT_DIR}")

    set(MYSMB_LOCAL_TITLE_DIR "${MYSMB_LOCAL_ROM_DIR}/title")
    add_custom_command(
        OUTPUT
            "${MYSMB_LOCAL_TITLE_DIR}/smb1_local_title.h"
            "${MYSMB_LOCAL_TITLE_DIR}/smb1_local_title.c"
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/smb_title_codegen.py
            --rom "${MYSMB_ROM_PATH}" --output "${MYSMB_LOCAL_TITLE_DIR}"
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tools/smb_title_codegen.py
                ${CMAKE_CURRENT_SOURCE_DIR}/tools/smb_rom_codegen.py
                "${MYSMB_ROM_PATH}"
        VERBATIM
    )
    add_custom_target(mysmb_local_title DEPENDS
        "${MYSMB_LOCAL_TITLE_DIR}/smb1_local_title.h"
        "${MYSMB_LOCAL_TITLE_DIR}/smb1_local_title.c"
    )
    add_library(mysmb_local_title_data OBJECT
        "${MYSMB_LOCAL_TITLE_DIR}/smb1_local_title.c"
    )
    add_dependencies(mysmb_local_title_data mysmb_local_title)
    target_include_directories(mysmb_local_title_data PRIVATE "${MYSMB_LOCAL_TITLE_DIR}")
    if(TARGET mysmb_win32)
        target_sources(mysmb_win32 PRIVATE
            $<TARGET_OBJECTS:mysmb_local_rom_data>
            $<TARGET_OBJECTS:mysmb_local_title_data>
        )
        target_include_directories(mysmb_win32 PRIVATE
            "${MYSMB_LOCAL_ROM_DIR}" "${MYSMB_LOCAL_TITLE_DIR}"
        )
        target_compile_definitions(mysmb_win32 PRIVATE MYSMB_LOCAL_TITLE=1)
        add_test(NAME mysmb.win32-${MYSMB_WIN32_ARCH}-self-test
                 COMMAND $<TARGET_FILE:mysmb_win32> --self-test)
    endif()
    add_executable(mysmb_local_title_smoke test/local_title_smoke.c
        $<TARGET_OBJECTS:mysmb_local_title_data>)
    target_include_directories(mysmb_local_title_smoke PRIVATE src "${MYSMB_LOCAL_TITLE_DIR}")
    target_link_libraries(mysmb_local_title_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.local-title-smoke COMMAND mysmb_local_title_smoke)
    add_executable(mysmb_local_title_oracle test/local_title_oracle.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>
        $<TARGET_OBJECTS:mysmb_local_title_data>)
    target_include_directories(mysmb_local_title_oracle PRIVATE src
        "${MYSMB_LOCAL_ROM_DIR}" "${MYSMB_LOCAL_TITLE_DIR}")
    target_link_libraries(mysmb_local_title_oracle PRIVATE mysmb_game)
    add_test(NAME mysmb.local-title-oracle COMMAND mysmb_local_title_oracle)
    add_executable(mysmb_local_title_bootstrap_smoke test/local_title_bootstrap_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>
        $<TARGET_OBJECTS:mysmb_local_title_data>)
    target_include_directories(mysmb_local_title_bootstrap_smoke PRIVATE src
        "${MYSMB_LOCAL_ROM_DIR}" "${MYSMB_LOCAL_TITLE_DIR}")
    target_link_libraries(mysmb_local_title_bootstrap_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.local-title-bootstrap-smoke
             COMMAND mysmb_local_title_bootstrap_smoke)
    add_executable(mysmb_local_area_smoke test/local_area_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_local_area_smoke PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_local_area_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.local-area-smoke COMMAND mysmb_local_area_smoke)
    add_executable(mysmb_area_output_smoke test/area_output_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_area_output_smoke PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_area_output_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.area-output-smoke COMMAND mysmb_area_output_smoke)
    add_executable(mysmb_area_data_smoke test/area_data_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_area_data_smoke PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_area_data_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.area-data-smoke COMMAND mysmb_area_data_smoke)
    add_executable(mysmb_area_parser_data_smoke test/area_parser_data_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_area_parser_data_smoke PRIVATE src
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_area_parser_data_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.area-parser-data-smoke COMMAND mysmb_area_parser_data_smoke)
    add_executable(mysmb_area_pointer_header_smoke test/area_pointer_header_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_area_pointer_header_smoke PRIVATE src
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_area_pointer_header_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.area-pointer-header-smoke COMMAND mysmb_area_pointer_header_smoke)
    add_executable(mysmb_castle_scene_stream_smoke test/castle_scene_stream_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_castle_scene_stream_smoke PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_castle_scene_stream_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.castle-scene-streams COMMAND mysmb_castle_scene_stream_smoke)
    add_executable(mysmb_ground_scene_stream_smoke test/ground_scene_stream_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_ground_scene_stream_smoke PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_ground_scene_stream_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.ground-scene-streams COMMAND mysmb_ground_scene_stream_smoke)
    add_executable(mysmb_underground_scene_stream_smoke test/underground_scene_stream_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_underground_scene_stream_smoke PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_underground_scene_stream_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.underground-scene-streams COMMAND mysmb_underground_scene_stream_smoke)
    add_executable(mysmb_water_scene_stream_smoke test/water_scene_stream_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_water_scene_stream_smoke PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_water_scene_stream_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.water-scene-streams COMMAND mysmb_water_scene_stream_smoke)
    add_executable(mysmb_block_graphics_smoke test/block_graphics_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_graphics_smoke PRIVATE src
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_block_graphics_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.block-graphics-smoke COMMAND mysmb_block_graphics_smoke)
    add_executable(mysmb_collision_regression_smoke test/collision_regression_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_collision_regression_smoke PRIVATE src
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_collision_regression_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.collision-regression-smoke
             COMMAND mysmb_collision_regression_smoke)
    add_executable(mysmb_enemy_background_entry_smoke test/enemy_background_entry_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_enemy_background_entry_smoke PRIVATE src
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_enemy_background_entry_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.enemy-background-entry COMMAND mysmb_enemy_background_entry_smoke)
    add_executable(mysmb_normal_movement_snapshot_check test/normal_movement_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_normal_movement_snapshot_check PRIVATE src)
    target_link_libraries(mysmb_normal_movement_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_entrance_snapshot_check test/entrance_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_entrance_snapshot_check PRIVATE src
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_entrance_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_player_control_snapshot_check test/player_control_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_player_control_snapshot_check PRIVATE src
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_player_control_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_player_transition_snapshot_check test/player_transition_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_player_transition_snapshot_check PRIVATE src
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_player_transition_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_player_modes_snapshot_check test/player_modes_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_player_modes_snapshot_check PRIVATE src
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_player_modes_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_player_end_level_snapshot_check test/player_end_level_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_player_end_level_snapshot_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_player_end_level_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_player_end_level_caller_check test/player_end_level_snapshot_check.c
        src/game/player_end_level.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_player_end_level_caller_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_player_end_level_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_fireball_dispatch_snapshot_check test/fireball_dispatch_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_fireball_dispatch_snapshot_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_fireball_dispatch_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_fireball_dispatch_caller_check test/fireball_dispatch_snapshot_check.c
        src/game/fireball/fireball_spawn.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_fireball_dispatch_caller_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_fireball_dispatch_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_fireball_core_snapshot_check test/fireball_core_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_fireball_core_snapshot_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_fireball_core_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_fireball_core_caller_check test/fireball_core_snapshot_check.c
        src/game/fireball/fireball_core.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_fireball_core_caller_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_fireball_core_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_block_buffer_player_actual_check
        test/block_buffer_player_actual_check.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_buffer_player_actual_check PRIVATE src
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_block_buffer_player_actual_check PRIVATE mysmb_game)
    add_executable(mysmb_timer_snapshot_check test/timer_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_timer_snapshot_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_timer_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_timer_caller_check test/timer_snapshot_check.c
        src/game/timer.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_timer_caller_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_timer_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_jumpspring_snapshot_check test/jumpspring_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_jumpspring_snapshot_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_jumpspring_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_jumpspring_caller_check test/jumpspring_snapshot_check.c
        src/game/jumpspring.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_jumpspring_caller_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_jumpspring_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_vine_actor_snapshot_check test/vine_actor_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_vine_actor_snapshot_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_vine_actor_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_vine_actor_caller_check test/vine_actor_snapshot_check.c
        src/game/vine.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_vine_actor_caller_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_vine_actor_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_hammer_chain_snapshot_check test/hammer_chain_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_hammer_chain_snapshot_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_hammer_chain_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_hammer_graphics_snapshot_check test/hammer_graphics_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_hammer_graphics_snapshot_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_hammer_graphics_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_hammer_chain_caller_check test/hammer_chain_snapshot_check.c
        src/game/hammer.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_hammer_chain_caller_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_hammer_chain_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_coin_allocation_snapshot_check test/coin_allocation_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_coin_allocation_snapshot_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_coin_allocation_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_coin_allocation_caller_check test/coin_allocation_snapshot_check.c
        src/game/coin.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_coin_allocation_caller_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_coin_allocation_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_misc_lifetime_snapshot_check test/misc_lifetime_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_misc_lifetime_snapshot_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_misc_lifetime_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_misc_lifetime_caller_check test/misc_lifetime_snapshot_check.c
        src/game/misc.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_misc_lifetime_caller_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_misc_lifetime_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_score_hud_snapshot_check test/score_hud_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_score_hud_snapshot_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_score_hud_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_score_hud_caller_check test/score_hud_snapshot_check.c
        src/game/score.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_score_hud_caller_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_score_hud_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_power_up_actor_snapshot_check test/power_up_actor_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_power_up_actor_snapshot_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_power_up_actor_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_power_up_actor_caller_check test/power_up_actor_snapshot_check.c
        src/game/power_up.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_power_up_actor_caller_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_power_up_actor_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_power_up_actor_child_check test/power_up_actor_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_power_up_actor_child_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_power_up_actor_child_check PRIVATE MYSMB_CHILD_DIAGNOSTIC=1)
    target_link_libraries(mysmb_power_up_actor_child_check PRIVATE mysmb_game)
    add_executable(mysmb_block_head_snapshot_check test/block_head_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_head_snapshot_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_block_head_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_block_head_caller_check test/block_head_snapshot_check.c
        src/game/blocks/head.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_head_caller_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_head_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_block_head_child_check test/block_head_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_head_child_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_head_child_check PRIVATE MYSMB_CHILD_DIAGNOSTIC=1)
    target_link_libraries(mysmb_block_head_child_check PRIVATE mysmb_game)
    add_executable(mysmb_block_bump_snapshot_check test/block_bump_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_bump_snapshot_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_block_bump_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_block_bump_caller_check test/block_bump_snapshot_check.c
        src/game/blocks/bump.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_bump_caller_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_bump_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_block_bump_child_check test/block_bump_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_bump_child_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_bump_child_check PRIVATE MYSMB_CHILD_DIAGNOSTIC=1)
    target_link_libraries(mysmb_block_bump_child_check PRIVATE mysmb_game)
    add_executable(mysmb_block_chunks_snapshot_check test/block_chunks_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_chunks_snapshot_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_block_chunks_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_block_chunks_caller_check test/block_chunks_snapshot_check.c
        src/game/blocks/chunks.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_chunks_caller_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_chunks_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_block_chunks_child_check test/block_chunks_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_chunks_child_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_chunks_child_check PRIVATE MYSMB_CHILD_DIAGNOSTIC=1)
    target_link_libraries(mysmb_block_chunks_child_check PRIVATE mysmb_game)
    add_executable(mysmb_block_lifetime_snapshot_check test/block_lifetime_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_lifetime_snapshot_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_block_lifetime_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_block_lifetime_caller_check test/block_lifetime_snapshot_check.c
        src/game/blocks/lifetime.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_lifetime_caller_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_lifetime_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_block_lifetime_child_check test/block_lifetime_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_lifetime_child_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_lifetime_child_check PRIVATE MYSMB_CHILD_DIAGNOSTIC=1)
    target_link_libraries(mysmb_block_lifetime_child_check PRIVATE mysmb_game)
    add_executable(mysmb_block_replacement_snapshot_check test/block_replacement_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_replacement_snapshot_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_block_replacement_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_block_replacement_caller_check test/block_replacement_snapshot_check.c
        src/game/blocks/replacement.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_replacement_caller_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_replacement_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_block_replacement_child_check test/block_replacement_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_replacement_child_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_replacement_child_check PRIVATE MYSMB_CHILD_DIAGNOSTIC=1)
    target_link_libraries(mysmb_block_replacement_child_check PRIVATE mysmb_game)
    add_executable(mysmb_player_movement_snapshot_check test/player_movement_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_player_movement_snapshot_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_player_movement_snapshot_check PRIVATE mysmb_game)
    add_executable(mysmb_player_movement_caller_check test/player_movement_snapshot_check.c
        src/game/player_movement.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_player_movement_caller_check PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_player_movement_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_palette_rotation_smoke test/palette_rotation_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_palette_rotation_smoke PRIVATE src
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_palette_rotation_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.palette-rotation-smoke COMMAND mysmb_palette_rotation_smoke)
    add_executable(mysmb_local_palette_timing_smoke test/local_palette_timing_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_local_palette_timing_smoke PRIVATE src
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_local_palette_timing_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.local-palette-timing-smoke
             COMMAND mysmb_local_palette_timing_smoke)
    add_executable(mysmb_local_victory_message_smoke test/local_victory_message_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_local_victory_message_smoke PRIVATE src
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_local_victory_message_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.local-victory-message-smoke
             COMMAND mysmb_local_victory_message_smoke)
    add_executable(mysmb_local_death_music_smoke test/local_death_music_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_local_death_music_smoke PRIVATE src
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_local_death_music_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.local-death-music-smoke
             COMMAND mysmb_local_death_music_smoke)
    add_executable(mysmb_local_frame_summary test/local_frame_summary.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>
        $<TARGET_OBJECTS:mysmb_local_title_data>)
    target_include_directories(mysmb_local_frame_summary PRIVATE src
        "${MYSMB_LOCAL_ROM_DIR}" "${MYSMB_LOCAL_TITLE_DIR}")
    target_link_libraries(mysmb_local_frame_summary PRIVATE mysmb_game)
    add_executable(mysmb_local_frame_recorder test/local_frame_recorder.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>
        $<TARGET_OBJECTS:mysmb_local_title_data>)
    target_include_directories(mysmb_local_frame_recorder PRIVATE src
        "${MYSMB_LOCAL_ROM_DIR}" "${MYSMB_LOCAL_TITLE_DIR}")
    target_link_libraries(mysmb_local_frame_recorder PRIVATE mysmb_game)

    if(MYSMB_ASM_PATH)
        add_custom_command(
            OUTPUT "${MYSMB_LOCAL_ROM_DIR}/smb1_symbols.txt"
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/smb_asm_index.py
                --rom "${MYSMB_ROM_PATH}" --asm "${MYSMB_ASM_PATH}"
                --output "${MYSMB_LOCAL_ROM_DIR}/smb1_symbols.txt"
            DEPENDS
                ${CMAKE_CURRENT_SOURCE_DIR}/tools/smb_asm_index.py
                ${CMAKE_CURRENT_SOURCE_DIR}/tools/smb_rom_codegen.py
                "${MYSMB_ROM_PATH}" "${MYSMB_ASM_PATH}"
            VERBATIM
        )
        add_custom_target(mysmb_local_symbols DEPENDS
            "${MYSMB_LOCAL_ROM_DIR}/smb1_symbols.txt"
        )
        add_dependencies(mysmb_local_symbols mysmb_local_rom)
    endif()
endif()

add_executable(mysmb_fireball_enemy_scan_smoke test/fireball_enemy_scan_smoke.c src/game/world/fireball_enemy.c)
target_include_directories(mysmb_fireball_enemy_scan_smoke PRIVATE src)
add_test(NAME mysmb.fireball-enemy-scan COMMAND mysmb_fireball_enemy_scan_smoke)

add_executable(mysmb_fireball_hit_smoke test/fireball_hit_smoke.c src/game/world/fireball_hit.c)
target_include_directories(mysmb_fireball_hit_smoke PRIVATE src)
add_test(NAME mysmb.fireball-hit-chain COMMAND mysmb_fireball_hit_smoke)

add_executable(mysmb_hammer_contact_smoke test/hammer_contact_smoke.c src/game/world/hammer_collision.c)
target_include_directories(mysmb_hammer_contact_smoke PRIVATE src)
add_test(NAME mysmb.hammer-contact-chain COMMAND mysmb_hammer_contact_smoke)

add_executable(mysmb_powerup_pickup_smoke test/powerup_pickup_smoke.c src/game/world/powerup_collision.c)
target_include_directories(mysmb_powerup_pickup_smoke PRIVATE src)
add_test(NAME mysmb.powerup-pickup-chain COMMAND mysmb_powerup_pickup_smoke)
add_executable(mysmb_player_enemy_contact_smoke test/player_enemy_contact_smoke.c src/game/world/player_enemy_collision.c)
target_include_directories(mysmb_player_enemy_contact_smoke PRIVATE src)
add_test(NAME mysmb.player-enemy-contact-chain COMMAND mysmb_player_enemy_contact_smoke)
add_executable(mysmb_enemy_pair_smoke test/enemy_pair_smoke.c src/game/world/enemy_collision.c)
target_include_directories(mysmb_enemy_pair_smoke PRIVATE src)
add_test(NAME mysmb.enemy-pair-chain COMMAND mysmb_enemy_pair_smoke)
add_executable(mysmb_platform_collision_smoke test/platform_collision_smoke.c src/game/enemy/platform_collision.c)
target_include_directories(mysmb_platform_collision_smoke PRIVATE src)
add_test(NAME mysmb.platform-collision-chain COMMAND mysmb_platform_collision_smoke)
add_executable(mysmb_platform_position_smoke test/platform_position_smoke.c src/game/enemy/platform_position.c)
target_include_directories(mysmb_platform_position_smoke PRIVATE src)
add_test(NAME mysmb.platform-positioning-chain COMMAND mysmb_platform_position_smoke)
add_executable(mysmb_collision_preflight_smoke test/collision_preflight_smoke.c)
target_link_libraries(mysmb_collision_preflight_smoke PRIVATE mysmb_game)
add_test(NAME mysmb.collision-preflight-chain COMMAND mysmb_collision_preflight_smoke)
add_executable(mysmb_player_terrain_smoke test/player_terrain_smoke.c src/game/player/terrain.c)
target_include_directories(mysmb_player_terrain_smoke PRIVATE src)
add_test(NAME mysmb.player-terrain-chain COMMAND mysmb_player_terrain_smoke)

add_executable(mysmb_terrain_metatile_smoke test/terrain_metatile_smoke.c src/game/player/terrain_metatiles.c)
target_include_directories(mysmb_terrain_metatile_smoke PRIVATE src)
add_test(NAME mysmb.terrain-metatile-chain COMMAND mysmb_terrain_metatile_smoke)

add_executable(mysmb_climbing_smoke test/climbing_smoke.c src/game/player/climbing.c)
target_include_directories(mysmb_climbing_smoke PRIVATE src)
add_test(NAME mysmb.climbing-chain COMMAND mysmb_climbing_smoke)

add_executable(mysmb_hidden_spring_smoke test/hidden_spring_smoke.c src/game/player/terrain_metatiles.c)
target_include_directories(mysmb_hidden_spring_smoke PRIVATE src)
add_test(NAME mysmb.hidden-spring-chain COMMAND mysmb_hidden_spring_smoke)

add_executable(mysmb_pipe_entry_smoke test/pipe_entry_smoke.c src/game/player/pipe_entry.c)
target_include_directories(mysmb_pipe_entry_smoke PRIVATE src)
add_test(NAME mysmb.pipe-entry-chain COMMAND mysmb_pipe_entry_smoke)

add_executable(mysmb_impede_smoke test/impede_smoke.c src/game/player/impede.c)
target_include_directories(mysmb_impede_smoke PRIVATE src)
add_test(NAME mysmb.impede-chain COMMAND mysmb_impede_smoke)

add_executable(mysmb_metatile_classification_smoke test/metatile_classification_smoke.c src/game/world/metatiles.c)
target_include_directories(mysmb_metatile_classification_smoke PRIVATE src)
add_test(NAME mysmb.metatile-classification-chain COMMAND mysmb_metatile_classification_smoke)

add_executable(mysmb_enemy_stun_smoke test/enemy_stun_smoke.c)
target_include_directories(mysmb_enemy_stun_smoke PRIVATE src)
target_link_libraries(mysmb_enemy_stun_smoke PRIVATE mysmb_game)
add_test(NAME mysmb.enemy-background-stun-chain COMMAND mysmb_enemy_stun_smoke)

add_executable(mysmb_enemy_landing_smoke test/enemy_landing_smoke.c
    src/game/enemy/background.c)
target_include_directories(mysmb_enemy_landing_smoke PRIVATE src)
add_test(NAME mysmb.enemy-landing-grounded-chain COMMAND mysmb_enemy_landing_smoke)
add_executable(mysmb_enemy_side_jump_hammer_smoke test/enemy_side_jump_hammer_smoke.c)
target_link_libraries(mysmb_enemy_side_jump_hammer_smoke PRIVATE mysmb_game)
add_test(NAME mysmb.enemy-side-jump-hammer-chain COMMAND mysmb_enemy_side_jump_hammer_smoke)
add_executable(mysmb_enemy_side_jump_hammer_actual_check
    test/enemy_side_jump_hammer_actual_check.c)
target_link_libraries(mysmb_enemy_side_jump_hammer_actual_check PRIVATE mysmb_game)
add_executable(mysmb_enemy_ground_query_nonsolids_smoke
    test/enemy_ground_query_nonsolids_smoke.c)
target_link_libraries(mysmb_enemy_ground_query_nonsolids_smoke PRIVATE mysmb_game)
add_test(NAME mysmb.enemy-ground-query-nonsolids-chain
    COMMAND mysmb_enemy_ground_query_nonsolids_smoke)
add_executable(mysmb_enemy_ground_query_actual_check
    test/enemy_ground_query_actual_check.c)
target_link_libraries(mysmb_enemy_ground_query_actual_check PRIVATE mysmb_game)
add_executable(mysmb_fireball_background_actual_check
    test/fireball_background_actual_check.c)
target_link_libraries(mysmb_fireball_background_actual_check PRIVATE mysmb_game)
add_executable(mysmb_bounding_box_entry_actual_check
    test/bounding_box_entry_actual_check.c)
target_link_libraries(mysmb_bounding_box_entry_actual_check PRIVATE mysmb_game)
add_executable(mysmb_enemy_bounding_box_entry_actual_check
    test/enemy_bounding_box_entry_actual_check.c)
target_link_libraries(mysmb_enemy_bounding_box_entry_actual_check PRIVATE mysmb_game)
add_executable(mysmb_platform_bounding_box_entry_actual_check
    test/platform_bounding_box_entry_actual_check.c)
target_link_libraries(mysmb_platform_bounding_box_entry_actual_check PRIVATE mysmb_game)
add_executable(mysmb_misc_bounding_box_entry_actual_check
    test/misc_bounding_box_entry_actual_check.c)
target_link_libraries(mysmb_misc_bounding_box_entry_actual_check PRIVATE mysmb_game)
