add_library(mygames_kvm STATIC
    src/color.c
    src/glyph.c
    src/windows_key.c
)
target_include_directories(mygames_kvm PUBLIC include)
if(MSVC)
    target_compile_options(mygames_kvm PRIVATE /W4 /WX)
else()
    target_compile_options(mygames_kvm PRIVATE -Wall -Wextra -Werror -pedantic)
endif()

add_executable(mygames_kvm_contract_smoke test/kvm_contract_smoke.c)
target_link_libraries(mygames_kvm_contract_smoke PRIVATE mygames_kvm)
add_test(NAME mygames.kvm-contract-smoke COMMAND mygames_kvm_contract_smoke)

add_executable(mygames_windows_key_smoke test/windows_key_smoke.c)
target_link_libraries(mygames_windows_key_smoke PRIVATE mygames_kvm)
add_test(NAME mygames.windows-key-wire COMMAND mygames_windows_key_smoke)
