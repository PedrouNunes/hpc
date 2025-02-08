cmake_minimum_required(VERSION 3.10)
project(KDE_OpenMP)

find_package(OpenMP REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(kde_sequential kde_sequential.cpp)
add_executable(kde_parallel kde_parallel.cpp)
add_executable(kde_gpu kde_gpu.cpp)

target_link_libraries(kde_sequential PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(kde_parallel PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(kde_gpu PRIVATE OpenMP::OpenMP_CXX)
