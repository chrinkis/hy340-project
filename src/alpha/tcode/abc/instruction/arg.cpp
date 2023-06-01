#include <alpha/tcode/abc/instruction/arg.h>

#include <utils/warnings.h>

namespace alpha::tcode::abc::instruction {

Arg::Arg(const Type& type, unsigned value) {
  WARN_EMPTY_FUNC_IMPL();
}

Arg::Arg(const Arg& type) {
  WARN_EMPTY_FUNC_IMPL();
}

Arg Arg::from_expr(const icode::Expr& expr) {
  WARN_EMPTY_FUNC_IMPL(Arg::for_ret_val());
}

Arg Arg::from_number(double number) {
  WARN_EMPTY_FUNC_IMPL(Arg::for_ret_val());
}

Arg Arg::from_string(const std::string& string) {
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
