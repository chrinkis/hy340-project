#pragma once

#include <alpha/icode/expr.h>
#include <alpha/symbol/symbol.h>

namespace alpha::tcode::abc::instruction {

class Arg {
 public:
  // FIXME
  using InstrSrcLine = unsigned;

 public:
  enum class Type {
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
  };

 private:
  Type type;
  unsigned value;

 private:
  Arg(const Type& type, unsigned value);

 public:
  Arg(const Arg& arg);

  static Arg from_expr(const icode::Expr& expr);
  static Arg from_number(const double number);
  static Arg from_bool(const bool boolean);
  static Arg for_label(const InstrSrcLine& instr_src_line);
  static Arg for_ret_val();

  Type get_type() const;
  unsigned get_value() const;

 private:
  static Type type_of_var(const symbol::Symbol& symbol);
  static unsigned value_of_program_func(const symbol::Symbol& symbol);
};

}  // namespace alpha::tcode::abc::instruction
