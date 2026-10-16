set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(mysmb_input_latch_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/io/input_latch_smoke.c kvm/io/input_latch.c)
target_include_directories(mysmb_input_latch_smoke PRIVATE . kvm)
add_test(NAME mysmb.io-clocked-input-latch COMMAND mysmb_input_latch_smoke)

# KVM is the project-wide neutral header contract.  A number of Mario's
# owner-local checks compile a narrow source unit directly rather than link a
# library target, so give those isolated units the same contract include root.
include_directories("${CMAKE_SOURCE_DIR}/src/lib")

set(MYSMB_WIN32_ARCH "host" CACHE STRING "Win32 target label: x86, x64, or host")
set_property(CACHE MYSMB_WIN32_ARCH PROPERTY STRINGS host x86 x64)
if(WIN32)
    if((MYSMB_WIN32_ARCH STREQUAL "x86" AND NOT CMAKE_SIZEOF_VOID_P EQUAL 4) OR
       (MYSMB_WIN32_ARCH STREQUAL "x64" AND NOT CMAKE_SIZEOF_VOID_P EQUAL 8))
        message(FATAL_ERROR "MYSMB_WIN32_ARCH must match the selected compiler's pointer width; select the matching toolchain or preset")
    endif()
endif()
set(MYSMB_ROM_PATH "" CACHE FILEPATH "Owner-local SMB1 NROM image")
set(MYSMB_ASM_PATH "" CACHE FILEPATH "Owner-local reviewed SMBDIS listing")
set(MYSMB_OPENNT_CL16 "" CACHE FILEPATH "Owner-local OpenNT 16-bit cl16.exe")
set(MYSMB_DOS_RUNTIME_DIR "" CACHE PATH "Owner-local reviewed 16-bit large-model runtime directory")
set(MYSMB_CACHE_PRODUCT_DIR "" CACHE PATH "Existing optimized DOS16 product objects for cache qualification")
set(MYSMB_DOSBOX_EXECUTABLE "" CACHE FILEPATH "Installed DOSBox for explicit host qualification")
set(MYSMB_DOSBOX_CONFIG "" CACHE FILEPATH "Unmodified owner DOSBox configuration")
add_test(NAME mysmb.dos16-cache-receipt COMMAND ${Python3_EXECUTABLE}
    "${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/dos16/test_cache_receipt.py")
if(WIN32)
    add_custom_target(mysmb_dos16_cache_integration
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-Dos16CacheProbe.ps1"
            -ProductDirectory "${MYSMB_CACHE_PRODUCT_DIR}"
            -OutputDirectory "${CMAKE_BINARY_DIR}/dos16-cache-probe"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-Dos16CacheProbe.ps1"
            -ProductDirectory "${MYSMB_CACHE_PRODUCT_DIR}"
            -OutputDirectory "${CMAKE_BINARY_DIR}/dos16-cache-probe" -LinkOnly
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Invoke-Dos16CacheProbe.ps1"
            -ProbeDirectory "${CMAKE_BINARY_DIR}/dos16-cache-probe"
            -DosBoxExecutable "${MYSMB_DOSBOX_EXECUTABLE}"
            -DosBoxConfiguration "${MYSMB_DOSBOX_CONFIG}"
        COMMAND ${Python3_EXECUTABLE} "${CMAKE_SOURCE_DIR}/tools/VerifyDos16CacheReceipt.py"
            "${CMAKE_BINARY_DIR}/dos16-cache-probe"
        USES_TERMINAL VERBATIM)
endif()

set(MYSMB_CORE_SOURCES core/boot.c core/dispatcher.c core/engine.c core/engine_slots.c core/engine_tail.c core/frame_root.c core/title_modes.c core/terminal_modes.c core/game.c core/audio.c core/area.c core/status.c core/area/block_metatile.c core/enemy/stream.c core/enemy/group.c core/enemy/init.c core/enemy/init_targets.c core/enemy/loop.c core/enemy/core.c core/enemy/dispatch_targets.c core/enemy/movement.c core/enemy/frenzy.c core/player.c core/objects.c core/fireball/fireball_spawn.c core/fireball/fireball_core.c core/world/movement.c core/world/gravity.c core/world/collision.c core/world/block_buffer.c core/world/bounding_box.c core/world/geometry.c core/bridge.c core/oam/bullet_bill_gfx.c core/oam/hammer_gfx.c core/oam/firebar_gfx.c core/oam/vine_gfx.c core/oam/sprite_stacker.c core/oam/sprite_dump.c core/enemy_bounds.c core/oam/power_up_gfx.c core/oam/object_position.c core/oam/sprite_row.c core/oam/player_gfx.c core/oam/fireball_gfx.c core/oam/block_gfx.c core/oam/goomba_gfx.c core/fireball/bubble.c core/oam/piranha_gfx.c core/oam/cheep_gfx.c core/oam/bloober_gfx.c core/oam/podoboo_gfx.c core/oam/normal_enemy_gfx.c core/oam/spiny_gfx.c core/oam/hammer_bro_gfx.c core/oam/bowser_gfx.c core/oam/bowser_flame_gfx.c core/endgame_objects.c core/oam/flagpole_gfx.c core/oam/small_platform_gfx.c )
list(APPEND MYSMB_CORE_SOURCES core/oam/enemy_offscreen.c core/oam/sprite_draw.c core/oam/block_offscreen.c)
list(APPEND MYSMB_CORE_SOURCES core/player/terrain.c core/player/terrain_metatiles.c core/player/climbing.c core/player/pipe_entry.c core/player/impede.c core/world/metatiles.c)
list(APPEND MYSMB_CORE_SOURCES core/area/block_buffer.c)
list(APPEND MYSMB_CORE_SOURCES core/area/area_data.c)
list(APPEND MYSMB_CORE_SOURCES core/whirlpool.c)
list(APPEND MYSMB_CORE_SOURCES core/cannon.c)
list(APPEND MYSMB_CORE_SOURCES core/timer.c)
list(APPEND MYSMB_CORE_SOURCES core/jumpspring.c)
list(APPEND MYSMB_CORE_SOURCES core/vine.c)
list(APPEND MYSMB_CORE_SOURCES core/hammer.c)
list(APPEND MYSMB_CORE_SOURCES core/coin.c)
list(APPEND MYSMB_CORE_SOURCES core/misc.c core/score.c core/power_up_init.c core/power_up.c)
list(APPEND MYSMB_CORE_SOURCES core/blocks/head.c core/blocks/bump.c core/blocks/chunks.c core/blocks/lifetime.c core/blocks/replacement.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/lifecycle.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/normal.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/special_callers.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/platform_callers.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/podoboo.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/hammer_bro.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/paratroopa.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/x_counter.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/green_paratroopa.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/bloober.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/bullet_bill.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/swimming_cheep.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/firebar.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/flying_cheep.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/lakitu.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/bowser.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/bowser_flame.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/fireworks.c core/oam/fireworks_gfx.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/star_flag.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/piranha.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/balance_platform.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/platform.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/actor_slots.c)
list(APPEND MYSMB_CORE_SOURCES core/world/fireball_enemy.c)
list(APPEND MYSMB_CORE_SOURCES core/world/fireball_hit.c)
list(APPEND MYSMB_CORE_SOURCES core/world/hammer_collision.c)
list(APPEND MYSMB_CORE_SOURCES core/world/powerup_collision.c core/world/player_enemy_collision.c)
list(APPEND MYSMB_CORE_SOURCES core/world/enemy_collision.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/platform_collision.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/platform_position.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/firebar_children.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/distance.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/background.c core/enemy/jump_terrain.c)
list(APPEND MYSMB_CORE_SOURCES core/enemy/side_collision.c)
list(APPEND MYSMB_CORE_SOURCES core/scroll.c)
list(APPEND MYSMB_CORE_SOURCES core/entry.c)
list(APPEND MYSMB_CORE_SOURCES core/player_control.c)
list(APPEND MYSMB_CORE_SOURCES core/player_transition.c)
list(APPEND MYSMB_CORE_SOURCES core/player_modes.c)
list(APPEND MYSMB_CORE_SOURCES core/player_end_level.c)
list(APPEND MYSMB_CORE_SOURCES core/player_movement.c)
list(APPEND MYSMB_CORE_SOURCES core/observation.c)
add_library(mysmb_text_snapshot STATIC kvm/text/observer_snapshot.c)
target_include_directories(mysmb_text_snapshot PUBLIC . kvm)
target_link_libraries(mysmb_text_snapshot PUBLIC mysmb_core)
add_library(mysmb_ppu_frame STATIC kvm/ppu/frame.c)
target_include_directories(mysmb_ppu_frame PUBLIC . kvm)
add_library(mysmb_ppu_state STATIC kvm/ppu/state.c)
target_include_directories(mysmb_ppu_state PUBLIC . kvm)
target_link_libraries(mysmb_ppu_state PUBLIC mygames_kvm)
add_library(mysmb_core STATIC ${MYSMB_CORE_SOURCES})
target_link_libraries(mysmb_core PUBLIC mysmb_ppu_state)
add_executable(mysmb_ppu_state_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/ppu/ppu_state_smoke.c)
target_link_libraries(mysmb_ppu_state_smoke PRIVATE mysmb_ppu_state)
add_test(NAME mysmb.ppu-state-smoke COMMAND mysmb_ppu_state_smoke)
target_include_directories(mysmb_core PUBLIC . kvm)

# Composition glue depends only on public game output and neutral contracts.
add_library(mysmb_game_io STATIC kvm/app/game_io.c)
target_include_directories(mysmb_game_io PUBLIC . kvm)
target_link_libraries(mysmb_game_io PUBLIC mysmb_ppu_frame)
add_library(mysmb_io_support STATIC kvm/io/color.c kvm/io/palette_pairs.c kvm/io/palette_expand.c kvm/io/scale.c kvm/io/pacing.c kvm/io/control.c)
target_link_libraries(mysmb_io_support PUBLIC mygames_kvm)
target_link_libraries(mysmb_ppu_frame PUBLIC mysmb_io_support)
target_include_directories(mysmb_io_support PUBLIC . kvm)
add_library(mysmb_io_snapshot STATIC kvm/io/snapshot.c kvm/io/snapshot_store.c
    kvm/io/snapshot_keys.c)
target_include_directories(mysmb_io_snapshot PUBLIC . kvm)
target_link_libraries(mysmb_io_snapshot PUBLIC mygames_kvm)
if(NOT MSVC)
    target_link_libraries(mysmb_io_snapshot PUBLIC m)
    target_compile_options(mysmb_io_snapshot PRIVATE -Wall -Wextra -Werror -pedantic)
endif()
add_executable(mysmb_io_snapshot_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/io/io_snapshot_smoke.c
    kvm/platform/win32/audio_snapshot_real.c)
target_link_libraries(mysmb_io_snapshot_smoke PRIVATE mysmb_io_snapshot)
add_test(NAME mysmb.io-snapshot-smoke COMMAND mysmb_io_snapshot_smoke)
add_executable(mysmb_snapshot_storage_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/app/snapshot_storage_smoke.c
    kvm/io/file/snapshot_files.c )
target_link_libraries(mysmb_snapshot_storage_smoke PRIVATE mysmb_io_snapshot mygames_win32)
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/snapshot-storage-test")
add_test(NAME mysmb.snapshot-storage-smoke COMMAND mysmb_snapshot_storage_smoke
    "${CMAKE_BINARY_DIR}/snapshot-storage-test")
add_library(mysmb_game_snapshot STATIC kvm/app/game_snapshot.c)
target_include_directories(mysmb_game_snapshot PUBLIC . kvm)
target_link_libraries(mysmb_game_snapshot PUBLIC mysmb_io_snapshot mysmb_core mysmb_text_snapshot)
add_executable(mysmb_game_snapshot_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/app/game_snapshot_smoke.c)
target_link_libraries(mysmb_game_snapshot_smoke PRIVATE mysmb_game_snapshot mysmb_ppu_frame)
add_test(NAME mysmb.game-snapshot-smoke COMMAND mysmb_game_snapshot_smoke)
add_executable(mysmb_text_observation_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/text/text_observation_smoke.c)
target_link_libraries(mysmb_text_observation_smoke PRIVATE mysmb_game_snapshot mysmb_ppu_frame)
add_test(NAME mysmb.text-observation-smoke COMMAND mysmb_text_observation_smoke)
add_executable(mysmb_audio_snapshot_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/win32/audio_snapshot_smoke.c
    kvm/platform/win32/audio_snapshot.c kvm/platform/win32/audio_snapshot_real.c
    kvm/platform/win32/audio_renderer.c)
target_link_libraries(mysmb_audio_snapshot_smoke PRIVATE mysmb_io_snapshot)
add_test(NAME mysmb.audio-snapshot-smoke COMMAND mysmb_audio_snapshot_smoke)
if(NOT MSVC)
    target_compile_options(mysmb_game_snapshot PRIVATE -Wall -Wextra -Werror -pedantic)
endif()
add_executable(mysmb_io_pacing_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/io/io_pacing_smoke.c)
target_link_libraries(mysmb_io_pacing_smoke PRIVATE mysmb_io_support)
add_test(NAME mysmb.io-pacing-smoke COMMAND mysmb_io_pacing_smoke)
add_executable(mysmb_game_io_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/app/game_io_smoke.c)
target_link_libraries(mysmb_game_io_smoke PRIVATE mysmb_game_io)
add_test(NAME mysmb.game-io-smoke COMMAND mysmb_game_io_smoke)
add_library(mysmb_app_input_mapping STATIC kvm/app/input_mapping.c)
target_include_directories(mysmb_app_input_mapping PUBLIC . kvm)
target_link_libraries(mysmb_app_input_mapping PUBLIC mygames_kvm)
add_executable(mysmb_app_input_mapping_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/app/app_input_mapping_smoke.c)
target_link_libraries(mysmb_app_input_mapping_smoke PRIVATE mysmb_app_input_mapping)
add_test(NAME mysmb.app-input-mapping-smoke COMMAND mysmb_app_input_mapping_smoke)

# IO contracts have no device or translated-game implementation dependency.
add_executable(mysmb_io_contract_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/io/io_contract_smoke.c)
target_link_libraries(mysmb_io_contract_smoke PRIVATE mysmb_io_support)
add_executable(mysmb_io_support_text_projection_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/io/io_color_text_projection_smoke.c)
target_link_libraries(mysmb_io_support_text_projection_smoke PRIVATE mysmb_io_support)
target_include_directories(mysmb_io_contract_smoke PRIVATE . kvm)
target_include_directories(mysmb_io_support_text_projection_smoke PRIVATE . kvm)
if(MSVC)
    target_compile_options(mysmb_io_contract_smoke PRIVATE /W4 /WX)
    target_compile_options(mysmb_io_support_text_projection_smoke PRIVATE /W4 /WX)
else()
    target_compile_options(mysmb_io_contract_smoke PRIVATE -Wall -Wextra -Werror -pedantic)
    target_compile_options(mysmb_io_support_text_projection_smoke PRIVATE -Wall -Wextra -Werror -pedantic)
endif()
add_test(NAME mysmb.io-contract-smoke COMMAND mysmb_io_contract_smoke)
add_test(NAME mysmb.io-color-text-projection-smoke COMMAND mysmb_io_support_text_projection_smoke)

if(MSVC)
    target_compile_options(mysmb_core PRIVATE /W4 /WX)
else()
    target_compile_options(mysmb_core PRIVATE -Wall -Wextra -Werror -pedantic)
endif()

add_executable(mysmb_core_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/core_smoke.c)
target_link_libraries(mysmb_core_smoke PRIVATE mysmb_core)
add_executable(mysmb_ram_cold_start_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/ram_cold_start_smoke.c)
target_link_libraries(mysmb_ram_cold_start_smoke PRIVATE mysmb_core)
add_executable(mysmb_reset_root_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/reset_root_smoke.c)
target_link_libraries(mysmb_reset_root_smoke PRIVATE mysmb_core)
add_executable(mysmb_boot_nmi_boundary_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/boot_nmi_boundary_smoke.c)
target_link_libraries(mysmb_boot_nmi_boundary_smoke PRIVATE mysmb_core)
add_executable(mysmb_nmi_parent_integration_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/nmi_parent_integration_check.c)
target_link_libraries(mysmb_nmi_parent_integration_check PRIVATE mysmb_core)
add_executable(mysmb_name_table_init_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/name_table_init_smoke.c)
target_link_libraries(mysmb_name_table_init_smoke PRIVATE mysmb_core)
add_executable(mysmb_vram_address_table_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/vram_address_table_smoke.c)
target_link_libraries(mysmb_vram_address_table_smoke PRIVATE mysmb_core)
add_executable(mysmb_joypad_vram_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/joypad_vram_chain_smoke.c)
target_link_libraries(mysmb_joypad_vram_chain_smoke PRIVATE mysmb_core)
add_executable(mysmb_pseudorandom_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/pseudorandom_smoke.c)
target_link_libraries(mysmb_pseudorandom_smoke PRIVATE mysmb_core)
add_executable(mysmb_timer_root_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/timer_root_smoke.c)
target_link_libraries(mysmb_timer_root_smoke PRIVATE mysmb_core)
add_executable(mysmb_pause_root_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/pause_root_smoke.c)
target_link_libraries(mysmb_pause_root_smoke PRIVATE mysmb_core)
add_executable(mysmb_sprite_root_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/sprite_root_smoke.c)
target_link_libraries(mysmb_sprite_root_smoke PRIVATE mysmb_core)
add_executable(mysmb_top_score_root_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/top_score_root_smoke.c)
target_link_libraries(mysmb_top_score_root_smoke PRIVATE mysmb_core)
add_executable(mysmb_status_arithmetic_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/status_arithmetic_smoke.c)
target_link_libraries(mysmb_status_arithmetic_smoke PRIVATE mysmb_core)
target_link_libraries(mysmb_pseudorandom_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_music_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_music_smoke.c)
target_link_libraries(mysmb_area_music_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_entry_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_entry_smoke.c)
target_link_libraries(mysmb_area_entry_smoke PRIVATE mysmb_core)
add_executable(mysmb_music_header_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/music_header_smoke.c)
target_link_libraries(mysmb_music_header_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_parser_column_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_parser_column_smoke.c)
target_link_libraries(mysmb_area_parser_column_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_parser_terminal_slot_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_parser_terminal_slot_smoke.c)
target_link_libraries(mysmb_area_parser_terminal_slot_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_special_object_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_special_object_smoke.c)
target_link_libraries(mysmb_area_special_object_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_rope_object_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_rope_object_smoke.c)
target_link_libraries(mysmb_area_rope_object_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_coin_row_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_coin_row_smoke.c)
target_link_libraries(mysmb_area_coin_row_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_castle_column_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_castle_column_smoke.c)
target_link_libraries(mysmb_area_castle_column_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_block_row_column_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_block_row_column_smoke.c)
target_link_libraries(mysmb_area_block_row_column_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_cannon_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_cannon_smoke.c)
target_link_libraries(mysmb_area_cannon_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_staircase_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_staircase_smoke.c)
target_link_libraries(mysmb_area_staircase_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_jumpspring_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_jumpspring_smoke.c)
target_link_libraries(mysmb_area_jumpspring_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_item_block_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_item_block_smoke.c)
target_link_libraries(mysmb_area_item_block_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_pipe_tail_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_pipe_tail_smoke.c)
target_link_libraries(mysmb_area_pipe_tail_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_block_address_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_block_address_smoke.c)
target_link_libraries(mysmb_area_block_address_smoke PRIVATE mysmb_core)
add_executable(mysmb_block_buffer_core_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_buffer_core_smoke.c)
target_link_libraries(mysmb_block_buffer_core_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_parser_boundary_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_parser_boundary_smoke.c)
target_link_libraries(mysmb_area_parser_boundary_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_loop_command_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_loop_command_smoke.c)
target_link_libraries(mysmb_area_loop_command_smoke PRIVATE mysmb_core)
add_executable(mysmb_game_entry_dispatch_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/game_entry_dispatch_smoke.c core/dispatcher.c)
target_include_directories(mysmb_game_entry_dispatch_smoke PRIVATE . kvm)
add_executable(mysmb_engine_caller_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/engine_caller_smoke.c core/engine.c)
target_include_directories(mysmb_engine_caller_smoke PRIVATE . kvm)
add_executable(mysmb_engine_tail_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/engine_tail_smoke.c core/engine_tail.c core/player_modes.c)
target_include_directories(mysmb_engine_tail_smoke PRIVATE . kvm)
add_executable(mysmb_engine_slots_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/engine_slots_smoke.c core/engine_slots.c)
target_include_directories(mysmb_engine_slots_smoke PRIVATE . kvm)
add_executable(mysmb_engine_environment_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/engine_environment_smoke.c core/whirlpool.c)
target_include_directories(mysmb_engine_environment_smoke PRIVATE . kvm)
add_executable(mysmb_cannon_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/cannon_smoke.c core/cannon.c)
target_include_directories(mysmb_cannon_smoke PRIVATE . kvm)
add_executable(mysmb_cannon_children_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/cannon_children_smoke.c core/enemy/core.c core/enemy/lifecycle.c core/oam/bullet_bill_gfx.c core/observation.c)
target_include_directories(mysmb_cannon_children_smoke PRIVATE . kvm)
add_executable(mysmb_enemy_dispatch_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_dispatch_smoke.c core/enemy/core.c core/enemy/lifecycle.c)
target_include_directories(mysmb_enemy_dispatch_smoke PRIVATE . kvm)
add_executable(mysmb_enemy_loop_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_loop_smoke.c core/enemy/loop.c)
target_include_directories(mysmb_enemy_loop_smoke PRIVATE . kvm)
add_executable(mysmb_normal_enemy_movement_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/normal_enemy_movement_smoke.c core/enemy/movement.c core/world/gravity.c)
target_include_directories(mysmb_normal_enemy_movement_smoke PRIVATE . kvm)
add_executable(mysmb_normal_enemy_caller_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/normal_enemy_caller_smoke.c core/enemy/normal.c)
target_include_directories(mysmb_normal_enemy_caller_smoke PRIVATE . kvm)
add_executable(mysmb_enemy_background_caller_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_background_caller_smoke.c core/enemy/background.c core/enemy/jump_terrain.c core/enemy/distance.c)
target_include_directories(mysmb_enemy_background_caller_smoke PRIVATE . kvm)
add_executable(mysmb_enemy_side_caller_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_side_caller_smoke.c core/enemy/side_collision.c)
target_include_directories(mysmb_enemy_side_caller_smoke PRIVATE . kvm)
add_executable(mysmb_area_helper_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_helper_smoke.c)
target_link_libraries(mysmb_area_helper_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_hole_underpart_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_hole_underpart_smoke.c)
target_link_libraries(mysmb_area_hole_underpart_smoke PRIVATE mysmb_core)
add_executable(mysmb_area_initialize_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_initialize_smoke.c)
target_link_libraries(mysmb_area_initialize_smoke PRIVATE mysmb_core)
add_executable(mysmb_enemy_stream_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_stream_smoke.c)
target_link_libraries(mysmb_enemy_stream_smoke PRIVATE mysmb_core)
add_executable(mysmb_enemy_no_init_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_no_init_smoke.c)
target_link_libraries(mysmb_enemy_no_init_smoke PRIVATE mysmb_core)
add_executable(mysmb_enemy_init_handoff_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_init_handoff_smoke.c core/enemy/init.c)
target_include_directories(mysmb_enemy_init_handoff_smoke PRIVATE . kvm)
add_executable(mysmb_enemy_init_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_init_snapshot_check.c core/enemy/init.c)
target_include_directories(mysmb_enemy_init_snapshot_check PRIVATE . kvm)
add_executable(mysmb_enemy_common_init_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_common_init_smoke.c core/enemy/init_targets.c core/enemy/lifecycle.c)
target_include_directories(mysmb_enemy_common_init_smoke PRIVATE . kvm)
add_executable(mysmb_lakitu_spiny_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/lakitu_spiny_chain_smoke.c)
target_link_libraries(mysmb_lakitu_spiny_chain_smoke PRIVATE mysmb_core)
add_executable(mysmb_firebar_initialization_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/firebar_initialization_smoke.c core/enemy/init_targets.c core/enemy/lifecycle.c)
target_include_directories(mysmb_firebar_initialization_smoke PRIVATE . kvm)
add_executable(mysmb_flying_fish_initialization_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/flying_fish_initialization_smoke.c)
target_link_libraries(mysmb_flying_fish_initialization_smoke PRIVATE mysmb_core)
add_executable(mysmb_bowser_flame_initialization_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/bowser_flame_initialization_smoke.c)
target_link_libraries(mysmb_bowser_flame_initialization_smoke PRIVATE mysmb_core)
add_executable(mysmb_fireworks_initialization_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/fireworks_initialization_smoke.c)
target_link_libraries(mysmb_fireworks_initialization_smoke PRIVATE mysmb_core)
add_executable(mysmb_bullet_swimming_fish_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/bullet_swimming_fish_smoke.c)
target_link_libraries(mysmb_bullet_swimming_fish_smoke PRIVATE mysmb_core)
add_executable(mysmb_group_enemy_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/group_enemy_smoke.c)
target_link_libraries(mysmb_group_enemy_smoke PRIVATE mysmb_core)
add_executable(mysmb_small_initializers_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/small_initializers_smoke.c)
target_link_libraries(mysmb_small_initializers_smoke PRIVATE mysmb_core)
add_executable(mysmb_platform_initialization_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/platform_initialization_smoke.c)
target_link_libraries(mysmb_platform_initialization_smoke PRIVATE mysmb_core)
add_executable(mysmb_retainer_call_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/retainer_call_chain_smoke.c core/enemy/dispatch_targets.c)
add_executable(mysmb_podoboo_movement_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/podoboo_movement_smoke.c core/enemy/podoboo.c)
add_executable(mysmb_hammer_movement_caller_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/hammer_movement_caller_smoke.c core/enemy/hammer_bro.c)
add_executable(mysmb_paratroopa_movement_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/paratroopa_movement_smoke.c core/enemy/paratroopa.c)
add_executable(mysmb_green_counter_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/green_counter_smoke.c core/enemy/green_paratroopa.c core/enemy/x_counter.c)
add_executable(mysmb_bloober_movement_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/bloober_movement_smoke.c core/enemy/bloober.c core/enemy/distance.c)
add_executable(mysmb_bullet_movement_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/bullet_movement_smoke.c core/enemy/bullet_bill.c)
add_executable(mysmb_swimming_cheep_movement_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/swimming_cheep_movement_smoke.c core/enemy/swimming_cheep.c)
add_executable(mysmb_firebar_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/firebar_chain_smoke.c core/enemy/firebar.c)
add_executable(mysmb_lakitu_movement_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/lakitu_movement_smoke.c core/enemy/lakitu.c)
add_executable(mysmb_bridge_collapse_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/bridge_collapse_smoke.c core/bridge.c)
add_executable(mysmb_bowser_control_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/bowser_control_smoke.c core/enemy/bowser.c)
add_executable(mysmb_bowser_graphics_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/bowser_graphics_smoke.c core/oam/bowser_gfx.c)
target_include_directories(mysmb_bowser_graphics_smoke PRIVATE . kvm)
add_executable(mysmb_bowser_flame_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/bowser_flame_chain_smoke.c core/enemy/bowser_flame.c core/oam/bowser_flame_gfx.c core/observation.c)
target_include_directories(mysmb_bowser_flame_chain_smoke PRIVATE . kvm)
add_executable(mysmb_fireworks_lifetime_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/fireworks_lifetime_smoke.c core/enemy/fireworks.c)
add_executable(mysmb_star_flag_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/star_flag_smoke.c core/enemy/star_flag.c core/observation.c)
target_include_directories(mysmb_star_flag_smoke PRIVATE . kvm)
add_executable(mysmb_star_flag_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/star_flag_snapshot_check.c)
target_link_libraries(mysmb_star_flag_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_piranha_movement_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/piranha_movement_smoke.c core/enemy/piranha.c)
target_include_directories(mysmb_piranha_movement_smoke PRIVATE . kvm)
add_executable(mysmb_firebar_spin_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/firebar_spin_smoke.c core/enemy/firebar_children.c)
target_include_directories(mysmb_firebar_spin_smoke PRIVATE . kvm)
add_executable(mysmb_balance_platform_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/balance_platform_smoke.c core/enemy/balance_platform.c)
target_include_directories(mysmb_balance_platform_smoke PRIVATE . kvm)
add_executable(mysmb_vertical_platform_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/vertical_platform_smoke.c core/enemy/platform.c)
target_include_directories(mysmb_vertical_platform_smoke PRIVATE . kvm)
add_executable(mysmb_horizontal_platform_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/horizontal_platform_smoke.c core/enemy/platform.c)
target_include_directories(mysmb_horizontal_platform_smoke PRIVATE . kvm)
add_executable(mysmb_lift_platform_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/lift_platform_smoke.c core/enemy/platform.c)
target_include_directories(mysmb_lift_platform_smoke PRIVATE . kvm)
add_executable(mysmb_offscreen_bounds_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/offscreen_bounds_smoke.c core/enemy/actor_slots.c)
target_include_directories(mysmb_offscreen_bounds_smoke PRIVATE . kvm)
add_executable(mysmb_jumpspring_origin_offscreen_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/jumpspring_origin_offscreen_smoke.c core/jumpspring.c core/enemy/actor_slots.c)
target_include_directories(mysmb_jumpspring_origin_offscreen_smoke PRIVATE . kvm)
target_include_directories(mysmb_fireworks_lifetime_smoke PRIVATE . kvm)
target_include_directories(mysmb_bowser_control_smoke PRIVATE . kvm)
target_include_directories(mysmb_bridge_collapse_smoke PRIVATE . kvm)
target_include_directories(mysmb_lakitu_movement_smoke PRIVATE . kvm)
add_executable(mysmb_flying_cheep_movement_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/flying_cheep_movement_smoke.c core/enemy/flying_cheep.c)
target_include_directories(mysmb_flying_cheep_movement_smoke PRIVATE . kvm)
target_include_directories(mysmb_firebar_chain_smoke PRIVATE . kvm)
target_include_directories(mysmb_swimming_cheep_movement_smoke PRIVATE . kvm)
target_include_directories(mysmb_bullet_movement_smoke PRIVATE . kvm)
target_include_directories(mysmb_bloober_movement_smoke PRIVATE . kvm)
target_include_directories(mysmb_green_counter_smoke PRIVATE . kvm)
target_include_directories(mysmb_paratroopa_movement_smoke PRIVATE . kvm)
target_include_directories(mysmb_hammer_movement_caller_smoke PRIVATE . kvm)
target_include_directories(mysmb_podoboo_movement_smoke PRIVATE . kvm)
add_executable(mysmb_special_actor_caller_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/special_actor_caller_smoke.c core/enemy/special_callers.c)
target_include_directories(mysmb_special_actor_caller_smoke PRIVATE . kvm)
add_executable(mysmb_platform_caller_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/platform_caller_smoke.c core/enemy/platform_callers.c core/enemy/lifecycle.c)
target_include_directories(mysmb_platform_caller_smoke PRIVATE . kvm)
target_include_directories(mysmb_retainer_call_chain_smoke PRIVATE . kvm)
add_executable(mysmb_enemy_stream_boundary_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_stream_boundary_smoke.c core/enemy/stream.c)
target_include_directories(mysmb_enemy_stream_boundary_smoke PRIVATE . kvm)
add_executable(mysmb_parser_schedule_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/parser_schedule_smoke.c)
target_link_libraries(mysmb_parser_schedule_smoke PRIVATE mysmb_core)
add_executable(mysmb_parser_buffer_commit_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/parser_buffer_commit_smoke.c)
target_link_libraries(mysmb_parser_buffer_commit_smoke PRIVATE mysmb_core)
add_executable(mysmb_screen_parser_output_chain_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/screen_parser_output_chain_check.c)
target_link_libraries(mysmb_screen_parser_output_chain_check PRIVATE mysmb_core)
add_executable(mysmb_kill_enemies_shared_primitive_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/kill_enemies_shared_primitive_check.c)
target_link_libraries(mysmb_kill_enemies_shared_primitive_check PRIVATE mysmb_core)
add_executable(mysmb_player_route_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_route_smoke.c)
add_executable(mysmb_player_scroll_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_scroll_chain_smoke.c core/scroll.c)
add_executable(mysmb_player_entry_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_entry_chain_smoke.c core/entry.c)
add_executable(mysmb_player_control_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_control_chain_smoke.c core/player_control.c)
target_include_directories(mysmb_player_control_chain_smoke PRIVATE . kvm)
add_executable(mysmb_player_transition_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_transition_chain_smoke.c core/player_transition.c)
add_executable(mysmb_player_modes_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_modes_chain_smoke.c core/player_modes.c)
target_include_directories(mysmb_player_modes_chain_smoke PRIVATE . kvm)
add_executable(mysmb_player_end_level_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_end_level_chain_smoke.c core/player_end_level.c)
target_include_directories(mysmb_player_end_level_chain_smoke PRIVATE . kvm)
add_executable(mysmb_player_movement_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_movement_chain_smoke.c core/player_movement.c)
target_include_directories(mysmb_player_movement_chain_smoke PRIVATE . kvm)
add_executable(mysmb_player_climbing_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_climbing_chain_smoke.c)
target_include_directories(mysmb_player_climbing_chain_smoke PRIVATE . kvm)
target_link_libraries(mysmb_player_climbing_chain_smoke PRIVATE mysmb_core)
add_executable(mysmb_player_physics_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_physics_chain_smoke.c)
target_include_directories(mysmb_player_physics_chain_smoke PRIVATE . kvm)
target_link_libraries(mysmb_player_physics_chain_smoke PRIVATE mysmb_core)
add_executable(mysmb_player_animation_friction_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_animation_friction_chain_smoke.c)
add_executable(mysmb_fireball_dispatch_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/fireball/fireball_dispatch_chain_smoke.c core/fireball/fireball_spawn.c)
target_include_directories(mysmb_fireball_dispatch_chain_smoke PRIVATE . kvm)
add_executable(mysmb_fireball_core_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/fireball/fireball_core_chain_smoke.c core/fireball/fireball_core.c)
target_include_directories(mysmb_fireball_core_chain_smoke PRIVATE . kvm)
add_executable(mysmb_bubble_core_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/fireball/bubble_core_chain_smoke.c core/fireball/bubble.c core/oam/object_position.c core/observation.c)
target_include_directories(mysmb_bubble_core_chain_smoke PRIVATE . kvm)
add_executable(mysmb_bubble_core_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/fireball/bubble_core_snapshot_check.c core/fireball/bubble.c core/oam/object_position.c core/observation.c)
target_include_directories(mysmb_bubble_core_snapshot_check PRIVATE . kvm)
add_executable(mysmb_object_relative_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/object_relative_snapshot_check.c)
target_link_libraries(mysmb_object_relative_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_player_offscreen_entry_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_offscreen_entry_snapshot_check.c)
target_link_libraries(mysmb_player_offscreen_entry_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_offscreen_chain_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/offscreen_chain_snapshot_check.c)
target_link_libraries(mysmb_offscreen_chain_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_sprite_row_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/sprite_row_snapshot_check.c)
target_link_libraries(mysmb_sprite_row_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_timer_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/timer_chain_smoke.c core/timer.c)
add_executable(mysmb_jumpspring_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/jumpspring_chain_smoke.c core/jumpspring.c)
add_executable(mysmb_vine_setup_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/vine_setup_smoke.c)
add_executable(mysmb_vine_actor_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/vine_actor_smoke.c core/vine.c)
add_executable(mysmb_hammer_chain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/hammer_chain_smoke.c core/hammer.c)
target_include_directories(mysmb_hammer_chain_smoke PRIVATE . kvm)
add_executable(mysmb_coin_allocation_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/coin_allocation_smoke.c core/coin.c)
target_include_directories(mysmb_coin_allocation_smoke PRIVATE . kvm)
add_executable(mysmb_misc_lifetime_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/misc_lifetime_smoke.c core/misc.c)
target_include_directories(mysmb_misc_lifetime_smoke PRIVATE . kvm)
add_executable(mysmb_score_hud_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/score_hud_smoke.c core/score.c)
target_include_directories(mysmb_score_hud_smoke PRIVATE . kvm)
add_executable(mysmb_power_up_init_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/power_up_init_smoke.c core/power_up_init.c)
target_include_directories(mysmb_power_up_init_smoke PRIVATE . kvm)
add_executable(mysmb_power_up_actor_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/power_up_actor_smoke.c core/power_up.c)
target_include_directories(mysmb_power_up_actor_smoke PRIVATE . kvm)
add_executable(mysmb_block_head_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_head_smoke.c core/blocks/head.c)
target_include_directories(mysmb_block_head_smoke PRIVATE . kvm)
add_executable(mysmb_block_bump_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_bump_smoke.c core/blocks/bump.c)
target_include_directories(mysmb_block_bump_smoke PRIVATE . kvm)
add_executable(mysmb_block_chunks_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_chunks_smoke.c core/blocks/chunks.c)
target_include_directories(mysmb_block_chunks_smoke PRIVATE . kvm)
add_executable(mysmb_block_lifetime_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_lifetime_smoke.c core/blocks/lifetime.c)
target_include_directories(mysmb_block_lifetime_smoke PRIVATE . kvm)
add_executable(mysmb_block_replacement_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_replacement_smoke.c core/blocks/replacement.c)
target_include_directories(mysmb_block_replacement_smoke PRIVATE . kvm)
add_executable(mysmb_horizontal_movement_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/horizontal_movement_smoke.c)
target_link_libraries(mysmb_horizontal_movement_smoke PRIVATE mysmb_core)
add_executable(mysmb_horizontal_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/horizontal_snapshot_check.c)
target_link_libraries(mysmb_horizontal_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_vertical_adapters_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/vertical_adapters_smoke.c)
target_link_libraries(mysmb_vertical_adapters_smoke PRIVATE mysmb_core)
add_executable(mysmb_gravity_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/gravity_smoke.c)
target_link_libraries(mysmb_gravity_smoke PRIVATE mysmb_core)
add_executable(mysmb_gravity_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/gravity_snapshot_check.c)
target_link_libraries(mysmb_gravity_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_power_up_init_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/power_up_init_snapshot_check.c core/power_up_init.c)
target_include_directories(mysmb_power_up_init_snapshot_check PRIVATE . kvm)
add_executable(mysmb_power_up_init_dispatch_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/power_up_init_dispatch_smoke.c)
target_link_libraries(mysmb_power_up_init_dispatch_smoke PRIVATE mysmb_core)

target_include_directories(mysmb_vine_actor_smoke PRIVATE . kvm)
target_link_libraries(mysmb_vine_setup_smoke PRIVATE mysmb_core)
target_include_directories(mysmb_vine_setup_smoke PRIVATE . kvm)
add_executable(mysmb_vine_setup_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/vine_setup_snapshot_check.c)
target_link_libraries(mysmb_vine_setup_snapshot_check PRIVATE mysmb_core)
target_include_directories(mysmb_vine_setup_snapshot_check PRIVATE . kvm)
target_include_directories(mysmb_jumpspring_chain_smoke PRIVATE . kvm)
target_include_directories(mysmb_timer_chain_smoke PRIVATE . kvm)
target_include_directories(mysmb_player_animation_friction_chain_smoke PRIVATE . kvm)
target_link_libraries(mysmb_player_animation_friction_chain_smoke PRIVATE mysmb_core)
add_executable(mysmb_player_animation_friction_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_animation_friction_snapshot_check.c)
target_include_directories(mysmb_player_animation_friction_snapshot_check PRIVATE . kvm)
target_link_libraries(mysmb_player_animation_friction_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_player_physics_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_physics_snapshot_check.c)
target_include_directories(mysmb_player_physics_snapshot_check PRIVATE . kvm)
target_link_libraries(mysmb_player_physics_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_player_climbing_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_climbing_snapshot_check.c)
target_include_directories(mysmb_player_climbing_snapshot_check PRIVATE . kvm)
target_link_libraries(mysmb_player_climbing_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_player_modes_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_modes_snapshot_check.c core/player_modes.c)
target_compile_definitions(mysmb_player_modes_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
target_include_directories(mysmb_player_modes_caller_check PRIVATE . kvm)
target_include_directories(mysmb_player_transition_chain_smoke PRIVATE . kvm)
add_executable(mysmb_player_transition_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_transition_caller_check.c core/player_transition.c)
target_include_directories(mysmb_player_transition_caller_check PRIVATE . kvm)
add_executable(mysmb_player_control_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_control_caller_check.c core/player_control.c)
target_include_directories(mysmb_player_control_caller_check PRIVATE . kvm)
target_include_directories(mysmb_player_entry_chain_smoke PRIVATE . kvm)
add_executable(mysmb_entrance_caller_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/entrance_caller_snapshot_check.c core/entry.c)
target_include_directories(mysmb_entrance_caller_snapshot_check PRIVATE . kvm)
target_include_directories(mysmb_player_scroll_chain_smoke PRIVATE . kvm)
add_executable(mysmb_scroll_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/scroll_snapshot_check.c core/scroll.c core/oam/object_position.c)
target_include_directories(mysmb_scroll_snapshot_check PRIVATE . kvm)
target_link_libraries(mysmb_player_route_smoke PRIVATE mysmb_core)
add_executable(mysmb_player_friction_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_friction_smoke.c)
target_link_libraries(mysmb_player_friction_smoke PRIVATE mysmb_core)
add_executable(mysmb_player_horizontal_carry_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_horizontal_carry_smoke.c)
target_link_libraries(mysmb_player_horizontal_carry_smoke PRIVATE mysmb_core)
add_executable(mysmb_player_bounding_box_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_bounding_box_smoke.c)
target_link_libraries(mysmb_player_bounding_box_smoke PRIVATE mysmb_core)
add_executable(mysmb_bounding_box_clip_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/bounding_box_clip_smoke.c)
target_link_libraries(mysmb_bounding_box_clip_smoke PRIVATE mysmb_core)
add_executable(mysmb_bounding_box_core_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/bounding_box_core_smoke.c)
target_link_libraries(mysmb_bounding_box_core_smoke PRIVATE mysmb_core)
add_executable(mysmb_geometry_core_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/geometry_core_smoke.c)
target_link_libraries(mysmb_geometry_core_smoke PRIVATE mysmb_core)
add_executable(mysmb_geometry_actual_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/geometry_actual_check.c)
target_link_libraries(mysmb_geometry_actual_check PRIVATE mysmb_core)
add_executable(mysmb_enemy_block_query_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_block_query_smoke.c)
target_link_libraries(mysmb_enemy_block_query_smoke PRIVATE mysmb_core)
add_executable(mysmb_enemy_terrain_state_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_terrain_state_smoke.c)
target_link_libraries(mysmb_enemy_terrain_state_smoke PRIVATE mysmb_core)
add_executable(mysmb_world_movement_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/world_movement_smoke.c)
target_link_libraries(mysmb_world_movement_smoke PRIVATE mysmb_core)
add_executable(mysmb_hazard_collision_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/hazard_collision_smoke.c)
target_link_libraries(mysmb_hazard_collision_smoke PRIVATE mysmb_core)
add_executable(mysmb_bullet_bill_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/bullet_bill_smoke.c)
target_link_libraries(mysmb_bullet_bill_smoke PRIVATE mysmb_core)
add_executable(mysmb_paratroopa_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/paratroopa_smoke.c)
target_link_libraries(mysmb_paratroopa_smoke PRIVATE mysmb_core)
add_executable(mysmb_lakitu_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/lakitu_smoke.c)
target_link_libraries(mysmb_lakitu_smoke PRIVATE mysmb_core)
add_executable(mysmb_hammer_bro_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/hammer_bro_smoke.c)
target_link_libraries(mysmb_hammer_bro_smoke PRIVATE mysmb_core)
add_executable(mysmb_hammer_bro_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/hammer_bro_oam_smoke.c)
target_link_libraries(mysmb_hammer_bro_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_enemy_collision_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_collision_smoke.c)
target_link_libraries(mysmb_enemy_collision_smoke PRIVATE mysmb_core)
add_executable(mysmb_flying_cheep_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/flying_cheep_smoke.c)
target_link_libraries(mysmb_flying_cheep_smoke PRIVATE mysmb_core)
add_executable(mysmb_firebar_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/firebar_smoke.c)
target_link_libraries(mysmb_firebar_smoke PRIVATE mysmb_core)
add_executable(mysmb_bowser_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/bowser_smoke.c)
target_link_libraries(mysmb_bowser_smoke PRIVATE mysmb_core)
add_executable(mysmb_vine_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/vine_oam_smoke.c)
target_link_libraries(mysmb_vine_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_six_sprite_stacker_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/six_sprite_stacker_smoke.c)
target_link_libraries(mysmb_six_sprite_stacker_smoke PRIVATE mysmb_core)
add_executable(mysmb_sprite_dump_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/sprite_dump_smoke.c)
target_link_libraries(mysmb_sprite_dump_smoke PRIVATE mysmb_core)
add_executable(mysmb_flagpole_gfx_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/flagpole_gfx_smoke.c)
target_link_libraries(mysmb_flagpole_gfx_smoke PRIVATE mysmb_core)
add_executable(mysmb_bowser_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/bowser_oam_smoke.c)
target_link_libraries(mysmb_bowser_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_bowser_flame_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/bowser_flame_oam_smoke.c)
target_link_libraries(mysmb_bowser_flame_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_endgame_objects_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/endgame_objects_smoke.c)
target_link_libraries(mysmb_endgame_objects_smoke PRIVATE mysmb_core)
add_executable(mysmb_flagpole_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/flagpole_oam_smoke.c)
target_link_libraries(mysmb_flagpole_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_retainer_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/retainer_oam_smoke.c)
target_link_libraries(mysmb_retainer_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_jumpspring_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/jumpspring_oam_smoke.c)
target_link_libraries(mysmb_jumpspring_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_jumpspring_graphics_snapshot_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/jumpspring_graphics_snapshot_check.c)
target_link_libraries(mysmb_jumpspring_graphics_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_bowser_half_graphics_snapshot_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/bowser_half_graphics_snapshot_check.c)
target_link_libraries(mysmb_bowser_half_graphics_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_normal_enemy_graphics_snapshot_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/normal_enemy_graphics_snapshot_check.c)
target_link_libraries(mysmb_normal_enemy_graphics_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_oam_helper_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/oam_helper_route_check.c)
target_link_libraries(mysmb_oam_helper_route_check PRIVATE mysmb_core)
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_executable(mysmb_oam_helper_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/oam_helper_route_check.c)
    target_compile_definitions(mysmb_oam_helper_caller_check PRIVATE MYSMB_OAM_HELPER_CHILD_CHECK=1)
    target_link_libraries(mysmb_oam_helper_caller_check PRIVATE mysmb_core)
    target_link_options(mysmb_oam_helper_caller_check PRIVATE
        "-Wl,--wrap=mysmb_oam_move_enemy_column_offscreen"
        "-Wl,--wrap=mysmb_oam_move_enemy_row_offscreen"
        "-Wl,--wrap=mysmb_objects_erase_enemy"
        "-Wl,--wrap=mysmb_oam_move_column_offscreen"
        "-Wl,--wrap=mysmb_oam_dump_two_sprites"
        "-Wl,--wrap=mysmb_oam_dump_four_sprites"
        "-Wl,--wrap=mysmb_oam_check_block_left_column"
        "-Wl,--wrap=mysmb_oam_draw_one_sprite_row"
        "-Wl,--wrap=mysmb_oam_draw_sprite_object"
        "-Wl,--wrap=mysmb_oam_dump_six_sprites"
        "-Wl,--wrap=mysmb_oam_draw_firebar"
        "-Wl,--wrap=mysmb_oam_draw_fireworks_explosion"
        "-Wl,--wrap=mysmb_oam_dump_three_sprites")
endif()

add_executable(mysmb_enemy_graphics_output_route_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/enemy_graphics_output_route_check.c)
target_link_libraries(mysmb_enemy_graphics_output_route_check PRIVATE mysmb_core)
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_executable(mysmb_enemy_graphics_output_caller_check
        ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/enemy_graphics_output_route_check.c)
    target_compile_definitions(mysmb_enemy_graphics_output_caller_check PRIVATE
        MYSMB_ENEMY_GFX_CHILD_CHECK=1)
    target_link_libraries(mysmb_enemy_graphics_output_caller_check PRIVATE mysmb_core)
    target_link_options(mysmb_enemy_graphics_output_caller_check PRIVATE
        "-Wl,--wrap=mysmb_oam_draw_one_sprite_row")
endif()
add_executable(mysmb_retainer_graphics_snapshot_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/retainer_graphics_snapshot_check.c)
target_link_libraries(mysmb_retainer_graphics_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_platform_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/platform_smoke.c)
target_link_libraries(mysmb_platform_smoke PRIVATE mysmb_core)
add_executable(mysmb_mode_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/mode_smoke.c)
target_link_libraries(mysmb_mode_smoke PRIVATE mysmb_core)
add_executable(mysmb_oper_mode_dispatch_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oper_mode_dispatch_smoke.c)
target_link_libraries(mysmb_oper_mode_dispatch_smoke PRIVATE mysmb_core)
add_executable(mysmb_title_demo_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/title_demo_smoke.c)
target_link_libraries(mysmb_title_demo_smoke PRIVATE mysmb_core)
add_executable(mysmb_screen_status_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/screen_status_smoke.c)
target_link_libraries(mysmb_screen_status_smoke PRIVATE mysmb_core)
add_executable(mysmb_audio_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/audio_smoke.c)
target_link_libraries(mysmb_audio_smoke PRIVATE mysmb_core)
add_executable(mysmb_sound_entry_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/sound_entry_snapshot_check.c)
target_link_libraries(mysmb_sound_entry_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_sound_helper_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/sound_helper_snapshot_check.c)
target_link_libraries(mysmb_sound_helper_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_sound_command_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/sound_command_route_check.c)
target_link_libraries(mysmb_sound_command_route_check PRIVATE mysmb_core)
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_sources(mysmb_sound_command_route_check PRIVATE
        ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/offscreen_child_observer.c)
    target_compile_definitions(mysmb_sound_command_route_check PRIVATE
        MYSMB_TEST_OFFSCREEN_OBSERVER)
    target_link_options(mysmb_sound_command_route_check PRIVATE
        "-Wl,--wrap=mysmb_oam_get_enemy_offscreen_bits")
endif()
add_executable(mysmb_sound_square1_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/sound_square1_snapshot_check.c)
target_link_libraries(mysmb_sound_square1_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_sound_square1_music_snapshot_check
               ${CMAKE_SOURCE_DIR}/test/app-mario/core/sound_square1_music_snapshot_check.c)
target_link_libraries(mysmb_sound_square1_music_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_sound_triangle_music_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/sound_triangle_music_snapshot_check.c)
target_link_libraries(mysmb_sound_triangle_music_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_sound_noise_music_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/sound_noise_music_snapshot_check.c)
target_link_libraries(mysmb_sound_noise_music_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_sound_square2_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/sound_square2_snapshot_check.c)
target_link_libraries(mysmb_sound_square2_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_sound_square2_dispatch_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/sound_square2_dispatch_smoke.c)
target_link_libraries(mysmb_sound_square2_dispatch_smoke PRIVATE mysmb_core)
add_executable(mysmb_sound_noise_dispatch_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/sound_noise_dispatch_smoke.c)
target_link_libraries(mysmb_sound_noise_dispatch_smoke PRIVATE mysmb_core)
add_executable(mysmb_sound_noise_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/sound_noise_snapshot_check.c)
target_link_libraries(mysmb_sound_noise_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_sound_noise_envelope_table_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/sound_noise_envelope_table_check.c)
target_link_libraries(mysmb_sound_noise_envelope_table_check PRIVATE mysmb_core)
add_executable(mysmb_sound_music_handoff_snapshot_check
               ${CMAKE_SOURCE_DIR}/test/app-mario/core/sound_music_handoff_snapshot_check.c)
target_link_libraries(mysmb_sound_music_handoff_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_sound_music_selection_snapshot_check
               ${CMAKE_SOURCE_DIR}/test/app-mario/core/sound_music_selection_snapshot_check.c)
target_link_libraries(mysmb_sound_music_selection_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_sound_music_header_table_check
               ${CMAKE_SOURCE_DIR}/test/app-mario/core/sound_music_header_table_check.c)
target_link_libraries(mysmb_sound_music_header_table_check PRIVATE mysmb_core)
add_executable(mysmb_sound_music_stream_record_check
               ${CMAKE_SOURCE_DIR}/test/app-mario/core/sound_music_stream_record_check.c)
target_link_libraries(mysmb_sound_music_stream_record_check PRIVATE mysmb_core)
add_executable(mysmb_sound_music_lookup_table_check
               ${CMAKE_SOURCE_DIR}/test/app-mario/core/sound_music_lookup_table_check.c)
target_link_libraries(mysmb_sound_music_lookup_table_check PRIVATE mysmb_core)
add_executable(mysmb_sound_square2_music_snapshot_check
               ${CMAKE_SOURCE_DIR}/test/app-mario/core/sound_square2_music_snapshot_check.c)
target_link_libraries(mysmb_sound_square2_music_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_end_to_end_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/end_to_end_smoke.c)
target_link_libraries(mysmb_end_to_end_smoke PRIVATE mysmb_core)
add_executable(mysmb_ppu_rows_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/ppu/ppu_rows_smoke.c ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/ppu/ppu_frame_reference.c)
target_link_libraries(mysmb_ppu_rows_smoke PRIVATE mysmb_ppu_frame mysmb_io_planar_frame)
add_test(NAME mysmb.ppu-rows-smoke COMMAND mysmb_ppu_rows_smoke)
add_executable(mysmb_ppu_frame_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/ppu/ppu_frame_smoke.c)
target_link_libraries(mysmb_ppu_frame_smoke PRIVATE mysmb_core mysmb_ppu_frame)
add_executable(mysmb_render_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/ppu/render_smoke.c)
target_link_libraries(mysmb_render_smoke PRIVATE mysmb_core)
add_executable(mysmb_frame_snapshot_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/ppu/frame_snapshot_smoke.c)
target_link_libraries(mysmb_frame_snapshot_smoke PRIVATE mysmb_core)
add_executable(mysmb_sprite_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/sprite_oam_smoke.c)
target_link_libraries(mysmb_sprite_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_player_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/player_oam_smoke.c)
target_link_libraries(mysmb_player_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_floatey_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/floatey_oam_smoke.c)
target_link_libraries(mysmb_floatey_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_misc_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/misc_oam_smoke.c)
target_link_libraries(mysmb_misc_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_jumping_coin_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/jumping_coin_snapshot_check.c)
target_link_libraries(mysmb_jumping_coin_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_rom_object_array_layout_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/rom_object_array_layout_smoke.c)
target_link_libraries(mysmb_rom_object_array_layout_smoke PRIVATE mysmb_core)
add_executable(mysmb_fireball_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/fireball_oam_smoke.c)
target_link_libraries(mysmb_fireball_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_power_up_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/power_up_oam_smoke.c)
target_link_libraries(mysmb_power_up_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_block_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/block_oam_smoke.c)
target_link_libraries(mysmb_block_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_block_graphics_snapshot_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/block_graphics_snapshot_check.c)
target_link_libraries(mysmb_block_graphics_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_goomba_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/goomba_oam_smoke.c)
target_link_libraries(mysmb_goomba_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_normal_enemy_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/normal_enemy_oam_smoke.c)
target_link_libraries(mysmb_normal_enemy_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_bubble_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/bubble_oam_smoke.c)
target_link_libraries(mysmb_bubble_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_small_platform_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/small_platform_oam_smoke.c)
target_link_libraries(mysmb_small_platform_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_large_platform_graphics_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/large_platform_graphics_smoke.c)
target_link_libraries(mysmb_large_platform_graphics_smoke PRIVATE mysmb_core)
add_executable(mysmb_large_platform_snapshot_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/large_platform_snapshot_check.c)
target_link_libraries(mysmb_large_platform_snapshot_check PRIVATE mysmb_core)
add_executable(mysmb_piranha_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/piranha_oam_smoke.c)
target_link_libraries(mysmb_piranha_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_cheep_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/cheep_oam_smoke.c)
target_link_libraries(mysmb_cheep_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_bloober_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/bloober_oam_smoke.c)
target_link_libraries(mysmb_bloober_oam_smoke PRIVATE mysmb_core)
add_executable(mysmb_podoboo_oam_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/podoboo_oam_smoke.c)
target_link_libraries(mysmb_podoboo_oam_smoke PRIVATE mysmb_core)
add_library(mysmb_text_elements STATIC kvm/text/elements.c
    kvm/text/compact_elements.c kvm/text/layout.c
    kvm/text/actor_scene.c
    kvm/text/background_scene.c
    kvm/text/caption_scene.c
    kvm/text/scene.c)
target_include_directories(mysmb_text_elements PUBLIC . kvm)
add_executable(mysmb_text_compact_scene_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/text/text_compact_scene_smoke.c)
target_link_libraries(mysmb_text_compact_scene_smoke PRIVATE mysmb_text_elements)
add_test(NAME mysmb.text-compact-scene-smoke COMMAND mysmb_text_compact_scene_smoke)
target_link_libraries(mysmb_text_elements PUBLIC mysmb_core mysmb_io_support)
target_link_libraries(mysmb_text_observation_smoke PRIVATE mysmb_text_elements)
add_executable(mysmb_text_elements_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/text/text_elements_smoke.c)
target_link_libraries(mysmb_text_elements_smoke PRIVATE mysmb_text_elements)
add_test(NAME mysmb.text-elements-smoke COMMAND mysmb_text_elements_smoke)
add_executable(mysmb_text_actor_scene_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/text/text_actor_scene_smoke.c)
target_link_libraries(mysmb_text_actor_scene_smoke PRIVATE mysmb_text_elements)
add_test(NAME mysmb.text-actor-scene-smoke COMMAND mysmb_text_actor_scene_smoke)
add_executable(mysmb_text_background_scene_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/text/text_background_scene_smoke.c)
target_link_libraries(mysmb_text_background_scene_smoke PRIVATE mysmb_text_elements)
add_test(NAME mysmb.text-background-scene-smoke COMMAND mysmb_text_background_scene_smoke)
add_executable(mysmb_text_caption_scene_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/text/text_caption_scene_smoke.c)
target_link_libraries(mysmb_text_caption_scene_smoke PRIVATE mysmb_text_elements)
add_test(NAME mysmb.text-caption-scene-smoke COMMAND mysmb_text_caption_scene_smoke)

add_library(mysmb_validate_text_frame STATIC ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/ppu/validate/text_frame.c)
target_include_directories(mysmb_validate_text_frame PUBLIC . kvm)
target_link_libraries(mysmb_validate_text_frame PUBLIC mysmb_ppu_frame)
add_executable(mysmb_text_frame_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/text/text_frame_smoke.c)
target_link_libraries(mysmb_text_frame_smoke PRIVATE mysmb_validate_text_frame)
add_library(mysmb_io_planar_frame STATIC kvm/io/planar_frame.c)
target_include_directories(mysmb_io_planar_frame PUBLIC . kvm)
target_link_libraries(mysmb_io_planar_frame PUBLIC mysmb_io_support)
add_executable(mysmb_vga_frame_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/ppu/vga_frame_smoke.c)
target_link_libraries(mysmb_vga_frame_smoke PRIVATE mysmb_io_planar_frame)
add_executable(mysmb_ppu_byte_background_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/ppu/ppu_byte_background_smoke.c)
target_link_libraries(mysmb_ppu_byte_background_smoke PRIVATE mysmb_ppu_frame)
add_executable(mysmb_ppu_background_damage_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/ppu/ppu_background_damage_smoke.c)
target_link_libraries(mysmb_ppu_background_damage_smoke PRIVATE mysmb_ppu_frame)
add_executable(mysmb_ppu_background_tile_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/ppu/ppu_background_tile_smoke.c)
target_link_libraries(mysmb_ppu_background_tile_smoke PRIVATE mysmb_ppu_frame)
add_executable(mysmb_ppu_sprite_overlay_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/ppu/ppu_sprite_overlay_smoke.c)
target_link_libraries(mysmb_ppu_sprite_overlay_smoke PRIVATE mysmb_ppu_frame)
add_library(mysmb_dos16_retained_background STATIC kvm/platform/dos16/retained_background.c)
target_include_directories(mysmb_dos16_retained_background PUBLIC . kvm)
target_link_libraries(mysmb_dos16_retained_background PUBLIC mysmb_ppu_frame)
add_executable(mysmb_dos16_retained_background_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/dos16/dos16_retained_background_smoke.c)
target_link_libraries(mysmb_dos16_retained_background_smoke PRIVATE mysmb_dos16_retained_background)
add_executable(mysmb_dos16_retained_apply_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/dos16/dos16_retained_apply_smoke.c)
target_link_libraries(mysmb_dos16_retained_apply_smoke PRIVATE mysmb_dos16_retained_background)
add_executable(mysmb_dos16_retained_overlay_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/dos16/dos16_retained_overlay_smoke.c)
target_link_libraries(mysmb_dos16_retained_overlay_smoke PRIVATE mysmb_dos16_retained_background)
add_library(mysmb_dos16_compact_vga_layout STATIC kvm/platform/dos16/compact_vga_layout.c)
target_include_directories(mysmb_dos16_compact_vga_layout PUBLIC . kvm)
target_link_libraries(mysmb_dos16_compact_vga_layout PUBLIC mygames_kvm)
add_executable(mysmb_dos16_compact_vga_layout_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/dos16/dos16_compact_vga_layout_smoke.c)
target_link_libraries(mysmb_dos16_compact_vga_layout_smoke PRIVATE mysmb_dos16_compact_vga_layout)
add_executable(mysmb_dos16_compact_overlay_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/dos16/dos16_compact_overlay_smoke.c)
target_link_libraries(mysmb_dos16_compact_overlay_smoke PRIVATE
    mysmb_dos16_retained_background mysmb_dos16_compact_vga_layout)
add_library(mysmb_dos16_ram_compositor STATIC kvm/platform/dos16/ram_compositor.c)
target_include_directories(mysmb_dos16_ram_compositor PUBLIC . kvm)
target_link_libraries(mysmb_dos16_ram_compositor PUBLIC mysmb_ppu_frame)
add_library(mysmb_integer_audio STATIC kvm/io/audio_renderer.c)
target_include_directories(mysmb_integer_audio PUBLIC . kvm)
target_link_libraries(mysmb_integer_audio PUBLIC mygames_kvm)
add_executable(mysmb_integer_audio_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/io/integer_audio_smoke.c)
target_link_libraries(mysmb_integer_audio_smoke PRIVATE mysmb_integer_audio)
add_test(NAME mysmb.integer-audio-smoke COMMAND mysmb_integer_audio_smoke)
add_executable(mysmb_dos16_ram_compositor_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/dos16/dos16_ram_compositor_smoke.c)
target_link_libraries(mysmb_dos16_ram_compositor_smoke PRIVATE mysmb_dos16_ram_compositor)
add_library(mysmb_dos16_root STATIC kvm/platform/dos16/dos16_root.c kvm/platform/dos16/keyboard.c kvm/platform/dos16/slot_copy.c)
target_include_directories(mysmb_dos16_root PUBLIC . kvm)
target_link_libraries(mysmb_dos16_root PUBLIC mysmb_core mysmb_game_io mysmb_io_support mysmb_game_snapshot mysmb_text_elements mygames_dos16)
add_executable(mysmb_dos16_root_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/dos16/dos16_root_smoke.c)
target_link_libraries(mysmb_dos16_root_smoke PRIVATE mysmb_dos16_root)
add_executable(mysmb_dos_snapshot_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/app/dos_snapshot_smoke.c
    kvm/io/file/snapshot_files.c kvm/io/file/executable_path.c
    )
target_link_libraries(mysmb_dos_snapshot_smoke PRIVATE mysmb_dos16_root mygames_win32)

# A separately named input for the later OpenNT large-model DOS build.  It has
# no DOS platform code and must stay free of host headers.
add_library(mysmb_dos16_core OBJECT ${MYSMB_CORE_SOURCES})
target_include_directories(mysmb_dos16_core PRIVATE . kvm)

if(MYSMB_OPENNT_CL16)
    # cl16 keeps intermediate paths in a fixed-size buffer.  Keep its owned
    # output beneath the repository build tree, but independent of the
    # width-specific Ninja directory so modern long build paths do not make
    # the historical compiler fail before issuing a diagnostic.
    set(MYSMB_OPENNT_OUTPUT_DIR "${CMAKE_BINARY_DIR}/dos16-opennt")
    add_custom_target(mysmb_opennt16_core
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/boot.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/frame_root.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/title_modes.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/terminal_modes.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/game.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/audio.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/area.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/enemy/stream.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/enemy/init.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
                        -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/enemy/core.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/enemy/movement.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/enemy/normal.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/enemy/background.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/enemy/side_collision.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/enemy/frenzy.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/player.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/scroll.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/entry.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/player_control.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/player_transition.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/player_modes.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/player_end_level.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/player_movement.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/objects.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/bridge.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/oam/bullet_bill_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/oam/hammer_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/oam/firebar_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/oam/vine_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/enemy_bounds.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/oam/power_up_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/oam/object_position.c core/oam/block_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/oam/goomba_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/fireball/bubble.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/oam/piranha_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/oam/cheep_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/oam/bloober_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/oam/podoboo_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
            COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
                "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
                -Compiler "${MYSMB_OPENNT_CL16}"
                -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
                -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/oam/normal_enemy_gfx.c"
                -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/oam/spiny_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/oam/hammer_bro_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/oam/bowser_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/endgame_objects.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/core/oam/small_platform_gfx.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/kvm/io/planar_frame.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_SOURCE_DIR}/test/app-mario/kvm/ppu/validate/text_frame.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/kvm/platform/dos16/dos16_root.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        VERBATIM
    )
    if(MYSMB_DOS_RUNTIME_DIR)
        get_filename_component(MYSMB_OPENNT_LINK16 "${MYSMB_OPENNT_CL16}" DIRECTORY)
        set(MYSMB_OPENNT_LINK16 "${MYSMB_OPENNT_LINK16}/link16.exe")
        add_custom_target(mysmb_opennt16_dos
            COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
                "${CMAKE_SOURCE_DIR}/tools/Build-OpenNt16Dos.ps1"
                -Compiler "${MYSMB_OPENNT_CL16}"
                -Linker "${MYSMB_OPENNT_LINK16}"
                -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}"
                -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}/dos"
                -RuntimeDirectory "${MYSMB_DOS_RUNTIME_DIR}"
                -SourceRoot "${CMAKE_CURRENT_SOURCE_DIR}"
                -RomPath "${MYSMB_ROM_PATH}"
            VERBATIM
        )
    endif()
endif()

if(WIN32)
    add_executable(mysmb_presentation_performance
        ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/dos16/presentation_performance.c ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/ppu/ppu_frame_reference.c)
    target_link_libraries(mysmb_presentation_performance PRIVATE
        mysmb_game_snapshot mysmb_game_io mysmb_text_elements mysmb_io_planar_frame)
    add_test(NAME mysmb.presentation-performance COMMAND mysmb_presentation_performance)
    add_executable(mysmb_win32_keyboard_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/win32/win32_keyboard_smoke.c)
    target_link_libraries(mysmb_win32_keyboard_smoke PRIVATE
        mygames_win32 mysmb_app_input_mapping)
    add_test(NAME mysmb.win32-keyboard-smoke COMMAND mysmb_win32_keyboard_smoke)
    if(MYSMB_WIN32_ARCH STREQUAL "host")
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(MYSMB_WIN32_ARCH "x64")
        else()
            set(MYSMB_WIN32_ARCH "x86")
        endif()
    endif()

    # Console subsystem makes interactive CMD wait for the same process.
    # The root detaches the initial console for non-shell graphical launches.
    add_executable(mysmb_win32 kvm/platform/win32/main_win32.c
        kvm/platform/win32/audio_output.c
        kvm/platform/win32/audio_renderer.c
        kvm/platform/win32/focus_pause.c
        )
    target_link_libraries(mysmb_win32 PRIVATE mygames_win32 mysmb_app_input_mapping mysmb_core mysmb_game_io mysmb_io_support user32 gdi32 winmm)
    target_sources(mysmb_win32 PRIVATE kvm/io/file/snapshot_files.c
         kvm/platform/win32/audio_snapshot.c
        kvm/platform/win32/audio_snapshot_real.c)
    target_link_libraries(mysmb_win32 PRIVATE mysmb_game_snapshot mysmb_io_snapshot mysmb_text_elements)
    add_executable(mysmb_win32_snapshot_binding_smoke
        ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/win32/win32_snapshot_binding_smoke.c kvm/platform/win32/audio_output.c
        kvm/platform/win32/audio_renderer.c kvm/platform/win32/focus_pause.c
        kvm/io/file/snapshot_files.c
        kvm/platform/win32/audio_snapshot.c kvm/platform/win32/audio_snapshot_real.c)
    add_executable(mysmb_win32_text_switch_smoke WIN32
        ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/win32/win32_text_switch_smoke.c kvm/platform/win32/audio_output.c
        kvm/platform/win32/audio_renderer.c kvm/platform/win32/focus_pause.c
        kvm/io/file/snapshot_files.c
         kvm/platform/win32/audio_snapshot.c
        kvm/platform/win32/audio_snapshot_real.c)
    target_link_libraries(mysmb_win32_text_switch_smoke PRIVATE
        mygames_win32 mysmb_app_input_mapping mysmb_game_snapshot mysmb_game_io mysmb_text_elements mysmb_io_snapshot user32 gdi32 winmm)
    target_link_libraries(mysmb_win32_snapshot_binding_smoke PRIVATE
        mygames_win32 mysmb_app_input_mapping mysmb_game_snapshot mysmb_game_io mysmb_io_support mysmb_text_elements user32 gdi32 winmm)
    add_test(NAME mysmb.win32-audio-exit COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/win32/test_audio_exit.py
        $<TARGET_FILE:mysmb_win32_snapshot_binding_smoke>)
    add_executable(mysmb_win32_focus_pause_smoke
        ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/win32/win32_focus_pause_smoke.c
        kvm/platform/win32/focus_pause.c)
    target_include_directories(mysmb_win32_focus_pause_smoke PRIVATE . kvm)
    target_link_libraries(mysmb_win32_focus_pause_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.win32-focus-pause-smoke
        COMMAND mysmb_win32_focus_pause_smoke)
    add_executable(mysmb_win32_audio_renderer_smoke
        ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/win32/win32_audio_renderer_smoke.c
        kvm/platform/win32/audio_renderer.c)
    target_include_directories(mysmb_win32_audio_renderer_smoke PRIVATE . kvm)
    add_test(NAME mysmb.win32-audio-renderer-smoke
        COMMAND mysmb_win32_audio_renderer_smoke)
    add_executable(mysmb_win32_audio_output_smoke
        ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/win32/win32_audio_output_smoke.c
        kvm/platform/win32/audio_output.c
        kvm/platform/win32/audio_renderer.c)
    target_include_directories(mysmb_win32_audio_output_smoke PRIVATE . kvm)
    target_link_libraries(mysmb_win32_audio_output_smoke PRIVATE mygames_win32 winmm)
    add_test(NAME mysmb.win32-audio-output-smoke
        COMMAND mysmb_win32_audio_output_smoke)
    set_tests_properties(mysmb.win32-audio-output-smoke PROPERTIES
        SKIP_RETURN_CODE 77)
    add_custom_target(mysmb_win32_audio_host_integration
        COMMAND $<TARGET_FILE:mysmb_win32_audio_output_smoke> --device
        DEPENDS mysmb_win32_audio_output_smoke USES_TERMINAL VERBATIM)
    set_target_properties(mysmb_win32 PROPERTIES
        OUTPUT_NAME "mysmb-win32-${MYSMB_WIN32_ARCH}"
    )
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU" AND CMAKE_STRIP)
        # Remove the non-loaded COFF symbol tail only. Preserve every mapped
        # section (including CRT debug sections),RVAs and resource bytes.
        add_custom_command(TARGET mysmb_win32 POST_BUILD
            COMMAND "${CMAKE_STRIP}" --strip-all "--keep-section=.debug*"
                "$<TARGET_FILE:mysmb_win32>" VERBATIM)
    endif()
endif()

enable_testing()
add_test(NAME mysmb.core-smoke COMMAND mysmb_core_smoke)
add_test(NAME mysmb.ram-cold-start-smoke COMMAND mysmb_ram_cold_start_smoke)
add_test(NAME mysmb.reset-root-smoke COMMAND mysmb_reset_root_smoke)
add_test(NAME mysmb.boot-nmi-boundary-smoke COMMAND mysmb_boot_nmi_boundary_smoke)
add_test(NAME mysmb.nmi-parent-integration COMMAND mysmb_nmi_parent_integration_check)
add_test(NAME mysmb.name-table-init-smoke COMMAND mysmb_name_table_init_smoke)
add_test(NAME mysmb.vram-address-table-smoke COMMAND mysmb_vram_address_table_smoke)
add_test(NAME mysmb.joypad-vram-chain-smoke COMMAND mysmb_joypad_vram_chain_smoke)
add_test(NAME mysmb.pseudorandom-smoke COMMAND mysmb_pseudorandom_smoke)
add_test(NAME mysmb.timer-root-smoke COMMAND mysmb_timer_root_smoke)
add_test(NAME mysmb.pause-root-smoke COMMAND mysmb_pause_root_smoke)
add_test(NAME mysmb.sprite-root-smoke COMMAND mysmb_sprite_root_smoke)
add_executable(mysmb_sprite_shuffle_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/sprite_shuffle_smoke.c)
target_link_libraries(mysmb_sprite_shuffle_smoke PRIVATE mysmb_core)
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
add_test(NAME mysmb.jumpspring-origin-offscreen COMMAND mysmb_jumpspring_origin_offscreen_smoke)
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
add_test(NAME mysmb.screen-parser-output-chain
    COMMAND mysmb_screen_parser_output_chain_check)
add_test(NAME mysmb.kill-enemies-shared-primitive
    COMMAND mysmb_kill_enemies_shared_primitive_check)
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
add_test(NAME mysmb.sound-square2-dispatch-smoke COMMAND mysmb_sound_square2_dispatch_smoke)
add_test(NAME mysmb.sound-noise-dispatch-smoke COMMAND mysmb_sound_noise_dispatch_smoke)
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
add_test(NAME mysmb.ppu-byte-background-smoke COMMAND mysmb_ppu_byte_background_smoke)
add_test(NAME mysmb.ppu-background-damage-smoke COMMAND mysmb_ppu_background_damage_smoke)
add_test(NAME mysmb.ppu-background-tile-smoke COMMAND mysmb_ppu_background_tile_smoke)
add_test(NAME mysmb.ppu-sprite-overlay-smoke COMMAND mysmb_ppu_sprite_overlay_smoke)
add_test(NAME mysmb.dos16-retained-background-smoke COMMAND mysmb_dos16_retained_background_smoke)
add_test(NAME mysmb.dos16-retained-apply-smoke COMMAND mysmb_dos16_retained_apply_smoke)
add_test(NAME mysmb.dos16-retained-overlay-smoke COMMAND mysmb_dos16_retained_overlay_smoke)
add_test(NAME mysmb.dos16-compact-vga-layout-smoke COMMAND mysmb_dos16_compact_vga_layout_smoke)
add_test(NAME mysmb.dos16-compact-overlay-smoke COMMAND mysmb_dos16_compact_overlay_smoke)
add_test(NAME mysmb.dos16-ram-compositor-smoke COMMAND mysmb_dos16_ram_compositor_smoke)
add_test(NAME mysmb.dos16-root-smoke COMMAND mysmb_dos16_root_smoke)

find_package(Python3 COMPONENTS Interpreter REQUIRED)

if(WIN32)
    # These fixtures exercise a real borrowed/owned Console and a private
    # desktop. They are deliberately not ordinary CTest cases: a CTest worker
    # may itself be a ConPTY without the classic Console contract under test.
    # Keep the lifecycle route named and invocable so it cannot silently become
    # a build-only executable.
    add_custom_target(mysmb_win32_host_integration
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "${CMAKE_BINARY_DIR}/win32-host-integration"
        COMMAND ${Python3_EXECUTABLE}
            "${CMAKE_SOURCE_DIR}/tools/Verify-Win32StartupConsole.py"
            --product "$<TARGET_FILE:mysmb_win32>"
            --policy "$<TARGET_FILE:mygames_win32_launch_policy_smoke>"
            --switch "$<TARGET_FILE:mysmb_win32_text_switch_smoke>"
            --parent "$<TARGET_FILE:mygames_win32_parent_console_smoke>"
            --devices "$<TARGET_FILE:mygames_win32_devices_probe>"
            --output "${CMAKE_BINARY_DIR}/win32-host-integration"
        DEPENDS mysmb_win32 mygames_win32_launch_policy_smoke
            mysmb_win32_text_switch_smoke mygames_win32_parent_console_smoke mygames_win32_devices_probe
        USES_TERMINAL
        VERBATIM)
endif()

add_test(NAME mysmb.rom-codegen
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/test/app-mario/core/test_smb_rom_codegen.py)
add_test(NAME mysmb.asm-index
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/test/app-mario/core/test_smb_asm_index.py)
add_test(NAME mysmb.enemy-data-bindings-synthetic
         COMMAND ${Python3_EXECUTABLE} -B ${CMAKE_SOURCE_DIR}/test/app-mario/core/test_smb_enemy_data_audit.py)
add_test(NAME mysmb.boot-codegen
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/test/app-mario/core/test_smb_boot_codegen.py)
add_test(NAME mysmb.title-codegen
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/test/app-mario/core/test_smb_title_codegen.py)
add_test(NAME mysmb.platform-purity
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/app/test_platform_purity.py)
add_test(NAME mysmb.static-analysis
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/test/app-mario/core/test_smb_static_analysis.py)
add_test(NAME mysmb.listing-layout
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/test/app-mario/core/test_smb_listing_layout.py)
add_test(NAME mysmb.listing-reconcile
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/test/app-mario/core/test_smb_listing_reconcile.py)
add_test(NAME mysmb.complete-analysis
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/test/app-mario/core/test_smb_complete_analysis.py)

if(MYSMB_ROM_PATH)
    add_test(NAME mysmb.music-header-table
        COMMAND mysmb_sound_music_header_table_check "${MYSMB_ROM_PATH}")
    add_test(NAME mysmb.music-stream-records
        COMMAND mysmb_sound_music_stream_record_check "${MYSMB_ROM_PATH}")
    add_test(NAME mysmb.music-lookup-tables
        COMMAND mysmb_sound_music_lookup_table_check "${MYSMB_ROM_PATH}")
    add_test(NAME mysmb.noise-envelope-tables
        COMMAND mysmb_sound_noise_envelope_table_check "${MYSMB_ROM_PATH}")

    set(MYSMB_LOCAL_ROM_DIR "${CMAKE_BINARY_DIR}/generated/smb1-local")
    add_custom_command(
        OUTPUT
            "${MYSMB_LOCAL_ROM_DIR}/smb1_local_rom.h"
            "${MYSMB_LOCAL_ROM_DIR}/smb1_local_rom.c"
            "${MYSMB_LOCAL_ROM_DIR}/smb1_local_map.txt"
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/tools/smb_rom_codegen.py
            --rom "${MYSMB_ROM_PATH}" --output "${MYSMB_LOCAL_ROM_DIR}"
        DEPENDS ${CMAKE_SOURCE_DIR}/tools/smb_rom_codegen.py "${MYSMB_ROM_PATH}"
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
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/tools/smb_boot_codegen.py
            --rom "${MYSMB_ROM_PATH}" --output "${MYSMB_STATIC_BOOT_DIR}"
        DEPENDS ${CMAKE_SOURCE_DIR}/tools/smb_boot_codegen.py
                ${CMAKE_SOURCE_DIR}/tools/smb_rom_codegen.py
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
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/tools/smb_title_codegen.py
            --rom "${MYSMB_ROM_PATH}" --output "${MYSMB_LOCAL_TITLE_DIR}"
        DEPENDS ${CMAKE_SOURCE_DIR}/tools/smb_title_codegen.py
                ${CMAKE_SOURCE_DIR}/tools/smb_rom_codegen.py
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
    add_executable(mysmb_snapshot_continuation_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/app/snapshot_continuation_smoke.c
        kvm/platform/win32/audio_renderer.c kvm/platform/win32/audio_snapshot.c
        kvm/platform/win32/audio_snapshot_real.c $<TARGET_OBJECTS:mysmb_local_rom_data>
        $<TARGET_OBJECTS:mysmb_local_title_data>)
    target_include_directories(mysmb_snapshot_continuation_smoke PRIVATE
        "${MYSMB_LOCAL_ROM_DIR}" "${MYSMB_LOCAL_TITLE_DIR}")
    target_link_libraries(mysmb_snapshot_continuation_smoke PRIVATE mysmb_game_snapshot mysmb_game_io)
    target_sources(mysmb_text_observation_smoke PRIVATE
        $<TARGET_OBJECTS:mysmb_local_rom_data> $<TARGET_OBJECTS:mysmb_local_title_data>)
    target_include_directories(mysmb_text_observation_smoke PRIVATE
        "${MYSMB_LOCAL_ROM_DIR}" "${MYSMB_LOCAL_TITLE_DIR}")
    target_compile_definitions(mysmb_text_observation_smoke PRIVATE MYSMB_LOCAL_TITLE=1)
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/snapshot-continuation-test")
    add_test(NAME mysmb.snapshot-continuation-smoke COMMAND mysmb_snapshot_continuation_smoke
        capture "${CMAKE_BINARY_DIR}/snapshot-continuation-test/mysmb.sav"
        "${CMAKE_BINARY_DIR}/snapshot-continuation-test/receipt.txt")
    if(TARGET mysmb_win32)
        target_sources(mysmb_dos_snapshot_smoke PRIVATE
            $<TARGET_OBJECTS:mysmb_local_rom_data> $<TARGET_OBJECTS:mysmb_local_title_data>)
        target_include_directories(mysmb_dos_snapshot_smoke PRIVATE
            "${MYSMB_LOCAL_ROM_DIR}" "${MYSMB_LOCAL_TITLE_DIR}")
        target_compile_definitions(mysmb_dos_snapshot_smoke PRIVATE MYSMB_LOCAL_TITLE=1)
        file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/dos-snapshot-test")
        add_test(NAME mysmb.dos-snapshot-smoke COMMAND mysmb_dos_snapshot_smoke
            "${CMAKE_BINARY_DIR}/dos-snapshot-test")
        target_sources(mysmb_win32 PRIVATE
            $<TARGET_OBJECTS:mysmb_local_rom_data>
            $<TARGET_OBJECTS:mysmb_local_title_data>
        )
        target_include_directories(mysmb_win32 PRIVATE
            "${MYSMB_LOCAL_ROM_DIR}" "${MYSMB_LOCAL_TITLE_DIR}"
        )
        target_compile_definitions(mysmb_win32 PRIVATE MYSMB_LOCAL_TITLE=1)
        target_sources(mysmb_win32_snapshot_binding_smoke PRIVATE
            $<TARGET_OBJECTS:mysmb_local_rom_data> $<TARGET_OBJECTS:mysmb_local_title_data>)
        target_include_directories(mysmb_win32_snapshot_binding_smoke PRIVATE
            "${MYSMB_LOCAL_ROM_DIR}" "${MYSMB_LOCAL_TITLE_DIR}")
        target_compile_definitions(mysmb_win32_snapshot_binding_smoke PRIVATE MYSMB_LOCAL_TITLE=1)
        file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/snapshot-binding-test")
        add_test(NAME mysmb.win32-snapshot-binding-smoke COMMAND mysmb_win32_snapshot_binding_smoke
            "${CMAKE_BINARY_DIR}/snapshot-binding-test")
        target_sources(mysmb_win32_text_switch_smoke PRIVATE
            $<TARGET_OBJECTS:mysmb_local_rom_data> $<TARGET_OBJECTS:mysmb_local_title_data>)
        target_include_directories(mysmb_win32_text_switch_smoke PRIVATE
            "${MYSMB_LOCAL_ROM_DIR}" "${MYSMB_LOCAL_TITLE_DIR}")
        target_compile_definitions(mysmb_win32_text_switch_smoke PRIVATE MYSMB_LOCAL_TITLE=1)
        add_test(NAME mysmb.win32-${MYSMB_WIN32_ARCH}-self-test
                 COMMAND $<TARGET_FILE:mysmb_win32> --self-test)
        target_sources(mysmb_presentation_performance PRIVATE
            $<TARGET_OBJECTS:mysmb_local_rom_data> $<TARGET_OBJECTS:mysmb_local_title_data>)
        target_include_directories(mysmb_presentation_performance PRIVATE
            "${MYSMB_LOCAL_ROM_DIR}" "${MYSMB_LOCAL_TITLE_DIR}")
        target_compile_definitions(mysmb_presentation_performance PRIVATE MYSMB_LOCAL_TITLE=1)
    endif()
    add_executable(mysmb_local_title_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/local_title_smoke.c
        $<TARGET_OBJECTS:mysmb_local_title_data>)
    target_include_directories(mysmb_local_title_smoke PRIVATE . kvm "${MYSMB_LOCAL_TITLE_DIR}")
    target_link_libraries(mysmb_local_title_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.local-title-smoke COMMAND mysmb_local_title_smoke)
    add_executable(mysmb_local_title_oracle ${CMAKE_SOURCE_DIR}/test/app-mario/core/local_title_oracle.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>
        $<TARGET_OBJECTS:mysmb_local_title_data>)
    target_include_directories(mysmb_local_title_oracle PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}" "${MYSMB_LOCAL_TITLE_DIR}")
    target_link_libraries(mysmb_local_title_oracle PRIVATE mysmb_core)
    add_test(NAME mysmb.local-title-oracle COMMAND mysmb_local_title_oracle)
    add_executable(mysmb_local_title_bootstrap_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/local_title_bootstrap_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>
        $<TARGET_OBJECTS:mysmb_local_title_data>)
    target_include_directories(mysmb_local_title_bootstrap_smoke PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}" "${MYSMB_LOCAL_TITLE_DIR}")
    target_link_libraries(mysmb_local_title_bootstrap_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.local-title-bootstrap-smoke
             COMMAND mysmb_local_title_bootstrap_smoke)
    add_executable(mysmb_local_area_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/local_area_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_local_area_smoke PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_local_area_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.local-area-smoke COMMAND mysmb_local_area_smoke)
    add_executable(mysmb_enemy_stream_local_consumer_check
        ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_stream_local_consumer_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_enemy_stream_local_consumer_check PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_enemy_stream_local_consumer_check PRIVATE mysmb_core)
    add_test(NAME mysmb.enemy-stream-local-consumer
        COMMAND mysmb_enemy_stream_local_consumer_check)
    add_executable(mysmb_area_output_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_output_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_area_output_smoke PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_area_output_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.area-output-smoke COMMAND mysmb_area_output_smoke)
    add_executable(mysmb_area_data_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_data_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_area_data_smoke PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_area_data_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.area-data-smoke COMMAND mysmb_area_data_smoke)
    add_executable(mysmb_area_parser_data_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_parser_data_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_area_parser_data_smoke PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_area_parser_data_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.area-parser-data-smoke COMMAND mysmb_area_parser_data_smoke)
    add_executable(mysmb_area_pointer_header_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/area_pointer_header_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_area_pointer_header_smoke PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_area_pointer_header_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.area-pointer-header-smoke COMMAND mysmb_area_pointer_header_smoke)
    add_executable(mysmb_castle_scene_stream_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/castle_scene_stream_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_castle_scene_stream_smoke PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_castle_scene_stream_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.castle-scene-streams COMMAND mysmb_castle_scene_stream_smoke)
    add_executable(mysmb_ground_scene_stream_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/ground_scene_stream_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_ground_scene_stream_smoke PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_ground_scene_stream_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.ground-scene-streams COMMAND mysmb_ground_scene_stream_smoke)
    add_executable(mysmb_underground_scene_stream_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/underground_scene_stream_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_underground_scene_stream_smoke PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_underground_scene_stream_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.underground-scene-streams COMMAND mysmb_underground_scene_stream_smoke)
    add_executable(mysmb_water_scene_stream_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/water_scene_stream_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_water_scene_stream_smoke PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_water_scene_stream_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.water-scene-streams COMMAND mysmb_water_scene_stream_smoke)
    add_executable(mysmb_block_graphics_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/block_graphics_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_graphics_smoke PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_block_graphics_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.block-graphics-smoke COMMAND mysmb_block_graphics_smoke)
    add_executable(mysmb_collision_regression_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/collision_regression_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_collision_regression_smoke PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_collision_regression_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.collision-regression-smoke
             COMMAND mysmb_collision_regression_smoke)
    add_executable(mysmb_enemy_background_entry_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_background_entry_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_enemy_background_entry_smoke PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_enemy_background_entry_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.enemy-background-entry COMMAND mysmb_enemy_background_entry_smoke)
    add_executable(mysmb_normal_movement_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/normal_movement_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_normal_movement_snapshot_check PRIVATE . kvm)
    target_link_libraries(mysmb_normal_movement_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_entrance_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/entrance_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_entrance_snapshot_check PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_entrance_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_player_control_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_control_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_player_control_snapshot_check PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_player_control_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_player_transition_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_transition_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_player_transition_snapshot_check PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_player_transition_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_player_modes_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_modes_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_player_modes_snapshot_check PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_player_modes_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_player_end_level_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_end_level_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_player_end_level_snapshot_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_player_end_level_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_player_end_level_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_end_level_snapshot_check.c
        core/player_end_level.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_player_end_level_caller_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_player_end_level_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_fireball_dispatch_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/fireball/fireball_dispatch_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_fireball_dispatch_snapshot_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_fireball_dispatch_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_fireball_dispatch_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/fireball/fireball_dispatch_snapshot_check.c
        core/fireball/fireball_spawn.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_fireball_dispatch_caller_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_fireball_dispatch_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_fireball_core_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/fireball/fireball_core_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_fireball_core_snapshot_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_fireball_core_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_fireball_core_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/fireball/fireball_core_snapshot_check.c
        core/fireball/fireball_core.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_fireball_core_caller_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_fireball_core_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_block_buffer_player_actual_check
        ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_buffer_player_actual_check.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_buffer_player_actual_check PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_block_buffer_player_actual_check PRIVATE mysmb_core)
    add_executable(mysmb_timer_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/timer_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_timer_snapshot_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_timer_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_timer_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/timer_snapshot_check.c
        core/timer.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_timer_caller_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_timer_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_jumpspring_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/jumpspring_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_jumpspring_snapshot_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_jumpspring_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_jumpspring_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/jumpspring_snapshot_check.c
        core/jumpspring.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_jumpspring_caller_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_jumpspring_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_vine_actor_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/vine_actor_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_vine_actor_snapshot_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_vine_actor_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_vine_actor_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/vine_actor_snapshot_check.c
        core/vine.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_vine_actor_caller_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_vine_actor_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_hammer_chain_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/hammer_chain_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_hammer_chain_snapshot_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_hammer_chain_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_hammer_graphics_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/hammer_graphics_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_hammer_graphics_snapshot_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_hammer_graphics_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_hammer_chain_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/hammer_chain_snapshot_check.c
        core/hammer.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_hammer_chain_caller_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_hammer_chain_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_coin_allocation_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/coin_allocation_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_coin_allocation_snapshot_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_coin_allocation_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_coin_allocation_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/coin_allocation_snapshot_check.c
        core/coin.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_coin_allocation_caller_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_coin_allocation_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_misc_lifetime_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/misc_lifetime_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_misc_lifetime_snapshot_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_misc_lifetime_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_misc_lifetime_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/misc_lifetime_snapshot_check.c
        core/misc.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_misc_lifetime_caller_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_misc_lifetime_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_score_hud_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/score_hud_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_score_hud_snapshot_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_score_hud_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_score_hud_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/score_hud_snapshot_check.c
        core/score.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_score_hud_caller_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_score_hud_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_power_up_actor_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/power_up_actor_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_power_up_actor_snapshot_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_power_up_actor_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_power_up_actor_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/power_up_actor_snapshot_check.c
        core/power_up.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_power_up_actor_caller_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_power_up_actor_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_power_up_actor_child_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/power_up_actor_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_power_up_actor_child_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_power_up_actor_child_check PRIVATE MYSMB_CHILD_DIAGNOSTIC=1)
    target_link_libraries(mysmb_power_up_actor_child_check PRIVATE mysmb_core)
    add_executable(mysmb_block_head_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_head_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_head_snapshot_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_block_head_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_block_head_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_head_snapshot_check.c
        core/blocks/head.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_head_caller_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_head_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_block_head_child_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_head_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_head_child_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_head_child_check PRIVATE MYSMB_CHILD_DIAGNOSTIC=1)
    target_link_libraries(mysmb_block_head_child_check PRIVATE mysmb_core)
    add_executable(mysmb_block_bump_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_bump_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_bump_snapshot_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_block_bump_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_block_bump_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_bump_snapshot_check.c
        core/blocks/bump.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_bump_caller_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_bump_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_block_bump_child_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_bump_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_bump_child_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_bump_child_check PRIVATE MYSMB_CHILD_DIAGNOSTIC=1)
    target_link_libraries(mysmb_block_bump_child_check PRIVATE mysmb_core)
    add_executable(mysmb_block_chunks_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_chunks_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_chunks_snapshot_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_block_chunks_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_block_chunks_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_chunks_snapshot_check.c
        core/blocks/chunks.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_chunks_caller_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_chunks_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_block_chunks_child_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_chunks_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_chunks_child_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_chunks_child_check PRIVATE MYSMB_CHILD_DIAGNOSTIC=1)
    target_link_libraries(mysmb_block_chunks_child_check PRIVATE mysmb_core)
    add_executable(mysmb_block_lifetime_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_lifetime_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_lifetime_snapshot_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_block_lifetime_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_block_lifetime_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_lifetime_snapshot_check.c
        core/blocks/lifetime.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_lifetime_caller_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_lifetime_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_block_lifetime_child_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_lifetime_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_lifetime_child_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_lifetime_child_check PRIVATE MYSMB_CHILD_DIAGNOSTIC=1)
    target_link_libraries(mysmb_block_lifetime_child_check PRIVATE mysmb_core)
    add_executable(mysmb_block_replacement_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_replacement_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_replacement_snapshot_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_block_replacement_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_block_replacement_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_replacement_snapshot_check.c
        core/blocks/replacement.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_replacement_caller_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_replacement_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_block_replacement_child_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_replacement_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_block_replacement_child_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_block_replacement_child_check PRIVATE MYSMB_CHILD_DIAGNOSTIC=1)
    target_link_libraries(mysmb_block_replacement_child_check PRIVATE mysmb_core)
    add_executable(mysmb_player_movement_snapshot_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_movement_snapshot_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_player_movement_snapshot_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_player_movement_snapshot_check PRIVATE mysmb_core)
    add_executable(mysmb_player_movement_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_movement_snapshot_check.c
        core/player_movement.c $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_player_movement_caller_check PRIVATE . kvm "${MYSMB_LOCAL_ROM_DIR}")
    target_compile_definitions(mysmb_player_movement_caller_check PRIVATE MYSMB_CALLER_CHECK=1)
    add_executable(mysmb_palette_rotation_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/io/palette_rotation_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_palette_rotation_smoke PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_palette_rotation_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.palette-rotation-smoke COMMAND mysmb_palette_rotation_smoke)
    add_executable(mysmb_local_palette_timing_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/local_palette_timing_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_local_palette_timing_smoke PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_local_palette_timing_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.local-palette-timing-smoke
             COMMAND mysmb_local_palette_timing_smoke)
    add_executable(mysmb_local_victory_message_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/local_victory_message_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_local_victory_message_smoke PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_local_victory_message_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.local-victory-message-smoke
             COMMAND mysmb_local_victory_message_smoke)
    add_executable(mysmb_local_death_music_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/local_death_music_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_local_death_music_smoke PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_local_death_music_smoke PRIVATE mysmb_core)
    add_test(NAME mysmb.local-death-music-smoke
             COMMAND mysmb_local_death_music_smoke)
    if(TARGET mysmb_win32)
        add_executable(mysmb_win32_death_audio_smoke
            ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/win32/win32_death_audio_smoke.c
            kvm/platform/win32/audio_renderer.c
            $<TARGET_OBJECTS:mysmb_local_rom_data>)
        target_include_directories(mysmb_win32_death_audio_smoke PRIVATE . kvm
            "${MYSMB_LOCAL_ROM_DIR}")
        target_link_libraries(mysmb_win32_death_audio_smoke PRIVATE mysmb_core mysmb_game_io)
        add_test(NAME mysmb.win32-death-audio-smoke
            COMMAND mysmb_win32_death_audio_smoke)
    endif()
    add_executable(mysmb_dos16_death_audio_smoke
        ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/dos16/dos16_death_audio_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_dos16_death_audio_smoke PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_dos16_death_audio_smoke PRIVATE
        mysmb_core mysmb_game_io mysmb_integer_audio)
    add_test(NAME mysmb.dos16-death-audio-smoke
        COMMAND mysmb_dos16_death_audio_smoke)
    add_executable(mysmb_dos16_gameplay_audio_smoke
        ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/dos16/dos16_gameplay_audio_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_dos16_gameplay_audio_smoke PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_dos16_gameplay_audio_smoke PRIVATE
        mysmb_core mysmb_game_io mysmb_integer_audio)
    add_test(NAME mysmb.dos16-gameplay-audio-smoke
        COMMAND mysmb_dos16_gameplay_audio_smoke)
    add_executable(mysmb_local_frame_summary ${CMAKE_SOURCE_DIR}/test/app-mario/core/local_frame_summary.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>
        $<TARGET_OBJECTS:mysmb_local_title_data>)
    target_include_directories(mysmb_local_frame_summary PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}" "${MYSMB_LOCAL_TITLE_DIR}")
    target_link_libraries(mysmb_local_frame_summary PRIVATE mysmb_core)
    add_executable(mysmb_local_frame_recorder ${CMAKE_SOURCE_DIR}/test/app-mario/core/local_frame_recorder.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>
        $<TARGET_OBJECTS:mysmb_local_title_data>)
    target_include_directories(mysmb_local_frame_recorder PRIVATE . kvm
        "${MYSMB_LOCAL_ROM_DIR}" "${MYSMB_LOCAL_TITLE_DIR}")
    target_link_libraries(mysmb_local_frame_recorder PRIVATE mysmb_core)

    if(MYSMB_ASM_PATH)
        add_custom_command(
            OUTPUT "${MYSMB_LOCAL_ROM_DIR}/smb1_symbols.txt"
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/tools/smb_asm_index.py
                --rom "${MYSMB_ROM_PATH}" --asm "${MYSMB_ASM_PATH}"
                --output "${MYSMB_LOCAL_ROM_DIR}/smb1_symbols.txt"
            DEPENDS
                ${CMAKE_SOURCE_DIR}/tools/smb_asm_index.py
                ${CMAKE_SOURCE_DIR}/tools/smb_rom_codegen.py
                "${MYSMB_ROM_PATH}" "${MYSMB_ASM_PATH}"
            VERBATIM
        )
        add_custom_target(mysmb_local_symbols DEPENDS
            "${MYSMB_LOCAL_ROM_DIR}/smb1_symbols.txt"
        )
        add_dependencies(mysmb_local_symbols mysmb_local_rom)
    endif()
endif()

add_executable(mysmb_fireball_enemy_scan_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/fireball_enemy_scan_smoke.c core/world/fireball_enemy.c)
target_include_directories(mysmb_fireball_enemy_scan_smoke PRIVATE . kvm)
add_test(NAME mysmb.fireball-enemy-scan COMMAND mysmb_fireball_enemy_scan_smoke)

add_executable(mysmb_fireball_hit_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/fireball_hit_smoke.c core/world/fireball_hit.c)
target_include_directories(mysmb_fireball_hit_smoke PRIVATE . kvm)
add_test(NAME mysmb.fireball-hit-chain COMMAND mysmb_fireball_hit_smoke)

add_executable(mysmb_hammer_contact_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/hammer_contact_smoke.c core/world/hammer_collision.c)
target_include_directories(mysmb_hammer_contact_smoke PRIVATE . kvm)
add_test(NAME mysmb.hammer-contact-chain COMMAND mysmb_hammer_contact_smoke)

add_executable(mysmb_powerup_pickup_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/powerup_pickup_smoke.c core/world/powerup_collision.c)
target_include_directories(mysmb_powerup_pickup_smoke PRIVATE . kvm)
add_test(NAME mysmb.powerup-pickup-chain COMMAND mysmb_powerup_pickup_smoke)
add_executable(mysmb_player_enemy_contact_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_enemy_contact_smoke.c core/world/player_enemy_collision.c)
target_include_directories(mysmb_player_enemy_contact_smoke PRIVATE . kvm)
add_test(NAME mysmb.player-enemy-contact-chain COMMAND mysmb_player_enemy_contact_smoke)
add_executable(mysmb_enemy_pair_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_pair_smoke.c core/world/enemy_collision.c)
target_include_directories(mysmb_enemy_pair_smoke PRIVATE . kvm)
add_test(NAME mysmb.enemy-pair-chain COMMAND mysmb_enemy_pair_smoke)
add_executable(mysmb_platform_collision_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/platform_collision_smoke.c core/enemy/platform_collision.c)
target_include_directories(mysmb_platform_collision_smoke PRIVATE . kvm)
add_test(NAME mysmb.platform-collision-chain COMMAND mysmb_platform_collision_smoke)
add_executable(mysmb_platform_position_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/platform_position_smoke.c core/enemy/platform_position.c)
target_include_directories(mysmb_platform_position_smoke PRIVATE . kvm)
add_test(NAME mysmb.platform-positioning-chain COMMAND mysmb_platform_position_smoke)
add_executable(mysmb_collision_preflight_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/collision_preflight_smoke.c)
target_link_libraries(mysmb_collision_preflight_smoke PRIVATE mysmb_core)
add_test(NAME mysmb.collision-preflight-chain COMMAND mysmb_collision_preflight_smoke)
add_executable(mysmb_player_terrain_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/player_terrain_smoke.c core/player/terrain.c)
target_include_directories(mysmb_player_terrain_smoke PRIVATE . kvm)
add_test(NAME mysmb.player-terrain-chain COMMAND mysmb_player_terrain_smoke)

add_executable(mysmb_terrain_metatile_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/terrain_metatile_smoke.c core/player/terrain_metatiles.c)
target_include_directories(mysmb_terrain_metatile_smoke PRIVATE . kvm)
add_test(NAME mysmb.terrain-metatile-chain COMMAND mysmb_terrain_metatile_smoke)

add_executable(mysmb_climbing_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/climbing_smoke.c core/player/climbing.c)
target_include_directories(mysmb_climbing_smoke PRIVATE . kvm)
add_test(NAME mysmb.climbing-chain COMMAND mysmb_climbing_smoke)

add_executable(mysmb_hidden_spring_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/hidden_spring_smoke.c core/player/terrain_metatiles.c)
target_include_directories(mysmb_hidden_spring_smoke PRIVATE . kvm)
add_test(NAME mysmb.hidden-spring-chain COMMAND mysmb_hidden_spring_smoke)

add_executable(mysmb_pipe_entry_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/pipe_entry_smoke.c core/player/pipe_entry.c)
target_include_directories(mysmb_pipe_entry_smoke PRIVATE . kvm)
add_test(NAME mysmb.pipe-entry-chain COMMAND mysmb_pipe_entry_smoke)

add_executable(mysmb_impede_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/player/impede_smoke.c core/player/impede.c)
target_include_directories(mysmb_impede_smoke PRIVATE . kvm)
add_test(NAME mysmb.impede-chain COMMAND mysmb_impede_smoke)

add_executable(mysmb_metatile_classification_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/metatile_classification_smoke.c core/world/metatiles.c)
target_include_directories(mysmb_metatile_classification_smoke PRIVATE . kvm)
add_test(NAME mysmb.metatile-classification-chain COMMAND mysmb_metatile_classification_smoke)

add_executable(mysmb_enemy_stun_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_stun_smoke.c)
target_include_directories(mysmb_enemy_stun_smoke PRIVATE . kvm)
target_link_libraries(mysmb_enemy_stun_smoke PRIVATE mysmb_core)
add_test(NAME mysmb.enemy-background-stun-chain COMMAND mysmb_enemy_stun_smoke)

add_executable(mysmb_enemy_landing_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_landing_smoke.c
    core/enemy/background.c)
target_include_directories(mysmb_enemy_landing_smoke PRIVATE . kvm)
add_test(NAME mysmb.enemy-landing-grounded-chain COMMAND mysmb_enemy_landing_smoke)
add_executable(mysmb_enemy_side_jump_hammer_smoke ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_side_jump_hammer_smoke.c)
target_link_libraries(mysmb_enemy_side_jump_hammer_smoke PRIVATE mysmb_core)
add_test(NAME mysmb.enemy-side-jump-hammer-chain COMMAND mysmb_enemy_side_jump_hammer_smoke)
add_executable(mysmb_enemy_side_jump_hammer_actual_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_side_jump_hammer_actual_check.c)
target_link_libraries(mysmb_enemy_side_jump_hammer_actual_check PRIVATE mysmb_core)
add_executable(mysmb_enemy_bump_entry_actual_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_bump_entry_actual_check.c)
target_link_libraries(mysmb_enemy_bump_entry_actual_check PRIVATE mysmb_core)
add_executable(mysmb_enemy_player_difference_actual_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_player_difference_actual_check.c)
target_link_libraries(mysmb_enemy_player_difference_actual_check PRIVATE mysmb_core)
add_executable(mysmb_enemy_landing_actual_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_landing_actual_check.c)
target_link_libraries(mysmb_enemy_landing_actual_check PRIVATE mysmb_core)
add_executable(mysmb_enemy_ground_query_nonsolids_smoke
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_ground_query_nonsolids_smoke.c)
target_link_libraries(mysmb_enemy_ground_query_nonsolids_smoke PRIVATE mysmb_core)
add_test(NAME mysmb.enemy-ground-query-nonsolids-chain
    COMMAND mysmb_enemy_ground_query_nonsolids_smoke)
add_executable(mysmb_enemy_ground_query_actual_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_ground_query_actual_check.c)
target_link_libraries(mysmb_enemy_ground_query_actual_check PRIVATE mysmb_core)
add_executable(mysmb_non_solids_actual_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/non_solids_actual_check.c)
target_link_libraries(mysmb_non_solids_actual_check PRIVATE mysmb_core)
if(TARGET mysmb_local_rom_data)
    add_executable(mysmb_chk_under_enemy_actual_check
        ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/chk_under_enemy_actual_check.c)
    target_link_libraries(mysmb_chk_under_enemy_actual_check PRIVATE mysmb_core)
    add_dependencies(mysmb_chk_under_enemy_actual_check mysmb_local_rom)
    target_include_directories(mysmb_chk_under_enemy_actual_check PRIVATE
        "${MYSMB_LOCAL_ROM_DIR}")
    target_sources(mysmb_chk_under_enemy_actual_check PRIVATE
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
endif()
add_executable(mysmb_fireball_background_actual_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/fireball/fireball_background_actual_check.c)
target_link_libraries(mysmb_fireball_background_actual_check PRIVATE mysmb_core)
add_executable(mysmb_bounding_box_data_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/bounding_box_data_check.c)
target_link_libraries(mysmb_bounding_box_data_check PRIVATE mysmb_core)
add_executable(mysmb_object_box_actual_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/object_box_actual_check.c)
target_link_libraries(mysmb_object_box_actual_check PRIVATE mysmb_core)
add_executable(mysmb_bounding_box_entry_actual_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/bounding_box_entry_actual_check.c)
target_link_libraries(mysmb_bounding_box_entry_actual_check PRIVATE mysmb_core)
add_executable(mysmb_enemy_bounding_box_entry_actual_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_bounding_box_entry_actual_check.c)
target_link_libraries(mysmb_enemy_bounding_box_entry_actual_check PRIVATE mysmb_core)
add_executable(mysmb_platform_bounding_box_entry_actual_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/platform_bounding_box_entry_actual_check.c)
target_link_libraries(mysmb_platform_bounding_box_entry_actual_check PRIVATE mysmb_core)
add_executable(mysmb_misc_bounding_box_entry_actual_check
    ${CMAKE_SOURCE_DIR}/test/app-mario/core/misc_bounding_box_entry_actual_check.c)
target_link_libraries(mysmb_misc_bounding_box_entry_actual_check PRIVATE mysmb_core)
if(MYSMB_ROM_PATH)
    add_executable(mysmb_enemy_jump_actual_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_jump_actual_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_enemy_jump_actual_check PRIVATE "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_enemy_jump_actual_check PRIVATE mysmb_core)
    add_executable(mysmb_hammer_bg_actual_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/hammer_bg_actual_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_hammer_bg_actual_check PRIVATE "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_hammer_bg_actual_check PRIVATE mysmb_core)
    add_executable(mysmb_kill_enemy_above_block_actual_check
        ${CMAKE_SOURCE_DIR}/test/app-mario/core/kill_enemy_above_block_actual_check.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_kill_enemy_above_block_actual_check PRIVATE "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_kill_enemy_above_block_actual_check PRIVATE mysmb_core)
endif()

add_executable(mysmb_bounding_box_core_actual_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/bounding_box_core_actual_check.c)
target_link_libraries(mysmb_bounding_box_core_actual_check PRIVATE mysmb_core)

add_executable(mysmb_bounding_box_clip_actual_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/bounding_box_clip_actual_check.c)
target_link_libraries(mysmb_bounding_box_clip_actual_check PRIVATE mysmb_core)

add_executable(mysmb_geometry_core_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/geometry_core_route_check.c)
target_link_libraries(mysmb_geometry_core_route_check PRIVATE mysmb_core)

add_executable(mysmb_terrain_connection_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/area/terrain_connection_route_check.c)
target_link_libraries(mysmb_terrain_connection_route_check PRIVATE mysmb_core)

add_executable(mysmb_platform_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/platform_integration_route_check.c)
target_link_libraries(mysmb_platform_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_podoboo_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/podoboo_integration_route_check.c)
target_link_libraries(mysmb_podoboo_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_hammer_bro_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/hammer_bro_integration_route_check.c)
target_link_libraries(mysmb_hammer_bro_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_enemy_movement_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_movement_integration_route_check.c)
target_link_libraries(mysmb_enemy_movement_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_x_counter_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/x_counter_integration_route_check.c)
target_link_libraries(mysmb_x_counter_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_bloober_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/bloober_integration_route_check.c)
target_link_libraries(mysmb_bloober_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_firebar_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/firebar_integration_route_check.c)
target_link_libraries(mysmb_firebar_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_flying_cheep_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/flying_cheep_integration_route_check.c)
target_link_libraries(mysmb_flying_cheep_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_lakitu_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/lakitu_integration_route_check.c)
target_link_libraries(mysmb_lakitu_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_bridge_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/bridge_integration_route_check.c)
target_link_libraries(mysmb_bridge_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_bowser_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/bowser_integration_route_check.c)
target_link_libraries(mysmb_bowser_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_bowser_half_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/bowser_half_integration_route_check.c)
target_link_libraries(mysmb_bowser_half_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_flame_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/flame_integration_route_check.c)
target_link_libraries(mysmb_flame_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_fireworks_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/fireworks_integration_route_check.c)
target_link_libraries(mysmb_fireworks_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_end_level_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/end_level_integration_route_check.c)
target_link_libraries(mysmb_end_level_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_piranha_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/piranha_integration_route_check.c)
target_link_libraries(mysmb_piranha_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_platform_movement_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/platform_movement_integration_route_check.c)
target_link_libraries(mysmb_platform_movement_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_fireball_hit_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/world/fireball_hit_integration_route_check.c)
target_link_libraries(mysmb_fireball_hit_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_powerup_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/powerup_integration_route_check.c)
target_link_libraries(mysmb_powerup_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_enemy_terrain_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/enemy/enemy_terrain_integration_route_check.c)
target_link_libraries(mysmb_enemy_terrain_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_jump_hammer_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/jump_hammer_integration_route_check.c)
target_link_libraries(mysmb_jump_hammer_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_block_query_integration_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/blocks/block_query_integration_route_check.c)
target_link_libraries(mysmb_block_query_integration_route_check PRIVATE mysmb_core)

add_executable(mysmb_vine_output_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/vine_output_route_check.c)
target_link_libraries(mysmb_vine_output_route_check PRIVATE mysmb_core)

add_executable(mysmb_hammer_output_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/hammer_output_route_check.c)
target_link_libraries(mysmb_hammer_output_route_check PRIVATE mysmb_core)
add_executable(mysmb_hammer_output_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/hammer_output_route_check.c core/oam/hammer_gfx.c core/observation.c)
target_include_directories(mysmb_hammer_output_caller_check PRIVATE . kvm)
target_compile_definitions(mysmb_hammer_output_caller_check PRIVATE MYSMB_HAMMER_CHILD_CHECK=1)

add_executable(mysmb_flagpole_output_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/flagpole_output_route_check.c)
target_link_libraries(mysmb_flagpole_output_route_check PRIVATE mysmb_core)
add_executable(mysmb_flagpole_output_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/flagpole_output_route_check.c core/oam/flagpole_gfx.c core/observation.c)
target_include_directories(mysmb_flagpole_output_caller_check PRIVATE . kvm)
target_compile_definitions(mysmb_flagpole_output_caller_check PRIVATE MYSMB_FLAGPOLE_CHILD_CHECK=1)

add_executable(mysmb_large_platform_output_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/large_platform_output_route_check.c)
target_link_libraries(mysmb_large_platform_output_route_check PRIVATE mysmb_core)
add_executable(mysmb_large_platform_output_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/large_platform_output_route_check.c core/oam/small_platform_gfx.c core/observation.c)
target_include_directories(mysmb_large_platform_output_caller_check PRIVATE . kvm)
target_compile_definitions(mysmb_large_platform_output_caller_check PRIVATE MYSMB_LARGE_PLATFORM_CHILD_CHECK=1)

add_executable(mysmb_coin_output_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/coin_output_route_check.c)
target_link_libraries(mysmb_coin_output_route_check PRIVATE mysmb_core)
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_executable(mysmb_coin_output_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/coin_output_route_check.c)
    target_link_libraries(mysmb_coin_output_caller_check PRIVATE mysmb_core)
    target_compile_definitions(mysmb_coin_output_caller_check PRIVATE MYSMB_COIN_CHILD_CHECK=1)
    target_link_options(mysmb_coin_output_caller_check PRIVATE "-Wl,--wrap=mysmb_oam_dump_two_sprites")
endif()

add_executable(mysmb_power_up_output_route_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/power_up_output_route_check.c)
target_link_libraries(mysmb_power_up_output_route_check PRIVATE mysmb_core)
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_executable(mysmb_power_up_output_caller_check ${CMAKE_SOURCE_DIR}/test/app-mario/core/oam/power_up_output_route_check.c)
    target_link_libraries(mysmb_power_up_output_caller_check PRIVATE mysmb_core)
    target_compile_definitions(mysmb_power_up_output_caller_check PRIVATE MYSMB_POWER_UP_CHILD_CHECK=1)
    target_link_options(mysmb_power_up_output_caller_check PRIVATE "-Wl,--wrap=mysmb_oam_draw_one_sprite_row" "-Wl,--wrap=mysmb_oam_sprite_object_offscreen_check")
endif()

# Validation projections are absent from every product target.
add_library(mysmb_validation_projections STATIC ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/ppu/validate/render.c
    ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/ppu/validate/frame_snapshot.c ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/ppu/validate/area_projection.c)
target_include_directories(mysmb_validation_projections PUBLIC . kvm)
target_link_libraries(mysmb_validation_projections PUBLIC mysmb_core)
foreach(MYSMB_VALIDATION_CONSUMER mysmb_core_smoke mysmb_render_smoke
        mysmb_frame_snapshot_smoke mysmb_area_data_smoke
        mysmb_local_frame_recorder mysmb_local_frame_summary)
    if(TARGET ${MYSMB_VALIDATION_CONSUMER})
        target_link_libraries(${MYSMB_VALIDATION_CONSUMER} PRIVATE mysmb_validation_projections)
    endif()
endforeach()

add_executable(mysmb_win16_scheduler_smoke
    ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/win16/scheduler_smoke.c
    kvm/platform/win16/scheduler.c)
target_include_directories(mysmb_win16_scheduler_smoke PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/kvm" "${CMAKE_SOURCE_DIR}/src/lib")
set_target_properties(mysmb_win16_scheduler_smoke PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON C_EXTENSIONS OFF)
add_test(NAME mysmb.win16-app-scheduler COMMAND mysmb_win16_scheduler_smoke)

if(TARGET mysmb_local_title_data)
    add_executable(mysmb_win16_window_text_join
        ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/win16/window_text_join.c
        kvm/platform/win16/main_win16.c kvm/platform/win16/scheduler.c
        kvm/io/audio_renderer.c kvm/io/input_latch.c
        kvm/io/file/snapshot_files.c kvm/io/file/executable_path.c
        $<TARGET_OBJECTS:mysmb_local_rom_data> $<TARGET_OBJECTS:mysmb_local_title_data>)
    target_include_directories(mysmb_win16_window_text_join BEFORE PRIVATE
        ${CMAKE_SOURCE_DIR}/test/lib/win16/host_sdk
        ${MYSMB_LOCAL_ROM_DIR} ${MYSMB_LOCAL_TITLE_DIR})
    target_link_libraries(mysmb_win16_window_text_join PRIVATE mysmb_app_input_mapping
        mysmb_game_snapshot mysmb_game_io mysmb_text_elements mysmb_io_snapshot)
    add_test(NAME mysmb.win16-window-text COMMAND mysmb_win16_window_text_join)
endif()

add_executable(mysmb_dos_audio_adapter_smoke
    ${CMAKE_SOURCE_DIR}/test/app-mario/kvm/platform/dos16/dos_audio_adapter_smoke.c
    kvm/platform/dos16/dos_audio_dos.c)
target_include_directories(mysmb_dos_audio_adapter_smoke PRIVATE . kvm ${CMAKE_SOURCE_DIR}/src/lib)
target_link_libraries(mysmb_dos_audio_adapter_smoke PRIVATE mysmb_integer_audio)
add_test(NAME mysmb.dos16-audio-adapter COMMAND mysmb_dos_audio_adapter_smoke)
