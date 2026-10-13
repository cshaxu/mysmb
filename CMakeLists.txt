cmake_minimum_required(VERSION 3.20)

project(mygames LANGUAGES C)

# Applications own policy and products; libraries build without app resources.
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
add_test(NAME mygames.library-purity COMMAND ${Python3_EXECUTABLE}
    ${CMAKE_SOURCE_DIR}/test/lib/test_dependency_purity.py)
add_subdirectory(src/lib/kvm)
add_subdirectory(src/lib/dos16)
add_subdirectory(src/lib/win32)
add_subdirectory(src/lib/win16)
option(MYGAMES_BUILD_MARIO "Build Mario and its owner-ROM targets" ON)
if(MYGAMES_BUILD_MARIO)
    add_subdirectory(src/app-mario)
endif()

option(MYGAMES_BUILD_MINE "Build the independent Mine application" ON)
if(MYGAMES_BUILD_MINE)
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/app-mine/CMakeLists.txt")
        message(FATAL_ERROR "MYGAMES_BUILD_MINE requires src/app-mine/CMakeLists.txt")
    endif()
    add_subdirectory(src/app-mine)
endif()
