add_library(Shape OBJECT)
aux_source_directory(. srcs)
target_sources(Shape PRIVATE ${srcs})
target_include_directories(Shape PRIVATE ${PROJECT_SOURCE_DIR}/include)
