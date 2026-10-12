cmake_minimum_required(VERSION 3.20)

project(mygames LANGUAGES C)

# Applications own their targets; shared libraries will be added beside them.
enable_testing()
add_subdirectory(lib/kvm)
add_subdirectory(app-mario)
