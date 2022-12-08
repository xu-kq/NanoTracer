add_library(Material OBJECT)
aux_source_directory(. srcs)
target_sources(Material PRIVATE ${srcs})
target_include_directories(Material PRIVATE ${PROJECT_SOURCE_DIR}/include)