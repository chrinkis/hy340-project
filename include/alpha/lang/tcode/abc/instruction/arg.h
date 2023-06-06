#pragma once

#include <alpha/lang/icode/expr.h>
#include <alpha/lang/icode/quad/quad.h>
#include <alpha/lang/symbol/symbol.h>

#include <functional>

namespace alpha::tcode::abc::instruction {

class Arg {
 public:
  // FIXME
  using InstrSrcLine = unsigned;

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

  using Mapper = std::function<InstrSrcLine(const icode::quad::Quad::Line)>;

 private:
  Type type;
  unsigned value;

 private:
  Arg(const Type& type, unsigned value);

 public:
  Arg();
  Arg(const Arg& arg);

  static Arg from_expr(const icode::Expr& expr, const Mapper& icode_to_tcode);
  static Arg from_number(const double number);
  static Arg from_bool(const bool boolean);
  static Arg for_label(const InstrSrcLine& instr_src_line);
  static Arg for_ret_val();

  Type get_type() const;
  unsigned get_value() const;

 private:
  static Type type_of_var(const symbol::Symbol& symbol);
  static unsigned value_of_program_func(const symbol::Symbol& symbol,
                                        const Mapper& icode_to_tcode);
};

}  // namespace alpha::tcode::abc::instruction
