cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

project(game)

# Source files
file(   GLOB SOURCES
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.h"
        "${PROJECT_SOURCE_DIR}/src/objects/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/objects/*.h"
        "${PROJECT_SOURCE_DIR}/src/ui/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/ui/*.h"
        "${PROJECT_SOURCE_DIR}/src/utils/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/utils/*.h"
    )


# For GDB Debugging
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# Finding Modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add executable and link libraries to it
add_executable(game ${SOURCES})
target_link_libraries(game ${SDL2_LIBRARIES})
