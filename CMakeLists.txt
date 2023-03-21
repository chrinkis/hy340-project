cmake_minimum_required (VERSION 3.18.4)

# Add `cmake` dir to path
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# For debugging
set(CMAKE_BUILD_TYPE Debug)

# For Clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define the project
project(hy340-project)

# Add `include` directory
include_directories(include)

# Add Flex and Bison
include(flex_bison)

# Add cmakes from subdirs
add_subdirectory(src)
add_subdirectory(demo)
