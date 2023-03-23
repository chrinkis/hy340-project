include(flex-scanner)
include(bison-parser)

# Connect Flex with Bison
ADD_FLEX_BISON_DEPENDENCY(FlexScanner BisonParser)

# Create Objective Library
add_library(flex_and_bison
    # Kind of library
    OBJECT

    # Flex and Bison files
    ${FLEX_FlexScanner_OUTPUTS}
    ${BISON_BisonParser_OUTPUTS}

    # Files Flex and Bison needs
    ${CMAKE_SOURCE_DIR}/src/alpha/token/token.cpp
)

# WARNING: all file of of lib `flex_and_bison` have direct
# access to this directories.
#
# That means that they can include every file without
# specifing the path.
#
# For example, `#include "parser.h"`, will be valid
target_include_directories(flex_and_bison
    # Kind
    PRIVATE

    # Files
    ${CMAKE_CURRENT_BINARY_DIR}/include/alpha/syntax
)
