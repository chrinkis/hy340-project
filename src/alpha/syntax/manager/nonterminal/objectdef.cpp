#include <alpha/syntax/manager/nonterminal/objectdef.h>

#include <alpha/icode/expr.h>
#include <alpha/icode/quad/table.h>
#include <alpha/symbol/table_manager.h>
#include <alpha/syntax/manager/nonterminal/elist.h>
#include <alpha/syntax/manager/nonterminal/indexed.h>

using namespace alpha::syntax::manager::nonterminal;

Objectdef Objectdef::from_lSqrBrackTkn_elist_rSqrBrackTkn(const Elist& elist) {
  Objectdef objectdef;

  auto temp_var = symTable.new_temp_variable();
  icode::Expr table = icode::Expr::for_new_table(temp_var);
  quadTable.emit_tablecreate(table);

  int i = 0;
  for (auto current_expr : elist.get_icode_elist()) {
    quadTable.emit_tablesetelem(table, icode::Expr::for_const_num(i++),
                                current_expr);
  }

  objectdef.set_expr(table);

  return objectdef;
}

Objectdef Objectdef::from_lSqrBrackTkn_indexed_rSqrBrackTkn(
    const Indexed& indexed) {
  Objectdef objectdef;

  auto temp_var = symTable.new_temp_variable();
  icode::Expr table = icode::Expr::for_new_table(temp_var);
  quadTable.emit_tablecreate(table);

  for (auto pair : indexed.get_indexed_list()) {
    icode::Expr index = pair.first;
    icode::Expr value = pair.second;
    quadTable.emit_tablesetelem(table, index, value);
  }

  objectdef.set_expr(table);

  return objectdef;
}

alpha::icode::Expr Objectdef::get_expr() const {
  return this->expr;
}

void Objectdef::set_expr(const icode::Expr& expr) {
  this->expr = expr;
}
