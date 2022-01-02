cmake_minimum_required(VERSION 3.20)

file(GLOB sources
        "io/*.c"
        "notes/*.c"
        "onset/*.c"
        "pitch/*.c"
        "spectral/*.c"
        "synth/*.c"
        "tempo/*.c"
        "temporal/*.c"
        "utils/*.c"
        "*.c")

file(GLOB headers
        "io/*.h"
        "notes/*.h"
        "onset/*.h"
        "pitch/*.h"
        "spectral/*.h"
        "synth/*.h"
        "tempo/*.h"
        "temporal/*.h"
        "utils/*.h"
        "*.h")

add_library(Aubio ${sources} ${headers})

target_include_directories(Aubio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
