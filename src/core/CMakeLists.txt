add_library(core STATIC)

target_sources(core
    PRIVATE
        source/coro.c
        source/coro_def_internal.c
        source/ctx_internal.s
)

target_include_directories(core
    PUBLIC
        include
)

target_link_libraries(core
    PRIVATE
        co-flags
)
