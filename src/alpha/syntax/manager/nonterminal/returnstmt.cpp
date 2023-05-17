#include <alpha/syntax/manager/nonterminal/returnstmt.h>

#include <alpha/icode/quad/table.h>
#include <alpha/syntax/manager/nonterminal/expr.h>

using namespace alpha::syntax::manager::nonterminal;
using Opcode = alpha::icode::quad::Quad::Opcode;

void Returnstmt::returnTkn_semicolonTkn() {
  quadTable.emit(Opcode::RET);
}

void Returnstmt::returnTkn_expr_semicolonTkn(const Expr& expr) {
  quadTable.emit(Opcode::RET, expr.get_expr());
}
