if(NOT WIN32)
    return()
endif()

add_library(mygames_win32 STATIC
    pcm.c
    pcm_session.c
    file.c
    frame_wait.c
    input.c
    launch.c
    text_console.c
    text_console_geometry.c
    text_console_input.c
    text_console_policy.c
    text_console_presentation.c
    window_geometry.c
    window.c)
target_include_directories(mygames_win32 PUBLIC "${CMAKE_SOURCE_DIR}/src/lib")
target_link_libraries(mygames_win32 PUBLIC mygames_kvm user32 gdi32 winmm)
if(MSVC)
    target_compile_options(mygames_win32 PRIVATE /W4 /WX)
else()
    target_compile_options(mygames_win32 PRIVATE -Wall -Wextra -Werror -pedantic)
endif()

add_executable(mygames_win32_contract_smoke ${CMAKE_SOURCE_DIR}/test/lib/win32/win32_contract_smoke.c)
target_link_libraries(mygames_win32_contract_smoke PRIVATE mygames_win32)
add_test(NAME mygames.win32-contract-smoke COMMAND mygames_win32_contract_smoke)

# Actual window/Console input needs the named private-desktop integration target.
add_executable(mygames_win32_devices_probe ${CMAKE_SOURCE_DIR}/test/lib/win32/host_devices_probe.c)
target_link_libraries(mygames_win32_devices_probe PRIVATE mygames_win32)

add_executable(mygames_win32_pcm_smoke ${CMAKE_SOURCE_DIR}/test/lib/win32/pcm_smoke.c)
target_link_libraries(mygames_win32_pcm_smoke PRIVATE mygames_win32)
add_test(NAME mygames.win32-pcm-lifecycle COMMAND mygames_win32_pcm_smoke)
add_executable(mygames_win32_pcm_session_smoke ${CMAKE_SOURCE_DIR}/test/lib/win32/pcm_session_smoke.c)
target_link_libraries(mygames_win32_pcm_session_smoke PRIVATE mygames_win32)
add_test(NAME mygames.win32-pcm-session COMMAND mygames_win32_pcm_session_smoke)
set_tests_properties(mygames.win32-pcm-session PROPERTIES TIMEOUT 30)

add_executable(mygames_win32_file_smoke ${CMAKE_SOURCE_DIR}/test/lib/win32/file_smoke.c)
target_link_libraries(mygames_win32_file_smoke PRIVATE mygames_win32)
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/file-test")
add_test(NAME mygames.win32-file-replace COMMAND mygames_win32_file_smoke)
set_tests_properties(mygames.win32-file-replace PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/file-test")

# Library-owned fixtures also build when all applications are disabled.
add_executable(mygames_win32_launch_policy_smoke
        ${CMAKE_SOURCE_DIR}/test/lib/win32/win32_launch_policy_smoke.c)
target_link_libraries(mygames_win32_launch_policy_smoke PRIVATE mygames_win32)
add_test(NAME mygames.win32-launch-policy-smoke COMMAND mygames_win32_launch_policy_smoke)
add_executable(mygames_win32_parent_console_smoke ${CMAKE_SOURCE_DIR}/test/lib/win32/win32_parent_console_smoke.c)
target_link_libraries(mygames_win32_parent_console_smoke PRIVATE mygames_win32)
add_executable(mygames_win32_console_capability_smoke ${CMAKE_SOURCE_DIR}/test/lib/win32/win32_console_capability_smoke.c)
target_link_libraries(mygames_win32_console_capability_smoke PRIVATE mygames_win32)
add_test(NAME mygames.win32-console-capability-smoke COMMAND mygames_win32_console_capability_smoke)
add_executable(mygames_win32_frame_wait_smoke ${CMAKE_SOURCE_DIR}/test/lib/win32/win32_frame_wait_smoke.c)
target_link_libraries(mygames_win32_frame_wait_smoke PRIVATE mygames_win32)
add_test(NAME mygames.win32-frame-wait-smoke COMMAND mygames_win32_frame_wait_smoke)

find_package(Python3 COMPONENTS Interpreter REQUIRED)
add_custom_target(mygames_win32_host_integration
    COMMAND ${Python3_EXECUTABLE}
        "${CMAKE_SOURCE_DIR}/tools/Verify-Win32StartupConsole.py"
        --devices-only --devices "$<TARGET_FILE:mygames_win32_devices_probe>"
        --output "${CMAKE_BINARY_DIR}/library-host-integration"
    DEPENDS mygames_win32_devices_probe
    USES_TERMINAL VERBATIM)
