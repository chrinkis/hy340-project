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
};

}  // namespace alpha::icode::quad
