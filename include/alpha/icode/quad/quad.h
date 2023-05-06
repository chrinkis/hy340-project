#pragma once

#include <alpha/icode/expr.h>

namespace alpha::icode::quad {

class Quad {
 public:
  enum class Opcode {
    ASSIGN,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    UMINUS,
    AND,
    OR,
    NOT,
    IF_EQ,
    IF_NOTEQ,
    IF_LESSEQ,
    IF_GREATEREQ,
    IF_LESS,
    IF_GREATER,
    CALL,
    PARAM,
    RET,
    GETRETVAL,
    FUNCSTART,
    FUNCEND,
    TABLECREATE,
    TABLEGETELEM,
    TABLESETELEM,
  };

  using Label = unsigned;
  using Line = unsigned;

 private:
  Opcode opcode;

  Expr::SharedPtr result;
  Expr::SharedPtr arg1;
  Expr::SharedPtr arg2;

  Label label;

  Line line;

 public:
  Opcode get_opcode() const;

  Expr::SharedPtr get_result() const;
  Expr::SharedPtr get_arg1() const;
  Expr::SharedPtr get_arg2() const;

  Label get_label() const;

  Line get_line() const;
};

}  // namespace alpha::icode::quad
