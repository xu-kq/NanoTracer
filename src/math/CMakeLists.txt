add_library(Vec3 STATIC)
aux_source_directory(. srcs)
target_sources(Vec3 PRIVATE ${srcs})
target_include_directories(Vec3 PRIVATE ${PROJECT_SOURCE_DIR}/include)