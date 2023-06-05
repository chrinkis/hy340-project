# Flex
find_package(FLEX 2.5.13)

flex_target(FlexScanner
    # Source file
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/lex/scanner.l

    # Output (c/cpp) source file
    ${CMAKE_BINARY_DIR}/src/alpha/lang/lex/scanner.cpp
)

# Create required directories for Flex
file(MAKE_DIRECTORY
    ${CMAKE_BINARY_DIR}/src/alpha/lang/lex
)

# Bison
find_package(BISON 3.7.5)

bison_target(BisonParser
    # Source file
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/parser.y

    # Output (c/cpp) source file
    ${CMAKE_BINARY_DIR}/src/alpha/lang/syntax/parser.cpp

    # Output header file
    DEFINES_FILE ${CMAKE_BINARY_DIR}/include/alpha/lang/syntax/parser.h

    # Output header file for location
    COMPILE_FLAGS -Dapi.location.file="${CMAKE_BINARY_DIR}/include/alpha/lang/syntax/location.h"

    # File with conflicts info
    VERBOSE REPORT_FILE ${CMAKE_BINARY_DIR}/bison_parser.output
)

# Create required directories for Bison
file(MAKE_DIRECTORY
    ${CMAKE_BINARY_DIR}/src/alpha/lang/syntax
    ${CMAKE_BINARY_DIR}/include/alpha/lang/syntax
)

# Connect Flex with Bison
ADD_FLEX_BISON_DEPENDENCY(FlexScanner BisonParser)

# Get all syntax-managers source files
file(GLOB_RECURSE SYNTAX_MANAGERS  "syntax/manager/*.cpp")

# For target lang
add_executable(lang
    main.cpp

    ${FLEX_FlexScanner_OUTPUTS}
    ${BISON_BisonParser_OUTPUTS}

    token/token.cpp

    lex/error.cpp

    icode/expr.cpp

    icode/quad/quad.cpp
    icode/quad/table.cpp

    symbol/function.cpp
    symbol/scope_space_manager.cpp
    symbol/symbol.cpp
    symbol/table.cpp
    symbol/table_manager.cpp
    symbol/variable.cpp

    syntax/error.cpp
    syntax/loop_counter.cpp

    ${SYNTAX_MANAGERS}

    tcode/abc/consts/consts.cpp
    tcode/abc/consts/user_func.cpp

    tcode/abc/instruction/arg.cpp
    tcode/abc/instruction/instruction.cpp

    tcode/abc/table.cpp

    tcode/abc/writer.cpp
)

# Add `include` directories
target_include_directories(lang
    # Kind
    PRIVATE

    # Directories
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
    ${CMAKE_BINARY_DIR}/include/alpha/lang/syntax
)
