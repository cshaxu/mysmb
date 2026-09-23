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

set(MYSMB_GAME_SOURCES src/game/game.c src/game/area.c src/game/player.c src/game/objects.c)
add_library(mysmb_game STATIC ${MYSMB_GAME_SOURCES})
target_include_directories(mysmb_game PUBLIC src)

if(MSVC)
    target_compile_options(mysmb_game PRIVATE /W4 /WX)
else()
    target_compile_options(mysmb_game PRIVATE -Wall -Wextra -Werror -pedantic)
endif()

add_executable(mysmb_core_smoke test/core_smoke.c)
target_link_libraries(mysmb_core_smoke PRIVATE mysmb_game)
add_executable(mysmb_player_route_smoke test/player_route_smoke.c)
target_link_libraries(mysmb_player_route_smoke PRIVATE mysmb_game)
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
add_executable(mysmb_enemy_collision_smoke test/enemy_collision_smoke.c)
target_link_libraries(mysmb_enemy_collision_smoke PRIVATE mysmb_game)

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
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/game.c"
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
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/player.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        COMMAND powershell.exe -NoProfile -ExecutionPolicy Bypass -File
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/Build-OpenNt16Core.ps1"
            -Compiler "${MYSMB_OPENNT_CL16}"
            -IncludeDirectory "${CMAKE_CURRENT_SOURCE_DIR}/src"
            -Source "${CMAKE_CURRENT_SOURCE_DIR}/src/game/objects.c"
            -OutputDirectory "${MYSMB_OPENNT_OUTPUT_DIR}"
        VERBATIM
    )
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
add_test(NAME mysmb.player-route-smoke COMMAND mysmb_player_route_smoke)
add_test(NAME mysmb.hazard-collision-smoke COMMAND mysmb_hazard_collision_smoke)
add_test(NAME mysmb.bullet-bill-smoke COMMAND mysmb_bullet_bill_smoke)
add_test(NAME mysmb.paratroopa-smoke COMMAND mysmb_paratroopa_smoke)
add_test(NAME mysmb.lakitu-smoke COMMAND mysmb_lakitu_smoke)
add_test(NAME mysmb.hammer-bro-smoke COMMAND mysmb_hammer_bro_smoke)
add_test(NAME mysmb.enemy-collision-smoke COMMAND mysmb_enemy_collision_smoke)

find_package(Python3 COMPONENTS Interpreter REQUIRED)
add_test(NAME mysmb.rom-codegen
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/test_smb_rom_codegen.py)
add_test(NAME mysmb.asm-index
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/test_smb_asm_index.py)
add_test(NAME mysmb.boot-codegen
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/test_smb_boot_codegen.py)
add_test(NAME mysmb.title-codegen
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/test_smb_title_codegen.py)
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
    endif()
    add_executable(mysmb_local_title_smoke test/local_title_smoke.c
        $<TARGET_OBJECTS:mysmb_local_title_data>)
    target_include_directories(mysmb_local_title_smoke PRIVATE src "${MYSMB_LOCAL_TITLE_DIR}")
    target_link_libraries(mysmb_local_title_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.local-title-smoke COMMAND mysmb_local_title_smoke)
    add_executable(mysmb_local_title_oracle test/local_title_oracle.c
        $<TARGET_OBJECTS:mysmb_local_title_data>)
    target_include_directories(mysmb_local_title_oracle PRIVATE src "${MYSMB_LOCAL_TITLE_DIR}")
    target_link_libraries(mysmb_local_title_oracle PRIVATE mysmb_game)
    add_executable(mysmb_local_area_smoke test/local_area_smoke.c
        $<TARGET_OBJECTS:mysmb_local_rom_data>)
    target_include_directories(mysmb_local_area_smoke PRIVATE src "${MYSMB_LOCAL_ROM_DIR}")
    target_link_libraries(mysmb_local_area_smoke PRIVATE mysmb_game)
    add_test(NAME mysmb.local-area-smoke COMMAND mysmb_local_area_smoke)

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
