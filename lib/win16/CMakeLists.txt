add_library(mygames_win16_contract INTERFACE)
target_include_directories(mygames_win16_contract INTERFACE include)
target_link_libraries(mygames_win16_contract INTERFACE mygames_kvm)

add_executable(mygames_win16_contract_smoke test/application_contract_smoke.c)
target_link_libraries(mygames_win16_contract_smoke PRIVATE mygames_win16_contract)
set_target_properties(mygames_win16_contract_smoke PROPERTIES
    C_STANDARD 90 C_STANDARD_REQUIRED ON C_EXTENSIONS OFF)
add_test(NAME mygames.win16-application-contract COMMAND mygames_win16_contract_smoke)

find_package(Python3 COMPONENTS Interpreter REQUIRED)
add_test(NAME mygames.win16-mz-binding COMMAND ${Python3_EXECUTABLE}
    ${CMAKE_CURRENT_SOURCE_DIR}/test/test_mz_binding.py)

add_library(mygames_win16_dib STATIC src/dib.c src/clock.c)
target_include_directories(mygames_win16_dib PUBLIC include)
target_link_libraries(mygames_win16_dib PUBLIC mygames_kvm)
add_executable(mygames_win16_dib_smoke test/dib_smoke.c)
target_link_libraries(mygames_win16_dib_smoke PRIVATE mygames_win16_dib)
add_test(NAME mygames.win16-dib-projection COMMAND mygames_win16_dib_smoke)
add_executable(mygames_win16_clock_smoke test/clock_smoke.c)
target_link_libraries(mygames_win16_clock_smoke PRIVATE mygames_win16_dib)
add_test(NAME mygames.win16-clock-budget COMMAND mygames_win16_clock_smoke)

add_executable(mygames_win16_audio_smoke test/audio_smoke.c src/audio.c)
target_include_directories(mygames_win16_audio_smoke PRIVATE test/fake_sdk include)
target_link_libraries(mygames_win16_audio_smoke PRIVATE mygames_kvm)
add_test(NAME mygames.win16-audio-lifecycle COMMAND mygames_win16_audio_smoke)
add_executable(mygames_win16_file_smoke test/file_replace_smoke.c src/file_replace.c)
target_include_directories(mygames_win16_file_smoke PRIVATE include)
target_link_libraries(mygames_win16_file_smoke PRIVATE mygames_kvm)
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/file-test")
add_test(NAME mygames.win16-file-replace COMMAND mygames_win16_file_smoke)
set_tests_properties(mygames.win16-file-replace PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/file-test")

add_executable(mygames_win16_file_path_smoke test/file_path_smoke.c src/file.c)
target_include_directories(mygames_win16_file_path_smoke PRIVATE test/fake_sdk include)
target_link_libraries(mygames_win16_file_path_smoke PRIVATE mygames_kvm)
add_test(NAME mygames.win16-file-path COMMAND mygames_win16_file_path_smoke)
