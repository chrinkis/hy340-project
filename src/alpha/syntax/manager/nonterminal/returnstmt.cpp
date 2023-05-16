#include <alpha/syntax/manager/nonterminal/returnstmt.h>

#include <alpha/icode/quad/table.h>
#include <alpha/syntax/manager/nonterminal/expr.h>

using namespace alpha::syntax::manager::nonterminal;

void Returnstmt::returnTkn_semicolonTkn() {
  quadTable.emit_ret();
}

void Returnstmt::returnTkn_expr_semicolonTkn(const Expr& expr) {
  quadTable.emit_ret(expr.get_expr());
}
