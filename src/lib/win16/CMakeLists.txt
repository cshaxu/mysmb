add_library(mygames_win16_contract INTERFACE)
target_include_directories(mygames_win16_contract INTERFACE "${CMAKE_SOURCE_DIR}/src/lib")
target_link_libraries(mygames_win16_contract INTERFACE mygames_kvm)

add_executable(mygames_win16_contract_smoke ${CMAKE_SOURCE_DIR}/lib/win16/test/application_contract_smoke.c)
target_link_libraries(mygames_win16_contract_smoke PRIVATE mygames_win16_contract)
set_target_properties(mygames_win16_contract_smoke PROPERTIES
    C_STANDARD 90 C_STANDARD_REQUIRED ON C_EXTENSIONS OFF)
add_test(NAME mygames.win16-application-contract COMMAND mygames_win16_contract_smoke)

find_package(Python3 COMPONENTS Interpreter REQUIRED)
add_test(NAME mygames.win16-mz-binding COMMAND ${Python3_EXECUTABLE}
    ${CMAKE_SOURCE_DIR}/lib/win16/test/test_mz_binding.py)

add_library(mygames_win16_dib STATIC dib.c clock.c)
target_include_directories(mygames_win16_dib PUBLIC "${CMAKE_SOURCE_DIR}/src/lib")
target_link_libraries(mygames_win16_dib PUBLIC mygames_kvm)
add_executable(mygames_win16_dib_smoke ${CMAKE_SOURCE_DIR}/lib/win16/test/dib_smoke.c)
target_link_libraries(mygames_win16_dib_smoke PRIVATE mygames_win16_dib)
add_test(NAME mygames.win16-dib-projection COMMAND mygames_win16_dib_smoke)
add_executable(mygames_win16_clock_smoke ${CMAKE_SOURCE_DIR}/lib/win16/test/clock_smoke.c)
target_link_libraries(mygames_win16_clock_smoke PRIVATE mygames_win16_dib)
add_test(NAME mygames.win16-clock-budget COMMAND mygames_win16_clock_smoke)

add_executable(mygames_win16_audio_smoke ${CMAKE_SOURCE_DIR}/lib/win16/test/audio_smoke.c audio.c)
target_include_directories(mygames_win16_audio_smoke PRIVATE ${CMAKE_SOURCE_DIR}/lib/win16/test/fake_sdk "${CMAKE_SOURCE_DIR}/src/lib")
target_link_libraries(mygames_win16_audio_smoke PRIVATE mygames_kvm)
add_test(NAME mygames.win16-audio-lifecycle COMMAND mygames_win16_audio_smoke)
add_executable(mygames_win16_file_smoke ${CMAKE_SOURCE_DIR}/lib/win16/test/file_replace_smoke.c file_replace.c)
target_include_directories(mygames_win16_file_smoke PRIVATE "${CMAKE_SOURCE_DIR}/src/lib")
target_link_libraries(mygames_win16_file_smoke PRIVATE mygames_kvm)
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/file-test")
add_test(NAME mygames.win16-file-replace COMMAND mygames_win16_file_smoke)
set_tests_properties(mygames.win16-file-replace PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/file-test")

add_executable(mygames_win16_file_path_smoke ${CMAKE_SOURCE_DIR}/lib/win16/test/file_path_smoke.c file.c)
target_include_directories(mygames_win16_file_path_smoke PRIVATE ${CMAKE_SOURCE_DIR}/lib/win16/test/fake_sdk "${CMAKE_SOURCE_DIR}/src/lib")
target_link_libraries(mygames_win16_file_path_smoke PRIVATE mygames_kvm)
add_test(NAME mygames.win16-file-path COMMAND mygames_win16_file_path_smoke)
