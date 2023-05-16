#include <alpha/syntax/manager/nonterminal/stmts.h>

#include <alpha/icode/quad/table.h>
#include <alpha/syntax/manager/nonterminal/stmt.h>

using namespace alpha::syntax::manager::nonterminal;

Stmts Stmts::from_stmt(const Stmt& stmt) {
  Stmts stmts;

  stmts.set_breaklist(stmt.get_breaklist());
  stmts.set_contlist(stmt.get_contlist());

  return stmts;
}

Stmts Stmts::from_stmts_stmt(const Stmts& stmts, const Stmt& stmt) {
  Stmts this_stmts;

  this_stmts.set_breaklist(
      quadTable.merge_lists(stmts.get_breaklist(), stmt.get_breaklist()));

  this_stmts.set_contlist(
      quadTable.merge_lists(stmts.get_contlist(), stmt.get_contlist()));

  return this_stmts;
}
