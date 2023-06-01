#include <alpha/tcode/abc/instruction/arg.h>

#include <utils/warnings.h>

namespace alpha::tcode::abc::instruction {

Arg::Arg(const icode::Expr& expr) {
  WARN_EMPTY_FUNC_IMPL();
}

Arg::Type Arg::get_type() const {
  return this->type;
}

unsigned Arg::get_value() const {
  return this->value;
}

}  // namespace alpha::tcode::abc::instruction
