#pragma once

#include <alpha/icode/expr.h>

#include <optional>
#include <ostream>

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
    JUMP,
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

  std::optional<Expr> result;
  std::optional<Expr> arg1;
  std::optional<Expr> arg2;

  std::optional<Label> label;

  std::optional<Line> line;

 public:
  Quad(const Opcode& opcode,
       const Expr& result);  // for function

  Opcode get_opcode() const;

  Expr get_result() const;
  Expr get_arg1() const;
  Expr get_arg2() const;

  Label get_label() const;

  Line get_line() const;

 public:
  friend std::ostream& operator<<(std::ostream& os, const Quad& quad);
};

}  // namespace alpha::icode::quad
