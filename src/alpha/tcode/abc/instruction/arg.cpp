#include <alpha/tcode/abc/instruction/arg.h>

#include <alpha/tcode/abc/consts/consts.h>
#include <utils/warnings.h>
#include <cassert>

namespace alpha::tcode::abc::instruction {

Arg::Arg(const Type& type, unsigned value) : type(type), value(value) {}

Arg::Arg(const Arg& arg) : type(arg.get_type()), value(arg.get_value()) {}

Arg Arg::from_expr(const icode::Expr& expr) {
  WARN_EMPTY_FUNC_IMPL(Arg::for_ret_val());
}

Arg Arg::from_number(const double number) {
  return Arg(Type::NUMBER, tcodeConsts.number(number));
}

Arg Arg::from_bool(const bool boolean) {
  return Arg(Type::BOOL, boolean);
}

Arg Arg::for_ret_val() {
  return Arg(Type::RET_VAL, 0);
}

Arg::Type Arg::get_type() const {
  return this->type;
}

unsigned Arg::get_value() const {
  return this->value;
}

Arg::Type Arg::type_of_var(const symbol::Symbol& symbol) {
  switch (symbol.get_type()) {
    case symbol::Symbol::Type::GLOBAL:
      return Type::GLOBAL;
    case symbol::Symbol::Type::LOCAL:
      return Type::LOCAL;
    case symbol::Symbol::Type::FORMAL:
      return Type::FORMAL;
    case symbol::Symbol::Type::USER_FUNCTION:
    case symbol::Symbol::Type::LIBRARY_FUNCTION:
    default:
      assert(0);
  }
}
}  // namespace alpha::tcode::abc::instruction
