#include <alpha/lang/syntax/manager/nonterminal/loopstmt.h>

#include <alpha/lang/syntax/manager/nonterminal/stmt.h>

using namespace alpha::syntax::manager::nonterminal;

Loopstmt Loopstmt::from_loopStart_stmt_loopEnd(const Stmt& stmt) {
  Loopstmt loopstmt;

  loopstmt.set_breaklist(stmt.get_breaklist());
  loopstmt.set_contlist(stmt.get_contlist());

  return loopstmt;
}

Loopstmt::Quad::Label Loopstmt::get_breaklist() const {
  return this->breaklist;
}

void Loopstmt::set_breaklist(const Quad::Label& breaklist) {
  this->breaklist = breaklist;
}

Loopstmt::Quad::Label Loopstmt::get_contlist() const {
  return this->contlist;
}

void Loopstmt::set_contlist(const Quad::Label& contlist) {
  this->contlist = contlist;
}
