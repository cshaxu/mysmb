if(NOT WIN32)
    return()
endif()

add_library(mygames_win32 STATIC
    src/frame_wait.c
    src/input.c
    src/launch.c
    src/text_console.c
    src/text_console_geometry.c
    src/text_console_input.c
    src/text_console_policy.c
    src/text_console_presentation.c
    src/window_geometry.c)
target_include_directories(mygames_win32 PUBLIC include)
target_link_libraries(mygames_win32 PUBLIC mygames_kvm user32 winmm)
if(MSVC)
    target_compile_options(mygames_win32 PRIVATE /W4 /WX)
else()
    target_compile_options(mygames_win32 PRIVATE -Wall -Wextra -Werror -pedantic)
endif()

add_executable(mygames_win32_contract_smoke test/win32_contract_smoke.c)
target_link_libraries(mygames_win32_contract_smoke PRIVATE mygames_win32)
add_test(NAME mygames.win32-contract-smoke COMMAND mygames_win32_contract_smoke)
