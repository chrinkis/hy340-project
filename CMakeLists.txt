cmake_minimum_required (VERSION 3.18.4)

# Add `cmake` dir to path
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# For debugging
set(CMAKE_BUILD_TYPE Debug)

# For Clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define the project
project(hy340-project)

# For Flex
include(flex-scanner)

# For target al
add_executable(al
    demo/lex/al/al.c
    src/collections/stack.c
    src/alpha/token/alpha_token.c
    ${FLEX_FlexScanner_OUTPUTS}
)

target_include_directories(al
    PUBLIC include
)
