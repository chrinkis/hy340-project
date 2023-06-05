#include <alpha/syntax/manager/nonterminal/member.h>

#include <alpha/icode/expr.h>
#include <alpha/icode/quad/table.h>
#include <alpha/syntax/error.h>
#include <alpha/syntax/manager/nonterminal/call.h>
#include <alpha/syntax/manager/nonterminal/expr.h>
#include <alpha/syntax/manager/nonterminal/lvalue.h>

using namespace alpha::syntax::manager::nonterminal;

using Call = alpha::syntax::manager::nonterminal::Call;

Member Member::from_lvalue_dotTkn_idTkn(const Lvalue& lvalue,
                                        const Identifier& id) {
  if ((lvalue.get_expr().get_type() == icode::Expr::Type::LIBRARY_FUNC) ||
      (lvalue.get_expr().get_type() == icode::Expr::Type::PROGRAM_FUNC)) {
    error::invalid_function_operation(error::Operator::DOT,
                                      lvalue.get_expr().get_symbol());
  }

  Member member;

  icode::Expr symbol_expr = quadTable.emit_if_table_item(lvalue.get_expr());
  icode::Expr index = icode::Expr::for_const_string(id.get_name());

  member.set_expr(icode::Expr::for_table_item(symbol_expr, index));

  return member;
}

Member Member::from_lvalue_lSqrBrackTkn_expr_rSqrtBrackTkn(const Lvalue& lvalue,
                                                           const Expr& expr) {
  if ((lvalue.get_expr().get_type() == icode::Expr::Type::LIBRARY_FUNC) ||
      (lvalue.get_expr().get_type() == icode::Expr::Type::PROGRAM_FUNC)) {
    error::invalid_function_operation(error::Operator::SQUARE_BRACKETS,
                                      lvalue.get_expr().get_symbol());
  }

  Member member;

  icode::Expr symbol_expr = quadTable.emit_if_table_item(lvalue.get_expr());
  icode::Expr index = expr.get_expr();

  member.set_expr(icode::Expr::for_table_item(symbol_expr, index));

  return member;
}

Member Member::from_call_dotTkn_idTkn(const Call& call, const Identifier& id) {
  Member member;

  icode::Expr symbol_expr = quadTable.emit_if_table_item(call.get_expr());
  icode::Expr index = icode::Expr::for_const_string(id.get_name());

  member.set_expr(icode::Expr::for_table_item(symbol_expr, index));

  return member;
}

Member Member::from_call_lSqrBrackTkn_expr_rSqrtBrackTkn(const Call& call,
                                                         const Expr& expr) {
  Member member;

  icode::Expr symbol_expr = quadTable.emit_if_table_item(call.get_expr());
  icode::Expr index = expr.get_expr();

  member.set_expr(icode::Expr::for_table_item(symbol_expr, index));

  return member;
}

alpha::icode::Expr Member::get_expr() const {
  return this->expr;
}

void Member::set_expr(const icode::Expr& expr) {
  this->expr = expr;
}
