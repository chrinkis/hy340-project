#include <alpha/tcode/abc/instruction/instruction.h>

#include <utils/warnings.h>

namespace alpha::tcode::abc::instruction {

void Instruction::init_as_binary(const Opcode& opcode,
                                 const icode::quad::Quad& quad) {
  this->opcode = opcode;

  this->result = Arg::from_expr(quad.get_result());
  this->arg_a = Arg::from_expr(quad.get_arg1());
  this->arg_b = Arg::from_expr(quad.get_arg2());
}

Instruction::Instruction(const icode::quad::Quad& quad) {
  using Quad = icode::quad::Quad;

  switch (quad.get_opcode()) {
    case Quad::Opcode::ASSIGN:
      FIXME
      break;
    case Quad::Opcode::ADD:
      this->init_as_binary(Opcode::ADD, quad);
      break;
    case Quad::Opcode::SUB:
      this->init_as_binary(Opcode::SUB, quad);
      break;
    case Quad::Opcode::MUL:
      this->init_as_binary(Opcode::MUL, quad);
      break;
    case Quad::Opcode::DIV:
      this->init_as_binary(Opcode::DIV, quad);
      break;
    case Quad::Opcode::MOD:
      this->init_as_binary(Opcode::MOD, quad);
      break;
    case Quad::Opcode::UMINUS:
      FIXME
      break;
    case Quad::Opcode::AND:
      FIXME
      break;
    case Quad::Opcode::OR:
      FIXME
      break;
    case Quad::Opcode::NOT:
      FIXME
      break;
    case Quad::Opcode::IF_EQ:
      FIXME
      break;
    case Quad::Opcode::IF_NOTEQ:
      FIXME
      break;
    case Quad::Opcode::IF_LESSEQ:
      FIXME
      break;
    case Quad::Opcode::IF_GREATEREQ:
      FIXME
      break;
    case Quad::Opcode::IF_LESS:
      FIXME
      break;
    case Quad::Opcode::IF_GREATER:
      FIXME
      break;
    case Quad::Opcode::JUMP:
      FIXME
      break;
    case Quad::Opcode::CALL:
      FIXME
      break;
    case Quad::Opcode::PARAM:
      FIXME
      break;
    case Quad::Opcode::RET:
      FIXME
      break;
    case Quad::Opcode::GETRETVAL:
      FIXME
      break;
    case Quad::Opcode::FUNCSTART:
      FIXME
      break;
    case Quad::Opcode::FUNCEND:
      FIXME
      break;
    case Quad::Opcode::TABLECREATE:
      FIXME
      break;
    case Quad::Opcode::TABLEGETELEM:
      FIXME
      break;
    case Quad::Opcode::TABLESETELEM:
      FIXME
      break;
  }

  this->src_line = 0;
  FIXME  //^^^^^^^^^^ What `src_line` is?
}

Opcode Instruction::get_opcode() const {
  return this->opcode;
}

std::optional<Arg> Instruction::get_result() const {
  return this->result;
}

std::optional<Arg> Instruction::get_arg_a() const {
  return this->arg_a;
}

std::optional<Arg> Instruction::get_arg_b() const {
  return this->arg_b;
}

Instruction::SrcLine Instruction::get_src_line() const {
  return this->src_line;
}

}  // namespace alpha::tcode::abc::instruction
