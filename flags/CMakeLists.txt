set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # to generate compile_commands.json

add_library(co-flags INTERFACE)

target_compile_features(co-flags
    INTERFACE
        cxx_std_20
        c_std_11
)

target_compile_options(co-flags
    INTERFACE
        -fdiagnostics-color=always
 
        -Wall
        -Wextra
        -Wpedantic
        # -Wshadow
        # -Wconversion
        # -Wsign-conversion
        -Wunused
        -Wformat=2

        -fstack-protector-strong # inserts checks for buffer overflow
        # -fPIE -pie
        
        $<$<CONFIG:Debug>:
            -Og
            -g3
            -ggdb
            # -fsanitize=address,leak,undefined
            -fno-omit-frame-pointer
        >

        $<$<CONFIG:Release>:
            -g
            -O2
            -march=native
            # -flto
            -DNDEBUG
            -Wa,-g
        >
)

target_link_options(co-flags
    INTERFACE
        -fdiagnostics-color=always

        -Wall
        -Wextra
        # -fPIE -pie
        -rdynamic

        $<$<CONFIG:Debug>:
            -Og
            -g3
            -ggdb
            # -fsanitize=address,leak,undefined
            -fno-omit-frame-pointer
        >

        $<$<CONFIG:Release>:
            -g
            -O2
            -march=native
            # -flto
        >
)
