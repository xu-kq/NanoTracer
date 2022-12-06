add_library(Sphere STATIC)
aux_source_directory(. srcs)
target_sources(Sphere PRIVATE ${srcs})
target_include_directories(Sphere PRIVATE ${PROJECT_SOURCE_DIR}/include)
