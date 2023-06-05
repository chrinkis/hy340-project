#pragma once

namespace alpha::vm::abc::instruction {

class Arg {
 public:
  enum class Type : char {
    LABEL = 0,
    GLOBAL = 1,
    FORMAL = 2,
    LOCAL = 3,
    NUMBER = 4,
    STRING = 5,
    BOOL = 6,
    NIL = 7,
    USER_FUNC = 8,
    LIB_FUNC = 9,
    RET_VAL = 10,
    EMPTY = 11,
  };

 private:
  Type type;
  unsigned value;

 public:
  Arg();
  Arg(const Type& type, unsigned value);
  Arg(const Arg& arg);

  Type get_type() const;
  unsigned get_value() const;
};

}  // namespace alpha::vm::abc::instruction
