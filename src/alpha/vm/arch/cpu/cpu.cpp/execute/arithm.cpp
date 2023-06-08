#include <alpha/vm/arch/cpu/cpu.h>

#include <alpha/vm/runtime/messages/error.h>

#include <utils/warnings.h>

namespace alpha::vm::arch::cpu {

void Cpu::execute_arithmetic(
    const AbcInstruction& instr,
    const std::function<double(double, double)>& do_operation) {
  mem::Cell& lv = this->translate_arg_to_cell(instr.get_result());
  mem::Cell& rv_a =
      this->translate_arg_to_cell(instr.get_arg_a(), this->registers.arg_a);
  mem::Cell& rv_b =
      this->translate_arg_to_cell(instr.get_arg_b(), this->registers.arg_b);

  FIXME;  // add missing assert
  FIXME;  // add missing assert
  FIXME;  // add missing assert
  FIXME;  // add missing assert

  if (rv_a.get_type() != mem::Cell::Type::NUMBER ||
      rv_b.get_type() != mem::Cell::Type::NUMBER) {
    runtime::messages::error("not a number in arithmetic!");
    this->execution_finished = true;

    return;
  }

  lv =
      mem::Cell::for_number(do_operation(rv_a.get_number(), rv_b.get_number()));
}

void Cpu::execute_add(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_sub(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_mul(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_div(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_mod(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_umninus(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

}  // namespace alpha::vm::arch::cpu
