add_library(Ray OBJECT)
aux_source_directory(. srcs)
target_sources(Ray PRIVATE ${srcs})