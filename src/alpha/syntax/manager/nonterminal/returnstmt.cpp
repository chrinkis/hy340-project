#include <alpha/syntax/manager/nonterminal/returnstmt.h>

#include <alpha/icode/quad/table.h>
#include <alpha/symbol/table_manager.h>
#include <alpha/syntax/error.h>
#include <alpha/syntax/manager/nonterminal/expr.h>

using namespace alpha::syntax::manager::nonterminal;
using Opcode = alpha::icode::quad::Quad::Opcode;

void Returnstmt::returnTkn_semicolonTkn(const location& loc) {
  if (!symTable.is_in_func_def()) {
    error::invalid_use_of_return(loc);
  }

  quadTable.emit(Opcode::RET);
}

void Returnstmt::returnTkn_expr_semicolonTkn(const location& loc,
                                             const Expr& _expr) {
  if (!symTable.is_in_func_def()) {
    error::invalid_use_of_return(loc);
  }

  auto expr =
      quadTable.emit_if_bool_expr(_expr.get_expr(), _expr.get_true_list_head(),
                                  _expr.get_false_list_head());

  quadTable.emit(Opcode::RET, expr);
}
