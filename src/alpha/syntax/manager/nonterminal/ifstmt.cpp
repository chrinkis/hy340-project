#include <alpha/syntax/manager/nonterminal/ifstmt.h>

#include <alpha/icode/quad/table.h>
#include <alpha/syntax/manager/nonterminal/ifstmt_else.h>
#include <alpha/syntax/manager/nonterminal/ifstmt_if.h>

using namespace alpha::syntax::manager::nonterminal;

using Quad = alpha::icode::quad::Quad;

void Ifstmt::ifstmtIf_stmt(const IfstmtIf& ifstmt_if, const Stmt& stmt) {
  quadTable.patch_label(ifstmt_if.get_label(), quadTable.get_next_label());
}

void Ifstmt::ifstmtIf_stmt_ifstmtElse_stmt(const IfstmtIf& ifstmt_if,
                                           const Stmt& stmt1,
                                           const IfstmtElse& ifstmt_else,
                                           const Stmt& stmt2) {
  quadTable.patch_label(ifstmt_if.get_label(),
                        ifstmt_else.get_quad_address() + 1);

  quadTable.patch_label(ifstmt_else.get_quad_address(),
                        quadTable.get_next_label());
}
