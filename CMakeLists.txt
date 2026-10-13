cmake_minimum_required(VERSION 3.20)

project(mygames LANGUAGES C)

# Applications own their targets; shared libraries will be added beside them.
enable_testing()
add_subdirectory(lib/kvm)
add_subdirectory(lib/dos16)
add_subdirectory(lib/win32)
add_subdirectory(lib/win16)
add_subdirectory(app-mario)

option(MYGAMES_BUILD_MINE "Build the separately admitted Mine application" OFF)
if(MYGAMES_BUILD_MINE)
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/app-mine/CMakeLists.txt")
        message(FATAL_ERROR "app-mine import is not present; complete its provenance admission and history-preserving import before enabling MYGAMES_BUILD_MINE")
    endif()
    add_subdirectory(app-mine)
endif()
