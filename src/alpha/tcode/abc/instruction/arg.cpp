#include <alpha/tcode/abc/instruction/arg.h>

#include <utils/warnings.h>

namespace alpha::tcode::abc::instruction {

Arg::Arg(const Type& type, unsigned value) : type(type), value(value) {}

Arg::Arg(const Arg& arg) : type(arg.get_type()), value(arg.get_value()) {}

Arg Arg::from_expr(const icode::Expr& expr) {
  WARN_EMPTY_FUNC_IMPL(Arg::for_ret_val());
}

Arg Arg::from_number(const double number) {
  WARN_EMPTY_FUNC_IMPL(Arg::for_ret_val());
}

Arg Arg::from_bool(const bool boolean) {
  WARN_EMPTY_FUNC_IMPL(Arg::for_ret_val());
}

Arg Arg::for_ret_val() {
  WARN_EMPTY_FUNC_IMPL(Arg(Arg::Type::NIL, 0));
}

Arg::Type Arg::get_type() const {
  return this->type;
}

unsigned Arg::get_value() const {
  return this->value;
}

}  // namespace alpha::tcode::abc::instruction
