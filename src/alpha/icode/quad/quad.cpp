#include <alpha/icode/quad/quad.h>

#include <cassert>

namespace alpha::icode::quad {

Quad::Quad(const Opcode& opcode, const Expr& result)
    : opcode(opcode), result(result) {}

Quad::Opcode Quad::get_opcode() const {
  return this->opcode;
}

Expr Quad::get_result() const {
  return this->result.value();
}

Expr Quad::get_arg1() const {
  return this->arg1.value();
}

Expr Quad::get_arg2() const {
  return this->arg2.value();
}

Quad::Label Quad::get_label() const {
  return this->label.value();
}

Quad::Line Quad::get_line() const {
  return this->line.value();
}

}  // namespace alpha::icode::quad
