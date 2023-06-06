cmake_minimum_required (VERSION 3.18.4)

# User options
set(skip_tests ON CACHE BOOL "Ignores tests")

# For debugging
set(CMAKE_BUILD_TYPE Debug)

# For Clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define the project
project(hy340-project)

# Cpp version
set(CMAKE_CXX_STANDARD 20)

# Add cmakes from subdirs
add_subdirectory(src)
if (NOT skip_tests)
    add_subdirectory(test)
endif()
