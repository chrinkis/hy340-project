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
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/token/token.cpp

    # Files Flex needs
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/lex/error.cpp

    # Files Bison needs
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/icode/expr.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/lang/icode/quad/quad.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/icode/quad/table.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/lang/symbol/function.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/symbol/scope_space_manager.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/symbol/symbol.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/symbol/table.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/symbol/table_manager.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/symbol/variable.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/error.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/loop_counter.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/assignexpr.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/block.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/block_body.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/block_close.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/block_open.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/breakstmt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/call.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/callsuffix.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/const.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/continuestmt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/elist.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/elist_opt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/expr.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/forstmt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/forstmt_m.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/forstmt_n.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/forstmt_pre.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/funcargs.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/funcbody.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/funcbody_post.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/funcbody_pre.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/funcdef.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/funcprefix.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/idlist_id.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/ifstmt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/ifstmt_else.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/ifstmt_if.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/indexed.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/indexed_opt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/indexedelem.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/loop_end.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/loop_start.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/loopstmt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/lvalue.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/member.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/methodcall.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/normalcall.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/objectdef.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/primary.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/returnstmt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/stmt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/stmts.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/term.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/whilestmt.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/whilestmt_cond.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/nonterminal/whilestmt_while.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/terminal/function.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/syntax/manager/terminal/identifier.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/lang/tcode/abc/consts/consts.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/tcode/abc/consts/user_func.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/lang/tcode/abc/instruction/arg.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/lang/tcode/abc/instruction/instruction.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/lang/tcode/abc/table.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/lang/tcode/abc/writer.cpp
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
    ${CMAKE_CURRENT_BINARY_DIR}/include/alpha/lang/syntax
)
