#include <alpha/syntax/manager/nonterminal/assignexpr.h>

#include <alpha/icode/quad/table.h>
#include <alpha/symbol/table_manager.h>
#include <alpha/syntax/error.h>
#include <alpha/syntax/manager/nonterminal/expr.h>
#include <alpha/syntax/manager/nonterminal/lvalue.h>

using namespace alpha::syntax::manager::nonterminal;
using Opcode = alpha::icode::quad::Quad::Opcode;

Assignexpr Assignexpr::from_lvalue_assignTkn_expr(const Lvalue& lvalue,
                                                  const Expr& expr) {
  if (lvalue.get_expr().get_type() == icode::Expr::Type::LIBRARY_FUNC ||
      lvalue.get_expr().get_type() == icode::Expr::Type::PROGRAM_FUNC) {
    error::invalid_function_operation(error::Operator::ASSIGN,
                                      lvalue.get_expr().get_symbol());
  }

  Assignexpr assignexpr;
  icode::Expr icode_expr;

  if (lvalue.get_expr().get_type() == icode::Expr::Type::TABLE_ITEM) {
    icode::Expr table = lvalue.get_expr();
    icode::Expr index = *lvalue.get_expr().get_index();
    icode::Expr value = expr.get_expr();
    quadTable.emit(Opcode::TABLESETELEM, value, table, index);

    icode_expr = quadTable.emit_if_table_item(lvalue.get_expr());
    icode_expr = icode::Expr::for_assign_expr(icode_expr);

  } else {
    icode::Expr icode_rvalue = expr.get_expr();
    icode::Expr icode_lvalue = lvalue.get_expr();
    quadTable.emit(Opcode::ASSIGN, icode_lvalue, icode_rvalue);

    auto temp_var = symTable.new_temp_variable();
    icode_expr = icode::Expr::for_assign_expr(temp_var);
    quadTable.emit(Opcode::ASSIGN, icode_expr, icode_lvalue);
  }

  assignexpr.set_expr(icode_expr);

  return assignexpr;
}

alpha::icode::Expr Assignexpr::get_expr() const {
  return this->expr;
}

void Assignexpr::set_expr(const icode::Expr& expr) {
  this->expr = expr;
}
