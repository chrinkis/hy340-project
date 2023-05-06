#include <alpha/icode/expr.h>

#include <assert.h>

namespace alpha::icode {

Expr Expr::for_program_func(const Symbol::SharedPtr& symbol) {
  assert(symbol->get_type() == Symbol::Type::USER_FUNCTION);

  Expr expr;

  expr.type = Type::PROGRAM_FUNC;
  expr.symbol = symbol;

  return expr;
}

}  // namespace alpha::icode
