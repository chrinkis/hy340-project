#include <alpha/vm/arch/cpu/cpu.h>

#include <alpha/vm/runtime/messages/error.h>

#include <utils/warnings.h>

namespace alpha::vm::arch::cpu {

void Cpu::execute_boolean(const AbcInstruction& instr,
                          const std::function<bool(bool, bool)>& do_operation) {
  mem::Cell& lv = this->translate_arg_to_cell(instr.get_result());

  mem::Cell& rv_a =
      this->translate_arg_to_cell(instr.get_arg_a(), this->registers.arg_a);

  mem::Cell& rv_b =
      this->translate_arg_to_cell(instr.get_arg_b(), this->registers.arg_b);

  if (rv_a.get_type() == mem::Cell::Type::UNDEF ||
      rv_b.get_type() == mem::Cell::Type::UNDEF) {
    runtime::messages::error("`undef` involved in boolean operation!");
    this->execution_finished = true;

    return;
  }

  lv = mem::Cell::for_boolean(do_operation(rv_a.to_bool(), rv_b.to_bool()));
}

void Cpu::execute_and(const AbcInstruction& instr) {
  this->execute_boolean(instr, [](auto a, auto b) { return a && b; });
}

void Cpu::execute_or(const AbcInstruction& instr) {
  this->execute_boolean(instr, [](auto a, auto b) { return a || b; });
}

void Cpu::execute_not(const AbcInstruction& instr) {
  mem::Cell& lv = this->translate_arg_to_cell(instr.get_result());

  mem::Cell& rv_a =
      this->translate_arg_to_cell(instr.get_arg_a(), this->registers.arg_a);

  if (rv_a.get_type() == mem::Cell::Type::UNDEF) {
    runtime::messages::error("`undef` involved in `not` operation!");
    this->execution_finished = true;

    return;
  }

  lv = mem::Cell::for_boolean(!rv_a.to_bool());
}

}  // namespace alpha::vm::arch::cpu
