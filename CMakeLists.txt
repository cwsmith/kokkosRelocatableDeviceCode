# Kokkos minimally requires 3.16 right now
cmake_minimum_required(VERSION 3.16)
project(Example CXX)
set(CMAKE_CXX_EXTENSIONS Off)
find_package(Kokkos REQUIRED)
add_executable(example helper.cpp example.cpp)
target_link_libraries(example Kokkos::kokkos)
