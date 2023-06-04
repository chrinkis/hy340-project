#include <alpha/tcode/abc/table.h>

#include <utils/warnings.h>

#include <cassert>

#define MAP_IADDR_WITH_NEXT_TADDR(iaddr) \
  { this->iaddr_to_taddr_map.insert({iaddr, this->get_next_label()}); }

#define ICODE_TO_TCODE_MAPPER \
  [this](auto iaddr) { return this->iaddr_to_taddr_map.at(iaddr); }

#define NullaryInstruction(opcode, quad)                 \
  (Instruction::construct_nullary(ICODE_TO_TCODE_MAPPER, \
                                  this->get_next_label(), opcode, quad))

#define UnaryInstruction(opcode, quad)                                         \
  (Instruction::construct_unary(ICODE_TO_TCODE_MAPPER, this->get_next_label(), \
                                opcode, quad))

#define UnaryVoidInstruction(opcode, quad)                    \
  (Instruction::construct_with_one_arg(ICODE_TO_TCODE_MAPPER, \
                                       this->get_next_label(), opcode, quad))

#define BinaryInstruction(opcode, quad)                 \
  (Instruction::construct_binary(ICODE_TO_TCODE_MAPPER, \
                                 this->get_next_label(), opcode, quad))

#define InstructionWithTwoArgs(opcode, quad)                   \
  (Instruction::construct_with_two_args(ICODE_TO_TCODE_MAPPER, \
                                        this->get_next_label(), opcode, quad))

namespace alpha::tcode::abc {

void Table::init_instruction_result_from_quad_label(
    Instruction& instruction,
    const icode::quad::Quad& quad) {
  using Arg = instruction::Arg;

  if (quad.get_label() >= quad.get_line()) {
    this->incomplete_jumps.emplace_back(instruction.get_src_line(),
                                        quad.get_label());
    return;
  }

  instruction.set_result(
      Arg::for_label(this->iaddr_to_taddr_map.at(quad.get_label())));
}

void Table::handle_quad_as_nullary(const instruction::Opcode& opcode,
                                   const icode::quad::Quad& quad) {
  MAP_IADDR_WITH_NEXT_TADDR(quad.get_line());

  Instruction instruction = NullaryInstruction(opcode, quad);

  this->emit(instruction);
}

void Table::handle_quad_as_unary(const instruction::Opcode& opcode,
                                 const icode::quad::Quad& quad) {
  MAP_IADDR_WITH_NEXT_TADDR(quad.get_line());

  Instruction instruction = UnaryInstruction(opcode, quad);

  this->emit(instruction);
}

void Table::handle_quad_as_unary_void(const instruction::Opcode& opcode,
                                      const icode::quad::Quad& quad) {
  MAP_IADDR_WITH_NEXT_TADDR(quad.get_line());

  Instruction instruction = UnaryVoidInstruction(opcode, quad);

  this->emit(instruction);
}

void Table::handle_quad_as_binary(const instruction::Opcode& opcode,
                                  const icode::quad::Quad& quad) {
  MAP_IADDR_WITH_NEXT_TADDR(quad.get_line());

  Instruction instruction = BinaryInstruction(opcode, quad);

  this->emit(instruction);
}

void Table::handle_quad_as_relational(const instruction::Opcode& opcode,
                                      const icode::quad::Quad& quad) {
  MAP_IADDR_WITH_NEXT_TADDR(quad.get_line());

  Instruction instruction = InstructionWithTwoArgs(opcode, quad);
  this->init_instruction_result_from_quad_label(instruction, quad);

  this->emit(instruction);
}

void Table::handle_quad_as_get_ret_val(const icode::quad::Quad& quad) {
  MAP_IADDR_WITH_NEXT_TADDR(quad.get_line());

  Instruction instruction = Instruction::construct_get_ret_val(
      ICODE_TO_TCODE_MAPPER, this->get_next_label(), quad);

  this->emit(instruction);
}

void Table::handle_quad_as_jump(const icode::quad::Quad& quad) {
  MAP_IADDR_WITH_NEXT_TADDR(quad.get_line());

  Instruction instruction(this->get_next_label(), instruction::Opcode::JUMP);
  this->init_instruction_result_from_quad_label(instruction, quad);

  this->emit(instruction);
}

void Table::handle_quad_as_ret(const icode::quad::Quad& quad) {
  MAP_IADDR_WITH_NEXT_TADDR(quad.get_line());

  Instruction instruction = Instruction::construct_for_return(
      ICODE_TO_TCODE_MAPPER, this->get_next_label(), quad);

  this->emit(instruction);
  this->emit(Instruction(this->get_next_label(), instruction::Opcode::JUMP));
}

void Table::handle_quad_as_func_enter(const icode::quad::Quad& quad) {
  using Opcode = instruction::Opcode;

  this->most_recent_return_list.emplace();

  this->handle_quad_as_nullary(Opcode::FUNC_ENTER, quad);
}

void Table::handle_quad_as_func_exit(const icode::quad::Quad& quad) {
  using Arg = instruction::Arg;

  for (auto& line : this->most_recent_return_list.top()) {
    this->table.at(line).set_result(Arg::for_label(this->get_next_label()));
  }

  this->most_recent_return_list.pop();

  this->handle_quad_as_nullary(instruction::Opcode::FUNC_EXIT, quad);
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
      this->handle_quad_as_jump(quad);
      break;
    case Quad::Opcode::CALL:
      this->handle_quad_as_unary_void(Opcode::CALL, quad);
      break;
    case Quad::Opcode::PARAM:
      this->handle_quad_as_unary_void(Opcode::PUSH_ARG, quad);
      break;
    case Quad::Opcode::RET:
      this->handle_quad_as_ret(quad);
      break;
    case Quad::Opcode::GETRETVAL:
      this->handle_quad_as_get_ret_val(quad);
      break;
    case Quad::Opcode::FUNCSTART:
      this->handle_quad_as_func_enter(quad);
      break;
    case Quad::Opcode::FUNCEND:
      this->handle_quad_as_func_exit(quad);
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

unsigned Table::get_size() const {
  return this->table.size();
}

void Table::parse_quad_table(const icode::quad::Table& quad_table) {
  using Arg = instruction::Arg;

  for (const auto& quad : quad_table) {
    this->handle_quad(quad);
  }

  for (const auto& pair : incomplete_jumps) {
    const auto& src = pair.first;
    const auto& dest = this->iaddr_to_taddr_map.at(pair.second);

    this->table.at(src).set_result(Arg::for_label(dest));
  }
}

void Table::emit(const Instruction& instruction) {
  assert(instruction.get_src_line() == this->get_next_label());

  this->table.push_back(instruction);
}

Table::Instruction::SrcLine Table::get_next_label() const {
  return this->table.size();
}

}  // namespace alpha::tcode::abc
