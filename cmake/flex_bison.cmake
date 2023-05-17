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
    ${CMAKE_SOURCE_DIR}/src/alpha/icode/expr.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/icode/quad/quad.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/icode/quad/table.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/symbol/function.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/symbol/scope_space_manager.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/symbol/symbol.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/symbol/table.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/symbol/table_manager.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/symbol/variable.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/error.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/assignexpr.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/block_close.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/block_open.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/breakstmt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/call.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/callsuffix.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/const.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/continuestmt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/elist.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/elist_opt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/expr.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/forstmt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/forstmt_m.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/forstmt_n.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/forstmt_pre.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/funcargs.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/funcbody.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/funcbody_post.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/funcbody_pre.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/funcdef.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/funcprefix.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/idlist_id.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/ifstmt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/ifstmt_else.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/ifstmt_if.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/indexed.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/indexed_opt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/indexedelem.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/loop_end.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/loop_start.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/loopstmt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/lvalue.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/member.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/methodcall.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/normalcall.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/objectdef.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/primary.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/returnstmt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/stmt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/stmts.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/term.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/whilestmt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/whilestmt_cond.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/manager/nonterminal/whilestmt_while.cpp
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
