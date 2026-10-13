add_library(mygames_dos16 STATIC
    src/raw_keyboard.c
    src/pit_clock.c
    src/text_cells.c)
target_include_directories(mygames_dos16 PUBLIC include)
target_link_libraries(mygames_dos16 PUBLIC mygames_kvm)
if(CMAKE_SYSTEM_NAME STREQUAL "DOS")
    target_sources(mygames_dos16 PRIVATE src/host.c src/video_mode.c)
endif()
if(MSVC)
    target_compile_options(mygames_dos16 PRIVATE /W4 /WX)
else()
    target_compile_options(mygames_dos16 PRIVATE -Wall -Wextra -Werror -pedantic)
endif()

add_executable(mygames_dos16_contract_smoke test/dos16_contract_smoke.c)
target_link_libraries(mygames_dos16_contract_smoke PRIVATE mygames_dos16)
add_test(NAME mygames.dos16-contract-smoke COMMAND mygames_dos16_contract_smoke)
add_executable(mygames_dos16_pit_clock_smoke test/pit_clock_smoke.c)
target_link_libraries(mygames_dos16_pit_clock_smoke PRIVATE mygames_dos16)
add_test(NAME mygames.dos16-pit-clock-smoke COMMAND mygames_dos16_pit_clock_smoke)
