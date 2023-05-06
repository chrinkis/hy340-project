#pragma once

#include <alpha/icode/expr.h>
#include <alpha/icode/opcode.h>

namespace alpha::icode::quad {

class Quad {
 public:
  using Label = unsigned;
  using Line = unsigned;

 private:
  Opcode opcode;

  Expr result;
  Expr arg1;
  Expr arg2;

  Label label;

  Line line;

 public:
  Opcode get_opcode() const;

  Expr get_result() const;
  Expr get_arg1() const;
  Expr get_arg2() const;

  Label get_label() const;

  Line get_line() const;
};

}  // namespace alpha::icode::quad
