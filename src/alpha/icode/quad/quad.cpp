#include <alpha/icode/quad/quad.h>

#include <cassert>
#include <iomanip>
#include <string>

namespace alpha::icode::quad {

std::string to_string(Quad::Opcode opcode);

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

std::ostream& operator<<(std::ostream& os, const Quad& quad) {
  auto ident = [](int w = 26) { return std::setw(w); };

  os << ident();
  os << to_string(quad.opcode);

  os << ident();
  if (quad.result) {
    os << quad.result.value();
  }

  os << ident();
  if (quad.arg1) {
    os << quad.arg1.value();
  }

  os << ident();
  if (quad.arg2) {
    os << quad.arg2.value();
  }

  os << ident();
  if (quad.label) {
    os << quad.label.value();
  }

  // FIXME what to do with `quad.line`. Huh?

  return os;
}

std::string to_string(Quad::Opcode opcode) {
  switch (opcode) {
    case Quad::Opcode::ASSIGN:
      return "assign";
    case Quad::Opcode::ADD:
      return "add";
    case Quad::Opcode::SUB:
      return "sub";
    case Quad::Opcode::MUL:
      return "mul";
    case Quad::Opcode::DIV:
      return "div";
    case Quad::Opcode::MOD:
      return "mod";
    case Quad::Opcode::UMINUS:
      return "uminus";
    case Quad::Opcode::AND:
      return "and";
    case Quad::Opcode::OR:
      return "or";
    case Quad::Opcode::NOT:
      return "not";
    case Quad::Opcode::IF_EQ:
      return "if_eq";
    case Quad::Opcode::IF_NOTEQ:
      return "if_noteq";
    case Quad::Opcode::IF_LESSEQ:
      return "if_lesseq";
    case Quad::Opcode::IF_GREATEREQ:
      return "if_greatereq";
    case Quad::Opcode::IF_LESS:
      return "if_less";
    case Quad::Opcode::IF_GREATER:
      return "if_greater";
    case Quad::Opcode::CALL:
      return "call";
    case Quad::Opcode::PARAM:
      return "param";
    case Quad::Opcode::RET:
      return "return";
    case Quad::Opcode::GETRETVAL:
      return "getretval";
    case Quad::Opcode::FUNCSTART:
      return "funcstart";
    case Quad::Opcode::FUNCEND:
      return "funcend";
    case Quad::Opcode::TABLECREATE:
      return "tablecreate";
    case Quad::Opcode::TABLEGETELEM:
      return "tablegetelem";
    case Quad::Opcode::TABLESETELEM:
      return "tablesetelem";
    default:
      assert(0);
  }

  assert(0);
}

}  // namespace alpha::icode::quad
