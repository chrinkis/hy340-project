#include <alpha/tcode/abc/instruction/instruction.h>

#include <utils/warnings.h>

namespace alpha::tcode::abc::instruction {

Instruction::Instruction(const SrcLine& src_line, const Opcode& opcode)
    : src_line(src_line), opcode(opcode) {}

Instruction::Instruction(const Instruction& other)
    : src_line(other.src_line), opcode(other.opcode) {}

Instruction Instruction::construct_nullary(const SrcLine& src_line,
                                           const Opcode& opcode,
                                           const icode::quad::Quad& quad) {
  Instruction instruction(src_line, opcode);

  instruction.result = Arg::from_expr(quad.get_result());

  return instruction;
}

Instruction Instruction::construct_unary(const SrcLine& src_line,
                                         const Opcode& opcode,
                                         const icode::quad::Quad& quad) {
  Instruction instruction(src_line, opcode);

  instruction.result = Arg::from_expr(quad.get_result());
  instruction.arg_a = Arg::from_expr(quad.get_arg1());

  return instruction;
}

Instruction Instruction::construct_binary(const SrcLine& src_line,
                                          const Opcode& opcode,
                                          const icode::quad::Quad& quad) {
  Instruction instruction(src_line, opcode);

  instruction.result = Arg::from_expr(quad.get_result());
  instruction.arg_a = Arg::from_expr(quad.get_arg1());
  instruction.arg_b = Arg::from_expr(quad.get_arg2());

  return instruction;
}

Instruction Instruction::construct_with_two_args(
    const SrcLine& src_line,
    const Opcode& opcode,
    const icode::quad::Quad& quad) {
  Instruction instruction(src_line, opcode);

  instruction.arg_a = Arg::from_expr(quad.get_arg1());
  instruction.arg_b = Arg::from_expr(quad.get_arg2());

  return instruction;
}

Instruction Instruction::construct_with_one_arg(const SrcLine& src_line,
                                                const Opcode& opcode,
                                                const icode::quad::Quad& quad) {
  Instruction instruction(src_line, opcode);

  instruction.arg_a = Arg::from_expr(quad.get_arg1());

  return instruction;
}

Instruction Instruction::construct_get_ret_val(const SrcLine& src_line,
                                               const icode::quad::Quad& quad) {
  Instruction instruction(src_line, Opcode::ASSIGN);

  instruction.result = Arg::from_expr(quad.get_result());
  instruction.arg_a = Arg::for_ret_val();

  return instruction;
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
