cmake_minimum_required(VERSION 3.21)

project(corolib C ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # to generate compile_commands.json

add_subdirectory(flags)
add_subdirectory(src/core)

add_library(coro INTERFACE)

target_include_directories(coro
    INTERFACE
        include/
)

target_link_libraries(coro
    INTERFACE
        core
)

add_executable(coro_run.x
    src/main.c
)

target_link_libraries(coro_run.x
    PRIVATE
        coro
        co-flags
)

# enable_testing()
# add_subdirectory(tests)
