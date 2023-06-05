#include <alpha/vm/abc/instruction/instruction.h>

#include <utils/warnings.h>

namespace alpha::vm::abc::instruction {

Instruction::Instruction(const SrcLine& src_line,
                         const Opcode& opcode,
                         const Arg& result,
                         const Arg& arg_a,
                         const Arg& arg_b) {
  WARN_EMPTY_FUNC_IMPL();
}

Instruction::Instruction(const Instruction& instruction) {
  WARN_EMPTY_FUNC_IMPL();
}

Opcode Instruction::get_opcode() const {
  WARN_EMPTY_FUNC_IMPL(Opcode::NOP);
}

Arg Instruction::get_result() const {
  WARN_EMPTY_FUNC_IMPL(Arg());
}

Arg Instruction::get_arg_a() const {
  WARN_EMPTY_FUNC_IMPL(Arg());
}

Arg Instruction::get_arg_b() const {
  WARN_EMPTY_FUNC_IMPL(Arg());
}

Instruction::SrcLine Instruction::get_src_line() const {
  WARN_EMPTY_FUNC_IMPL(0);
}

}  // namespace alpha::vm::abc::instruction
