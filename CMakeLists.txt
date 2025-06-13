cmake_minimum_required(VERSION 3.10)
project(NDRayTracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Eigen library
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(nd_ray_tracer main.cpp nd_ray_tracer.cpp plotting.cpp)

target_include_directories(nd_ray_tracer PUBLIC ${EIGEN3_INCLUDE_DIR})

# Add compiler flags for warnings
target_compile_options(nd_ray_tracer PRIVATE -Wall -Wextra -Wpedantic)