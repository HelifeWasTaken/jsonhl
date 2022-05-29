project(jsonhl)

cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC
    src/*.cpp
)

add_library(${PROJECT_NAME} STATIC ${SRC})
