add_subdirectory(stb_image)
add_subdirectory(math)
add_subdirectory(Ray)

target_include_directories(Ray PRIVATE ${PROJECT_SOURCE_DIR}/include)