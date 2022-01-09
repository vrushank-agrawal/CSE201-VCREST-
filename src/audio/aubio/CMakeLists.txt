cmake_minimum_required(VERSION 3.20)

file(GLOB sources
        "src/io/*.c"
        "src/notes/*.c"
        "src/onset/*.c"
        "src/pitch/*.c"
        "src/spectral/*.c"
        "src/synth/*.c"
        "src/tempo/*.c"
        "src/temporal/*.c"
        "src/utils/*.c"
        "src/*.c")

file(GLOB headers
        "src/io/*.h"
        "src/notes/*.h"
        "src/onset/*.h"
        "src/pitch/*.h"
        "src/spectral/*.h"
        "src/synth/*.h"
        "src/tempo/*.h"
        "src/temporal/*.h"
        "src/utils/*.h"
        "src/*.h")

add_library(Aubio ${sources} ${headers})

target_include_directories(Aubio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
