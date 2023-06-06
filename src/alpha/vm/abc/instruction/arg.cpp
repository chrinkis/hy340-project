#include <alpha/vm/abc/instruction/arg.h>

namespace alpha::vm::abc::instruction {

Arg::Arg() : type(Type::EMPTY), value(0){};

Arg::Arg(const Type& type, unsigned value) : type(type), value(value) {}

Arg::Arg(const Arg& arg) : type(arg.type), value(arg.value) {}

Arg::Type Arg::get_type() const {
  return this->type;
}

unsigned Arg::get_value() const {
  return this->value;
}

}  // namespace alpha::vm::abc::instruction
