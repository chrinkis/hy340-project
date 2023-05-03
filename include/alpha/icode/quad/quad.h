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
