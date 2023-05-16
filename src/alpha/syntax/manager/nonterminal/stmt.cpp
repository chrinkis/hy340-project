#include <alpha/syntax/manager/nonterminal/stmt.h>

#include <alpha/syntax/manager/nonterminal/breakstmt.h>
#include <alpha/syntax/manager/nonterminal/continuestmt.h>

using namespace alpha::syntax::manager::nonterminal;

Stmt::Stmt() : breaklist(0), contlist(0) {}

Stmt Stmt::from_expr_smclnTkn() {
  Stmt stmt;

  return stmt;
}

Stmt Stmt::from_ifstmt() {
  Stmt stmt;

  return stmt;
}

Stmt Stmt::from_whilestmt() {
  Stmt stmt;

  return stmt;
}

Stmt Stmt::from_forstmt() {
  Stmt stmt;

  return stmt;
}

Stmt Stmt::from_returnstmt() {
  Stmt stmt;

  return stmt;
}

Stmt Stmt::from_breakstmt(const Breakstmt& breakstmt) {
  Stmt stmt;

  stmt.set_breaklist(breakstmt.get_break_list_head());
  stmt.set_contlist(breakstmt.get_continue_list_head());

  return stmt;
}

Stmt Stmt::from_continuestmt(const Continuestmt& continuestmt) {
  Stmt stmt;

  stmt.set_breaklist(continuestmt.get_break_list_head());
  stmt.set_contlist(continuestmt.get_continue_list_head());

  return stmt;
}

Stmt Stmt::from_block() {
  Stmt stmt;

  return stmt;
}

Stmt Stmt::from_funcdef() {
  Stmt stmt;

  return stmt;
}

Stmt Stmt::from_smclnTkn() {
  Stmt stmt;

  return stmt;
}

Stmt::Quad::Label Stmt::get_breaklist() const {
  return this->breaklist;
}

void Stmt::set_breaklist(const Quad::Label& breaklist) {
  this->breaklist = breaklist;
}

Stmt::Quad::Label Stmt::get_contlist() const {
  return this->contlist;
}

void Stmt::set_contlist(const Quad::Label& contlist) {
  this->contlist = contlist;
}
