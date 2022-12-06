add_library(Ray OBJECT)
aux_source_directory(. srcs)
target_sources(Ray PRIVATE ${srcs})
target_include_directories(Ray PRIVATE ${PROJECT_SOURCE_DIR}/include)