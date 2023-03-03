add_library(BVH OBJECT)
aux_source_directory(. srcs)
target_sources(BVH PRIVATE ${srcs})
target_include_directories(BVH PRIVATE ${PROJECT_SOURCE_DIR}/include)