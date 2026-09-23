cmake_minimum_required(VERSION 3.20)

project(mysmb LANGUAGES C)

# The shared game layer must remain usable by a 16-bit C toolchain.
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(mysmb
    src/main.c
    src/game/game.c
)

target_include_directories(mysmb PRIVATE src)

if(MSVC)
    target_compile_options(mysmb PRIVATE /W4 /WX)
else()
    target_compile_options(mysmb PRIVATE -Wall -Wextra -Werror -pedantic)
endif()
