#pragma once

#include <alpha/lang/icode/expr.h>

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
  Quad(const Opcode& opcode, const Line& line);

  Opcode get_opcode() const;

  Expr get_result() const;
  void set_result(const Expr& result);

  Expr get_arg1() const;
  void set_arg1(const Expr& arg);

  Expr get_arg2() const;
  void set_arg2(const Expr& arg);

  Label get_label() const;
  void set_label(const Label& label);

  Line get_line() const;

 public:
  friend std::ostream& operator<<(std::ostream& os, const Quad& quad);
};

}  // namespace alpha::icode::quad
