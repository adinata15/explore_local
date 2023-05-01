cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

add_library(utils file.cpp)
# target_link_directories(utils PUBLIC file.hpp)