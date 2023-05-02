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

    # Files Flex needs
    ${CMAKE_SOURCE_DIR}/src/alpha/lex/error.cpp

    # Files Bison needs
    ${CMAKE_SOURCE_DIR}/src/alpha/icode/quad/quad.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/icode/quad/table.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/symbol/function.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/symbol/scope_space_manager.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/symbol/table.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/symbol/table_manager.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/symbol/variable.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/handler/symbol/symbol.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/error.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/handler/symbol/function/argument.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/handler/symbol/function/definition.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/handler/symbol/function/error_checker.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/handler/symbol/variable/global.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/handler/symbol/variable/implicit.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/handler/symbol/variable/local.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/handler/block.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/holder/symbol.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/assignexpr.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/block.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/expr.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/funcdef.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/idlist.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/idlist_opt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/lvalue.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/member.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/primary.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/term.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/terminal/function.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/terminal/identifier.cpp
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
