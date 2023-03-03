add_library(AABB OBJECT)
aux_source_directory(. srcs)
target_sources(AABB PRIVATE ${srcs})
target_include_directories(AABB PRIVATE ${PROJECT_SOURCE_DIR}/include)