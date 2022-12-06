#
# OBJECT LIBRARY servers as an Abstract provided by CMake.
#
# The convenience comes out while you can regard 'stb_image' as something like a STATIC LIBRARY, however, it is never
# compiled into '.lib'. In fact, it is still compiled into a '.obj' file waiting for linking.
# Thus, it is only an abstract which is easy for us to program in CMake.
add_library(stb_image STATIC)
aux_source_directory(. srcs)
target_sources(stb_image PRIVATE ${srcs})
target_include_directories(stb_image PRIVATE ${PROJECT_SOURCE_DIR}/include)

