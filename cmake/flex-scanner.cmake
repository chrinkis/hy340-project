# Flex
find_package(FLEX 2.5.13)

flex_target(FlexScanner
    # Source file
    ${CMAKE_SOURCE_DIR}/src/alpha/lex/scanner.l

    # Output (c/cpp) source file
    ${CMAKE_SOURCE_DIR}/src/alpha/lex/scanner.cpp
)
