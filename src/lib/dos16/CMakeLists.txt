add_library(mygames_dos16 STATIC
    pcm.c
    command_line.c
    file.c
    mouse.c
    raw_keyboard.c
    pit_clock.c
    text_cells.c)
target_include_directories(mygames_dos16 PUBLIC "${CMAKE_SOURCE_DIR}/src/lib")
target_link_libraries(mygames_dos16 PUBLIC mygames_kvm)
if(CMAKE_SYSTEM_NAME STREQUAL "DOS")
    target_sources(mygames_dos16 PRIVATE host.c video_mode.c vga.c mouse_dos.c pcm_dos.c executable_path.c)
endif()

add_executable(mygames_dos16_command_line_smoke ${CMAKE_SOURCE_DIR}/test/lib/dos16/command_line_smoke.c)
target_link_libraries(mygames_dos16_command_line_smoke PRIVATE mygames_dos16)
add_test(NAME mygames.dos16-command-line COMMAND mygames_dos16_command_line_smoke)
if(MSVC)
    target_compile_options(mygames_dos16 PRIVATE /W4 /WX)
else()
    target_compile_options(mygames_dos16 PRIVATE -Wall -Wextra -Werror -pedantic)
endif()

add_executable(mygames_dos16_contract_smoke ${CMAKE_SOURCE_DIR}/test/lib/dos16/dos16_contract_smoke.c)
target_link_libraries(mygames_dos16_contract_smoke PRIVATE mygames_dos16)
add_test(NAME mygames.dos16-contract-smoke COMMAND mygames_dos16_contract_smoke)
add_executable(mygames_dos16_pit_clock_smoke ${CMAKE_SOURCE_DIR}/test/lib/dos16/pit_clock_smoke.c)
target_link_libraries(mygames_dos16_pit_clock_smoke PRIVATE mygames_dos16)
add_test(NAME mygames.dos16-pit-clock-smoke COMMAND mygames_dos16_pit_clock_smoke)

add_executable(mygames_dos16_mouse_smoke ${CMAKE_SOURCE_DIR}/test/lib/dos16/mouse_smoke.c)
target_link_libraries(mygames_dos16_mouse_smoke PRIVATE mygames_dos16)
add_test(NAME mygames.dos16-mouse-lifecycle COMMAND mygames_dos16_mouse_smoke)

add_executable(mygames_dos16_pcm_smoke ${CMAKE_SOURCE_DIR}/test/lib/dos16/pcm_smoke.c)
target_link_libraries(mygames_dos16_pcm_smoke PRIVATE mygames_dos16)
add_test(NAME mygames.dos16-pcm-lifecycle COMMAND mygames_dos16_pcm_smoke)

add_executable(mygames_dos16_file_smoke ${CMAKE_SOURCE_DIR}/test/lib/dos16/file_smoke.c)
target_link_libraries(mygames_dos16_file_smoke PRIVATE mygames_dos16)
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/file-test")
add_test(NAME mygames.dos16-file-replace COMMAND mygames_dos16_file_smoke)
set_tests_properties(mygames.dos16-file-replace PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/file-test")

add_executable(mygames_dos16_pcm_hardware_smoke
    ${CMAKE_SOURCE_DIR}/test/lib/dos16/pcm_hardware_smoke.c pcm_dos.c)
target_include_directories(mygames_dos16_pcm_hardware_smoke BEFORE PRIVATE
    ${CMAKE_SOURCE_DIR}/test/lib/dos16/pcm_sdk ${CMAKE_SOURCE_DIR}/src/lib)
target_compile_definitions(mygames_dos16_pcm_hardware_smoke PRIVATE MYGAMES_DOS16_PCM_TEST)
target_link_libraries(mygames_dos16_pcm_hardware_smoke PRIVATE mygames_dos16)
set_target_properties(mygames_dos16_pcm_hardware_smoke PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON C_EXTENSIONS OFF)
add_test(NAME mygames.dos16-pcm-hardware COMMAND mygames_dos16_pcm_hardware_smoke)
