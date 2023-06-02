#include <alpha/tcode/abc/table.h>

#include <utils/warnings.h>

#define NullaryInstruction(opcode, quad) \
  (Instruction::construct_nullary(this->get_next_label(), opcode, quad))

#define UnaryInstruction(opcode, quad) \
  (Instruction::construct_unary(this->get_next_label(), opcode, quad))

#define BinaryInstruction(opcode, quad) \
  (Instruction::construct_binary(this->get_next_label(), opcode, quad))

#define InstructionWithTwoArgs(opcode, quad) \
  (Instruction::construct_with_two_args(this->get_next_label(), opcode, quad))

namespace alpha::tcode::abc {

void Table::init_instruction_result_from_quad_label(
    Instruction& instruction,
    const icode::quad::Quad& quad) {
  WARN_EMPTY_FUNC_IMPL()
}

void Table::handle_quad_as_nullary(const instruction::Opcode& opcode,
                                   const icode::quad::Quad& quad) {
  Instruction instruction = NullaryInstruction(opcode, quad);

  this->iaddr_to_taddr_map.insert(quad.get_line(), instruction.get_src_line());

  this->emit(instruction);
}

void Table::handle_quad_as_unary(const instruction::Opcode& opcode,
                                 const icode::quad::Quad& quad) {
  Instruction instruction = UnaryInstruction(opcode, quad);

  this->iaddr_to_taddr_map.insert(quad.get_line(), instruction.get_src_line());

  this->emit(instruction);
}

void Table::handle_quad_as_unary_void(const instruction::Opcode& opcode,
                                      const icode::quad::Quad& quad) {
  WARN_EMPTY_FUNC_IMPL()
}

void Table::handle_quad_as_binary(const instruction::Opcode& opcode,
                                  const icode::quad::Quad& quad) {
  Instruction instruction = BinaryInstruction(opcode, quad);

  this->iaddr_to_taddr_map.insert(quad.get_line(), instruction.get_src_line());

  this->emit(instruction);
}

void Table::handle_quad_as_relational(const instruction::Opcode& opcode,
                                      const icode::quad::Quad& quad) {
  Instruction instruction = InstructionWithTwoArgs(opcode, quad);
  this->init_instruction_result_from_quad_label(instruction, quad);

  this->iaddr_to_taddr_map.insert(quad.get_line(), instruction.get_src_line());

  this->emit(instruction);
}

void Table::handle_quad_as_get_ret_val(const icode::quad::Quad& quad) {
  WARN_EMPTY_FUNC_IMPL()
}

void Table::handle_quad(const icode::quad::Quad& quad) {
  using Quad = icode::quad::Quad;
  using Opcode = instruction::Opcode;

  switch (quad.get_opcode()) {
    case Quad::Opcode::ASSIGN:
      this->handle_quad_as_unary(Opcode::ASSIGN, quad);
      break;
    case Quad::Opcode::ADD:
      this->handle_quad_as_binary(Opcode::ADD, quad);
      break;
    case Quad::Opcode::SUB:
      this->handle_quad_as_binary(Opcode::SUB, quad);
      break;
    case Quad::Opcode::MUL:
      this->handle_quad_as_binary(Opcode::MUL, quad);
      break;
    case Quad::Opcode::DIV:
      this->handle_quad_as_binary(Opcode::DIV, quad);
      break;
    case Quad::Opcode::MOD:
      this->handle_quad_as_binary(Opcode::MOD, quad);
      break;
    case Quad::Opcode::UMINUS:
      this->handle_quad_as_unary(Opcode::UMINUS, quad);
      break;
    case Quad::Opcode::AND:
      this->handle_quad_as_binary(Opcode::AND, quad);
      break;
    case Quad::Opcode::OR:
      this->handle_quad_as_binary(Opcode::OR, quad);
      break;
    case Quad::Opcode::NOT:
      this->handle_quad_as_unary(Opcode::NOT, quad);
      break;
    case Quad::Opcode::IF_EQ:
      this->handle_quad_as_relational(Opcode::JEQ, quad);
      break;
    case Quad::Opcode::IF_NOTEQ:
      this->handle_quad_as_relational(Opcode::JNE, quad);
      break;
    case Quad::Opcode::IF_LESSEQ:
      this->handle_quad_as_relational(Opcode::JLE, quad);
      break;
    case Quad::Opcode::IF_GREATEREQ:
      this->handle_quad_as_relational(Opcode::JGE, quad);
      break;
    case Quad::Opcode::IF_LESS:
      this->handle_quad_as_relational(Opcode::JLT, quad);
      break;
    case Quad::Opcode::IF_GREATER:
      this->handle_quad_as_relational(Opcode::JGT, quad);
      break;
    case Quad::Opcode::JUMP:
      FIXME
      break;
    case Quad::Opcode::CALL:
      this->handle_quad_as_unary_void(Opcode::CALL, quad);
      break;
    case Quad::Opcode::PARAM:
      this->handle_quad_as_unary_void(Opcode::PUSH_ARG, quad);
      break;
    case Quad::Opcode::RET:
      FIXME
      break;
    case Quad::Opcode::GETRETVAL:
      this->handle_quad_as_get_ret_val(quad);
      break;
    case Quad::Opcode::FUNCSTART:
      FIXME
      break;
    case Quad::Opcode::FUNCEND:
      FIXME
      break;
    case Quad::Opcode::TABLECREATE:
      this->handle_quad_as_nullary(Opcode::NEW_TABLE, quad);
      break;
    case Quad::Opcode::TABLEGETELEM:
      this->handle_quad_as_binary(Opcode::TABLE_GET_ELEM, quad);
      break;
    case Quad::Opcode::TABLESETELEM:
      this->handle_quad_as_binary(Opcode::TABLE_SET_ELEM, quad);
      break;
  }
}

void Table::parse_quad_table() {
  WARN_EMPTY_FUNC_IMPL();
}

void Table::emit(const Instruction& instruction) {
  WARN_EMPTY_FUNC_IMPL();
}

Table::Instruction::SrcLine Table::get_next_label() const {
  return this->table.size();
}

}  // namespace alpha::tcode::abc
