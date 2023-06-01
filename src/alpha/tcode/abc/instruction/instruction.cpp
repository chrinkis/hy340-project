#include <alpha/tcode/abc/instruction/instruction.h>

#include <utils/warnings.h>

namespace alpha::tcode::abc::instruction {

Instruction::Instruction(const icode::quad::Quad& quad)
    : result(Arg::for_ret_val()) {
  WARN_EMPTY_FUNC_IMPL();
}

Opcode Instruction::get_opcode() const {
  return this->opcode;
}

Arg Instruction::get_result() const {
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
