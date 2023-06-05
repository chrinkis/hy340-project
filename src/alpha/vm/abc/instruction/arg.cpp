#include <alpha/vm/abc/instruction/arg.h>

#include <utils/warnings.h>

namespace alpha::vm::abc::instruction {

Arg::Arg() {
  WARN_EMPTY_FUNC_IMPL();
}

Arg::Arg(const Type& type, unsigned value) {
  WARN_EMPTY_FUNC_IMPL();
}

Arg::Arg(const Arg& arg) {
  WARN_EMPTY_FUNC_IMPL();
}

Arg::Type Arg::get_type() const {
  WARN_EMPTY_FUNC_IMPL(Type::EMPTY);
}

unsigned Arg::get_value() const {
  WARN_EMPTY_FUNC_IMPL(0);
}

}  // namespace alpha::vm::abc::instruction
