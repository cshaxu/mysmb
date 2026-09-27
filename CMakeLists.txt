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

set(MYSMB_GAME_SOURCES src/game/boot.c src/game/frame_root.c src/game/title_modes.c src/game/terminal_modes.c src/game/game.c src/game/audio.c src/game/area.c src/game/status.c src/game/area/block_metatile.c src/game/enemy/stream.c src/game/enemy/init.c src/game/enemy/core.c src/game/enemy/movement.c src/game/enemy/frenzy.c src/game/player.c src/game/objects.c src/game/fireball/fireball_spawn.c src/game/fireball/fireball_core.c src/game/world/movement.c src/game/world/collision.c src/game/bridge.c src/game/oam/bullet_bill_gfx.c src/game/oam/hammer_gfx.c src/game/oam/firebar_gfx.c src/game/oam/vine_gfx.c src/game/enemy_bounds.c src/game/oam/power_up_gfx.c src/game/oam/object_position.c src/game/oam/player_gfx.c src/game/oam/fireball_gfx.c src/game/oam/block_gfx.c src/game/oam/goomba_gfx.c src/game/fireball/bubble.c src/game/oam/piranha_gfx.c src/game/oam/cheep_gfx.c src/game/oam/bloober_gfx.c src/game/oam/podoboo_gfx.c src/game/oam/normal_enemy_gfx.c src/game/oam/spiny_gfx.c src/game/oam/hammer_bro_gfx.c src/game/oam/bowser_gfx.c src/game/oam/bowser_flame_gfx.c src/game/endgame_objects.c src/game/oam/flagpole_gfx.c src/game/oam/small_platform_gfx.c src/game/render.c src/game/ppu_frame.c src/game/frame_snapshot.c)
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
add_executable(mysmb_area_parser_boundary_smoke test/area_parser_boundary_smoke.c)
target_link_libraries(mysmb_area_parser_boundary_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_helper_smoke test/area_helper_smoke.c)
target_link_libraries(mysmb_area_helper_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_hole_underpart_smoke test/area_hole_underpart_smoke.c)
target_link_libraries(mysmb_area_hole_underpart_smoke PRIVATE mysmb_game)
add_executable(mysmb_area_initialize_smoke test/area_initialize_smoke.c)
target_link_libraries(mysmb_area_initialize_smoke PRIVATE mysmb_game)
add_executable(mysmb_enemy_stream_smoke test/enemy_stream_smoke.c)
target_link_libraries(mysmb_enemy_stream_smoke PRIVATE mysmb_game)
add_executable(mysmb_parser_schedule_smoke test/parser_schedule_smoke.c)
target_link_libraries(mysmb_parser_schedule_smoke PRIVATE mysmb_game)
add_executable(mysmb_parser_buffer_commit_smoke test/parser_buffer_commit_smoke.c)
target_link_libraries(mysmb_parser_buffer_commit_smoke PRIVATE mysmb_game)
add_executable(mysmb_player_route_smoke test/player_route_smoke.c)
target_link_libraries(mysmb_player_route_smoke PRIVATE mysmb_game)
add_executable(mysmb_player_friction_smoke test/player_friction_smoke.c)
target_link_libraries(mysmb_player_friction_smoke PRIVATE mysmb_game)
add_executable(mysmb_player_horizontal_carry_smoke test/player_horizontal_carry_smoke.c)
target_link_libraries(mysmb_player_horizontal_carry_smoke PRIVATE mysmb_game)
add_executable(mysmb_player_bounding_box_smoke test/player_bounding_box_smoke.c)
target_link_libraries(mysmb_player_bounding_box_smoke PRIVATE mysmb_game)
add_executable(mysmb_bounding_box_clip_smoke test/bounding_box_clip_smoke.c)
target_link_libraries(mysmb_bounding_box_clip_smoke PRIVATE mysmb_game)
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
add_test(NAME mysmb.area-parser-boundary-smoke COMMAND mysmb_area_parser_boundary_smoke)
add_test(NAME mysmb.area-helper-smoke COMMAND mysmb_area_helper_smoke)
add_test(NAME mysmb.area-hole-underpart-smoke COMMAND mysmb_area_hole_underpart_smoke)
add_test(NAME mysmb.area-initialize-smoke COMMAND mysmb_area_initialize_smoke)
add_test(NAME mysmb.enemy-stream-smoke COMMAND mysmb_enemy_stream_smoke)
add_test(NAME mysmb.parser-schedule-smoke COMMAND mysmb_parser_schedule_smoke)
add_test(NAME mysmb.parser-buffer-commit-smoke COMMAND mysmb_parser_buffer_commit_smoke)
add_test(NAME mysmb.player-route-smoke COMMAND mysmb_player_route_smoke)
add_test(NAME mysmb.player-friction-smoke COMMAND mysmb_player_friction_smoke)
add_test(NAME mysmb.player-horizontal-carry-smoke COMMAND mysmb_player_horizontal_carry_smoke)
add_test(NAME mysmb.player-bounding-box-smoke COMMAND mysmb_player_bounding_box_smoke)
add_test(NAME mysmb.bounding-box-clip-smoke COMMAND mysmb_bounding_box_clip_smoke)
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
