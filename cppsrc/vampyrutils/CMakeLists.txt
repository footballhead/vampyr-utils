add_library(vampyrutils STATIC
    bmp2con.cpp
    color.cpp
    con2bmp.cpp
    csv.cpp
    image.cpp
    io.cpp
    math.cpp
    stb.cpp
    )
target_include_directories(vampyrutils
    PUBLIC
        ..
    )
