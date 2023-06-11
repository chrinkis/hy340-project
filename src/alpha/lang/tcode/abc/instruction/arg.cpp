#include <alpha/lang/tcode/abc/instruction/arg.h>

#include <alpha/lang/symbol/function.h>
#include <alpha/lang/tcode/abc/consts/consts.h>
#include <alpha/lang/tcode/abc/consts/user_func.h>
#include <utils/warnings.h>

#include <cassert>

namespace alpha::tcode::abc::instruction {

Arg::Arg(const Type& type, unsigned value) : type(type), value(value) {}

Arg::Arg() : type(Type::EMPTY), value(0){};

Arg::Arg(const Arg& arg) : type(arg.get_type()), value(arg.get_value()) {}

Arg Arg::from_expr(const icode::Expr& expr, const Mapper& icode_to_tcode) {
  Type type;
  unsigned value;

  switch (expr.get_type()) {
    case icode::Expr::Type::VAR:
    case icode::Expr::Type::TABLE_ITEM:
    case icode::Expr::Type::ARITHM_EXPR:
    case icode::Expr::Type::BOOL_EXPR:
    case icode::Expr::Type::NEW_TABLE:
    case icode::Expr::Type::ASSIGN_EXPR:
      assert(expr.has_symbol());
      value = expr.get_symbol()->get_offset();
      type = Arg::type_of_var(*expr.get_symbol());
      break;

    case icode::Expr::Type::CONST_BOOL:
      assert(expr.has_bool_const());
      value = expr.get_bool_const();
      type = Type::BOOL;
      break;

    case icode::Expr::Type::CONST_STRING:
      assert(expr.has_string_const());
      value = tcodeConsts.string(expr.get_string_const());
      type = Type::STRING;
      break;

    case icode::Expr::Type::CONST_NUM:
      assert(expr.has_number_const());
      value = tcodeConsts.number(expr.get_number_const());
      type = Type::NUMBER;
      break;

    case icode::Expr::Type::NIL:
      value = 0;
      type = Type::NIL;
      break;

    case icode::Expr::Type::PROGRAM_FUNC:
      assert(expr.has_symbol());
      value = Arg::value_of_program_func(*expr.get_symbol(), icode_to_tcode);
      type = Type::USER_FUNC;
      break;

    case icode::Expr::Type::LIBRARY_FUNC:
      assert(expr.has_symbol());
      value = tcodeConsts.lib_func_name(expr.get_symbol()->get_name());
      type = Type::LIB_FUNC;
      break;

    case icode::Expr::Type::_NO_TYPE:
    default:
      assert(0);
  }

  return Arg(type, value);
}

Arg Arg::from_number(const double number) {
  return Arg(Type::NUMBER, tcodeConsts.number(number));
}

Arg Arg::from_bool(const bool boolean) {
  return Arg(Type::BOOL, boolean);
}

Arg Arg::for_label(const InstrSrcLine& instr_src_line) {
  return Arg(Type::LABEL, instr_src_line);
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
      return static_cast<Arg::Type>(-1);
  }
}

unsigned Arg::value_of_program_func(const symbol::Symbol& symbol,
                                    const Mapper& icode_to_tcode) {
  const symbol::Function* function =
      dynamic_cast<const symbol::Function*>(&symbol);
  assert(function);

  auto taddr = icode_to_tcode(function->get_iaddress()) +
               1;  // target code address maps to the jump before funcenter

  consts::UserFunc user_func(taddr, function->get_name(),
                             function->get_total_locals());

  return tcodeConsts.user_func(user_func);
}

}  // namespace alpha::tcode::abc::instruction
