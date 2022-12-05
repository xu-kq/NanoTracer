cmake_minimum_required(VERSION 3.24)
project(PathTracer LANGUAGES CXX
        VERSION 0.1.0
        DESCRIPTION "A trip follows the tutorial Ray Tracing in One Week."
        HOMEPAGE_URL "https://github.com/xu-kq"
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

if (WIN32)
    # NOMINMAX: stay from 'min/max' macro in <windows.h>
    # _USE_MATH_DEFINES: to use math macro such 'M_PI' in <cmath>
    add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)
endif ()

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Main Executable
add_executable(tracer main.cpp)

add_subdirectory(
        src
        include
)
target_include_directories(tracer PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(tracer
        PRIVATE
        stb_image
        )