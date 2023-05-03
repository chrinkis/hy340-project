#include <alpha/icode/quad/quad.h>

namespace alpha::icode::quad {

Opcode Quad::get_opcode() const {
  return this->opcode;
}

Expr::SharedPtr Quad::get_result() const {
  return this->result;
}

Expr::SharedPtr Quad::get_arg1() const {
  return this->arg1;
}

Expr::SharedPtr Quad::get_arg2() const {
  return this->arg2;
}

Quad::Label Quad::get_label() const {
  return this->label;
}

Quad::Line Quad::get_line() const {
  return this->line;
}

}  // namespace alpha::icode::quad
