#include <alpha/tcode/abc/instruction/instruction.h>

#include <utils/warnings.h>

namespace alpha::tcode::abc::instruction {

void Instruction::init_result_from_label(const icode::quad::Quad& quad) {
  if (quad.get_label() < quad.get_line()) {
    FIXME
  } else {
    FIXME
  }
}

void Instruction::init_as_nullary(const Opcode& opcode,
                                  const icode::quad::Quad& quad) {
  this->opcode = opcode;

  this->result = Arg::from_expr(quad.get_result());
}

void Instruction::init_as_unary(const Opcode& opcode,
                                const icode::quad::Quad& quad) {
  this->opcode = opcode;

  this->result = Arg::from_expr(quad.get_result());
  this->arg_a = Arg::from_expr(quad.get_arg1());
}

void Instruction::init_as_binary(const Opcode& opcode,
                                 const icode::quad::Quad& quad) {
  this->opcode = opcode;

  this->result = Arg::from_expr(quad.get_result());
  this->arg_a = Arg::from_expr(quad.get_arg1());
  this->arg_b = Arg::from_expr(quad.get_arg2());
}

void Instruction::init_as_relational(const Opcode& opcode,
                                     const icode::quad::Quad& quad) {
  this->opcode = opcode;

  this->init_result_from_label(quad);
  this->arg_a = Arg::from_expr(quad.get_arg1());
  this->arg_b = Arg::from_expr(quad.get_arg2());
}

void Instruction::init_as_jump(const icode::quad::Quad& quad) {
  this->opcode = Opcode::JUMP;

  this->init_result_from_label(quad);
}

void Instruction::init_with_one_arg(const Opcode& opcode,
                                    const icode::quad::Quad& quad) {
  this->opcode = opcode;

  this->arg_a = Arg::from_expr(quad.get_arg1());
}

void Instruction::init_as_get_ret_val(const icode::quad::Quad& quad) {
  this->opcode = Opcode::ASSIGN;

  this->result = Arg::from_expr(quad.get_result());
  this->arg_a = Arg::for_ret_val();
}

Instruction::Instruction(const icode::quad::Quad& quad) {
  using Quad = icode::quad::Quad;

  switch (quad.get_opcode()) {
    case Quad::Opcode::ASSIGN:
      this->init_as_unary(Opcode::ASSIGN, quad);
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
      this->init_as_unary(Opcode::UMINUS, quad);
      break;
    case Quad::Opcode::AND:
      this->init_as_binary(Opcode::AND, quad);
      break;
    case Quad::Opcode::OR:
      this->init_as_binary(Opcode::OR, quad);
      break;
    case Quad::Opcode::NOT:
      this->init_as_unary(Opcode::NOT, quad);
      break;
    case Quad::Opcode::IF_EQ:
      this->init_as_relational(Opcode::JEQ, quad);
      break;
    case Quad::Opcode::IF_NOTEQ:
      this->init_as_relational(Opcode::JNE, quad);
      break;
    case Quad::Opcode::IF_LESSEQ:
      this->init_as_relational(Opcode::JLE, quad);
      break;
    case Quad::Opcode::IF_GREATEREQ:
      this->init_as_relational(Opcode::JGE, quad);
      break;
    case Quad::Opcode::IF_LESS:
      this->init_as_relational(Opcode::JLT, quad);
      break;
    case Quad::Opcode::IF_GREATER:
      this->init_as_relational(Opcode::JGT, quad);
      break;
    case Quad::Opcode::JUMP:
      this->init_as_jump(quad);
      break;
    case Quad::Opcode::CALL:
      this->init_with_one_arg(Opcode::CALL, quad);
      break;
    case Quad::Opcode::PARAM:
      this->init_with_one_arg(Opcode::PUSH_ARG, quad);
      break;
    case Quad::Opcode::RET:
      FIXME
      break;
    case Quad::Opcode::GETRETVAL:
      this->init_as_get_ret_val(quad);
      break;
    case Quad::Opcode::FUNCSTART:
      FIXME
      break;
    case Quad::Opcode::FUNCEND:
      FIXME
      break;
    case Quad::Opcode::TABLECREATE:
      this->init_as_nullary(Opcode::NEW_TABLE, quad);
      break;
    case Quad::Opcode::TABLEGETELEM:
      this->init_as_binary(Opcode::TABLE_GET_ELEM, quad);
      break;
    case Quad::Opcode::TABLESETELEM:
      this->init_as_binary(Opcode::TABLE_SET_ELEM, quad);
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
