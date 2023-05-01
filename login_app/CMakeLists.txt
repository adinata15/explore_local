cmake_minimum_required(VERSION 3.25)

project(login_app)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

# message(${PROJECT_SOURCE_DIR})

# set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
# set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
set(UTIL_DIR ${PROJECT_SOURCE_DIR}/utils)
# set(HEADERS_DIR ${PROJECT_SOURCE_DIR}/headers)

# include_directories(${INCLUDE_DIR})
# include_directories(${HEADERS_DIR})

add_subdirectory(${LIB_DIR})
add_subdirectory(${UTIL_DIR})

add_executable(login_app main.cpp)
target_link_libraries(login_app lib utils)


# add_executable(test test.cpp)
# target_link_libraries(test utils)