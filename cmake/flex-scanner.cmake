# Flex
find_package(FLEX 2.5.13)

flex_target(FlexScanner
    # Source file
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/lex/scanner.l

    # Output (c/cpp) source file
    ${CMAKE_CURRENT_BINARY_DIR}/src/alpha/lang/lex/scanner.cpp
)

# Create required directories
file(MAKE_DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/src/alpha/lang/lex
)
