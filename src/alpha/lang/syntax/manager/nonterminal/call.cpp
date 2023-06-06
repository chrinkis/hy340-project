#include <alpha/lang/syntax/manager/nonterminal/call.h>

#include <alpha/lang/icode/expr.h>
#include <alpha/lang/icode/quad/table.h>
#include <alpha/lang/symbol/table_manager.h>
#include <alpha/lang/syntax/manager/nonterminal/callsuffix.h>
#include <alpha/lang/syntax/manager/nonterminal/elist.h>
#include <alpha/lang/syntax/manager/nonterminal/funcdef.h>
#include <alpha/lang/syntax/manager/nonterminal/lvalue.h>

using Opcode = alpha::icode::quad::Quad::Opcode;

namespace alpha::syntax::manager::nonterminal {

static icode::Expr make_call(const icode::Expr& lv,
                             const Elist::ExprCollection& elist) {
  icode::Expr func = quadTable.emit_if_table_item(lv);

  for (icode::Expr param : elist) {
    quadTable.emit(Opcode::PARAM, emptyExpr, param);
  }

  quadTable.emit(Opcode::CALL, emptyExpr, func);

  icode::Expr result = icode::Expr::for_var(symTable.new_temp_variable());
  quadTable.emit(Opcode::GETRETVAL, result);

  return result;
}

Call Call::from_call_lParTkn_elist_rParTkn(const Call& call,
                                           const Elist& elist) {
  Call this_call;

  this_call.set_expr(make_call(call.get_expr(), elist.get_icode_elist()));

  return this_call;
}

Call Call::from_lvalue_callsuffix(Lvalue& lvalue, Callsuffix& callsuffix) {
  Call call;

  lvalue.set_expr(quadTable.emit_if_table_item(lvalue.get_expr()));

  if (callsuffix.is_method()) {
    icode::Expr t = lvalue.get_expr();

    lvalue.set_expr(quadTable.emit_if_table_item(lvalue.get_expr()));

    lvalue.set_expr(icode::Expr::for_table_item(
        lvalue.get_expr(),
        icode::Expr::for_const_string(callsuffix.get_id().get_name())));

    callsuffix.add_to_elist(t);
  }

  call.set_expr(make_call(lvalue.get_expr(), callsuffix.get_elist()));

  return call;
}

Call Call::from_lParTkn_funcdef_rParTkn_lParTkn_elist_rParTkn(
    const Funcdef& funcdef,
    const Elist& elist) {
  Call call;

  icode::Expr func = icode::Expr::for_program_func(funcdef.get_symbol());

  call.set_expr(make_call(func, elist.get_icode_elist()));

  return call;
}

icode::Expr Call::get_expr() const {
  return this->expr;
}

void Call::set_expr(const icode::Expr& expr) {
  this->expr = expr;
}

}  // namespace alpha::syntax::manager::nonterminal
