#include <alpha/lang/syntax/manager/nonterminal/ifstmt.h>

#include <alpha/lang/icode/quad/table.h>
#include <alpha/lang/syntax/manager/nonterminal/ifstmt_else.h>
#include <alpha/lang/syntax/manager/nonterminal/ifstmt_if.h>
#include <alpha/lang/syntax/manager/nonterminal/stmt.h>

using namespace alpha::syntax::manager::nonterminal;

using Quad = alpha::icode::quad::Quad;

Ifstmt Ifstmt::from_ifstmtIf_stmt(const IfstmtIf& ifstmt_if, const Stmt& stmt) {
  Ifstmt ifstmt;

  quadTable.patch_label(ifstmt_if.get_label(), quadTable.get_next_label());

  return ifstmt;
}

Ifstmt Ifstmt::from_ifstmtIf_stmt_ifstmtElse_stmt(const IfstmtIf& ifstmt_if,
                                                  const Stmt& stmt1,
                                                  const IfstmtElse& ifstmt_else,
                                                  const Stmt& stmt2) {
  Ifstmt ifstmt;

  quadTable.patch_label(ifstmt_if.get_label(),
                        ifstmt_else.get_quad_address() + 1);

  quadTable.patch_label(ifstmt_else.get_quad_address(),
                        quadTable.get_next_label());

  ifstmt.set_breaklist(
      quadTable.merge_lists(stmt1.get_breaklist(), stmt2.get_breaklist()));

  ifstmt.set_contlist(
      quadTable.merge_lists(stmt1.get_contlist(), stmt2.get_contlist()));

  return ifstmt;
}

Quad::Label Ifstmt::get_breaklist() const {
  return this->breaklist;
}

void Ifstmt::set_breaklist(const Quad::Label& breaklist) {
  this->breaklist = breaklist;
}

Quad::Label Ifstmt::get_contlist() const {
  return contlist;
}

void Ifstmt::set_contlist(const Quad::Label& contlist) {
  this->contlist = contlist;
}
