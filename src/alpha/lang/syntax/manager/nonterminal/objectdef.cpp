#include <alpha/lang/syntax/manager/nonterminal/objectdef.h>

#include <alpha/lang/icode/expr.h>
#include <alpha/lang/icode/quad/table.h>
#include <alpha/lang/symbol/table_manager.h>
#include <alpha/lang/syntax/manager/nonterminal/elist.h>
#include <alpha/lang/syntax/manager/nonterminal/indexed.h>

#include <ranges>

using namespace alpha::syntax::manager::nonterminal;
using Opcode = alpha::icode::quad::Quad::Opcode;

Objectdef Objectdef::from_lSqrBrackTkn_elist_rSqrBrackTkn(const Elist& elist) {
  namespace views = std::ranges::views;

  Objectdef objectdef;

  auto temp_var = symTable.new_temp_variable();
  icode::Expr table = icode::Expr::for_new_table(temp_var);
  quadTable.emit(Opcode::TABLECREATE, table);

  int i = 0;
  for (auto current_expr : views::reverse(elist.get_icode_elist())) {
    quadTable.emit(Opcode::TABLESETELEM, current_expr, table,
                   icode::Expr::for_const_num(i++));
  }

  objectdef.set_expr(table);

  return objectdef;
}

Objectdef Objectdef::from_lSqrBrackTkn_indexed_rSqrBrackTkn(
    const Indexed& indexed) {
  Objectdef objectdef;

  auto temp_var = symTable.new_temp_variable();
  icode::Expr table = icode::Expr::for_new_table(temp_var);
  quadTable.emit(Opcode::TABLECREATE, table);

  for (auto pair : indexed.get_indexed_list()) {
    icode::Expr index = pair.first;
    icode::Expr value = pair.second;
    quadTable.emit(Opcode::TABLESETELEM, value, table, index);
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
