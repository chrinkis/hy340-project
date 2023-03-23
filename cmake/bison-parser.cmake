# Bison
find_package(BISON 3.7.5)

bison_target(BisonParser
    # Source file
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/parser.y

    # Output (c/cpp) source file
    ${CMAKE_CURRENT_BINARY_DIR}/src/alpha/syntax/parser.cpp

    # Output header file
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/include/alpha/syntax/parser.h

    # Output header file for location
    COMPILE_FLAGS -Dapi.location.file="${CMAKE_CURRENT_BINARY_DIR}/include/alpha/syntax/location.h"

    # File with conflicts info
    VERBOSE REPORT_FILE ${CMAKE_CURRENT_BINARY_DIR}/bison_parser.output
)

# Create required directories
file(MAKE_DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/src/alpha/syntax
    ${CMAKE_CURRENT_BINARY_DIR}/include/alpha/syntax
)