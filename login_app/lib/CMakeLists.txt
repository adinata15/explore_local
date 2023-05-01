cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

# note that the reference path if not specified always start from the root dir
# so dont use relative path 
file(GLOB CXX_FILES ${PROJECT_SOURCE_DIR}/lib/*.cpp)

# message("This is ${CXX_FILES}")

add_library(lib ${CXX_FILES})
# target_link_directories(lib PUBLIC ${HEADER_FILES})