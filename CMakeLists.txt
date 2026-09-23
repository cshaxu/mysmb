cmake_minimum_required(VERSION 3.20)

project(mysmb LANGUAGES C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(MYSMB_WIN32_ARCH "host" CACHE STRING "Win32 target label: x86, x64, or host")
set_property(CACHE MYSMB_WIN32_ARCH PROPERTY STRINGS host x86 x64)
set(MYSMB_ROM_PATH "" CACHE FILEPATH "Owner-local SMB1 NROM image")

add_library(mysmb_game STATIC src/game/game.c)
target_include_directories(mysmb_game PUBLIC src)

if(MSVC)
    target_compile_options(mysmb_game PRIVATE /W4 /WX)
else()
    target_compile_options(mysmb_game PRIVATE -Wall -Wextra -Werror -pedantic)
endif()

add_executable(mysmb_core_smoke test/core_smoke.c)
target_link_libraries(mysmb_core_smoke PRIVATE mysmb_game)

# A separately named input for the later OpenNT large-model DOS build.  It has
# no DOS platform code and must stay free of host headers.
add_library(mysmb_dos16_core OBJECT src/game/game.c)
target_include_directories(mysmb_dos16_core PRIVATE src)

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

find_package(Python3 COMPONENTS Interpreter REQUIRED)
add_test(NAME mysmb.rom-codegen
         COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/test_smb_rom_codegen.py)

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
endif()
