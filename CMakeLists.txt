cmake_minimum_required (VERSION 3.18.4)

# For debugging
set(CMAKE_BUILD_TYPE Debug)

# For Clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define the project
project(hy340-project)

# For Flex
find_package(FLEX 2.5.13)

flex_target(FlexTarget src/alpha/lex/scanner.l "${CMAKE_SOURCE_DIR}/src/alpha/lex/scanner.c"
            DEFINES_FILE "${CMAKE_SOURCE_DIR}/include/alpha/lex/scanner.h"
)

# For target al
add_executable(al
    demo/lex/al/al.c
    src/collections/stack.c
    src/alpha/token/alpha_token.c
    ${FLEX_FlexTarget_OUTPUTS}
)

target_include_directories(al
    PUBLIC include
)
