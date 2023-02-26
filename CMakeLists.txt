cmake_minimum_required (VERSION 3.18.4)

# For debugging
set(CMAKE_BUILD_TYPE Debug)

# For Clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define the project
project(hy340-project)

# For Flex
find_package(FLEX 2.5.13)

flex_target(FlexTarget src/lex/scanner.l "${CMAKE_SOURCE_DIR}/src/lex/scanner.c"
            DEFINES_FILE "${CMAKE_SOURCE_DIR}/include/lex/scanner.h"
)

# Define libraries
add_library(LIB_token STATIC "")
add_library(LIB_collections STATIC "")

# Add CMakeLists from subdirectory
add_subdirectory(src)
add_subdirectory(demo)

# add_subdirectory(src)
add_executable(hy340-project
    ${FLEX_FlexTarget_OUTPUTS}
)
target_link_libraries(hy340-project LIB_token)
