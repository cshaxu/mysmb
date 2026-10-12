add_library(mygames_kvm STATIC
    src/color.c
    src/glyph.c
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
