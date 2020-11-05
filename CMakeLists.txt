cmake_minimum_required(VERSION 3.17)
project(Voxel)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/libs/include)
link_directories(${CMAKE_SOURCE_DIR}/libs/lib)

add_executable(Voxel src/main.cpp src/RayTracer.cpp src/Utils.cpp src/Box.cpp src/Box.h)
target_link_libraries(Voxel SDL2.dll libSDl2.a libSDl2main.a)
