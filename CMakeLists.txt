cmake_minimum_required(VERSION 3.10)
project(KDE_OpenMP)

# Habilita o uso do OpenMP
find_package(OpenMP REQUIRED)

# Define o compilador padrão
set(CMAKE_CXX_STANDARD 17)

# Adiciona os executáveis
add_executable(kde_sequential kde_sequential.cpp)
add_executable(kde_parallel kde_parallel.cpp)
add_executable(kde_gpu kde_gpu.cpp)

# Configura as flags de compilação para OpenMP
target_compile_options(kde_parallel PRIVATE ${OpenMP_CXX_FLAGS})
target_link_libraries(kde_parallel PRIVATE ${OpenMP_CXX_FLAGS})

target_compile_options(kde_gpu PRIVATE ${OpenMP_CXX_FLAGS})
target_link_libraries(kde_gpu PRIVATE ${OpenMP_CXX_FLAGS})
