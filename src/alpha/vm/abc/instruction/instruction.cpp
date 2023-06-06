#include <alpha/vm/abc/instruction/instruction.h>

namespace alpha::vm::abc::instruction {

Instruction::Instruction(const SrcLine& src_line,
                         const Opcode& opcode,
                         const Arg& result,
                         const Arg& arg_a,
                         const Arg& arg_b)
    : src_line(src_line),
      opcode(opcode),
      result(result),
      arg_a(arg_a),
      arg_b(arg_b) {}

Instruction::Instruction(const Instruction& instruction)
    : src_line(instruction.src_line),
      opcode(instruction.opcode),
      result(instruction.result),
      arg_a(instruction.arg_a),
      arg_b(instruction.arg_b) {}

Opcode Instruction::get_opcode() const {
  return this->opcode;
}

Arg Instruction::get_result() const {
  return this->result;
}

Arg Instruction::get_arg_a() const {
  return this->arg_a;
}

Arg Instruction::get_arg_b() const {
  return this->arg_b;
}

Instruction::SrcLine Instruction::get_src_line() const {
  return this->src_line;
}

}  // namespace alpha::vm::abc::instruction
