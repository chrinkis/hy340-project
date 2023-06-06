#include <alpha/lang/syntax/manager/nonterminal/returnstmt.h>

#include <alpha/lang/icode/quad/table.h>
#include <alpha/lang/symbol/table_manager.h>
#include <alpha/lang/syntax/error.h>
#include <alpha/lang/syntax/manager/nonterminal/expr.h>

using namespace alpha::syntax::manager::nonterminal;
using Opcode = alpha::icode::quad::Quad::Opcode;

void Returnstmt::returnTkn_semicolonTkn(const location& loc) {
  if (!symTable.is_in_func_def()) {
    error::invalid_use_of_return(loc);
  }

  quadTable.emit(Opcode::RET);
}

void Returnstmt::returnTkn_expr_semicolonTkn(const location& loc,
                                             const Expr& expr) {
  if (!symTable.is_in_func_def()) {
    error::invalid_use_of_return(loc);
  }

  quadTable.emit(Opcode::RET, expr.get_expr());
}
