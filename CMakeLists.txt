cmake_minimum_required(VERSION 3.20)

project(mysmb LANGUAGES C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(MYSMB_WIN32_ARCH "host" CACHE STRING "Win32 target label: x86, x64, or host")
set_property(CACHE MYSMB_WIN32_ARCH PROPERTY STRINGS host x86 x64)

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
