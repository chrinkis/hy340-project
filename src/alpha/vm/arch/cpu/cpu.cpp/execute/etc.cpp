#include <alpha/vm/arch/cpu/cpu.h>

#include <utils/warnings.h>

namespace alpha::vm::arch::cpu {

void Cpu::execute_assign(const AbcInstruction& instr) {
  mem::Cell& lv = this->translate_arg_to_cell(instr.get_result());
  mem::Cell& rv =
      this->translate_arg_to_cell(instr.get_arg_a(), this->registers.arg_a);

  FIXME;  // add missing assertions for vl
  FIXME;  // add missing assertions for rv

  if (&rv == &this->registers.retval &&
      rv.get_type() == mem::Cell::Type::UNDEF) {
    lv.clear();

    return;
  }

  this->assign(lv, rv);

  if (&rv == &this->registers.retval) {
    this->registers.retval.clear();
  }
}

void Cpu::execute_nop(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

}  // namespace alpha::vm::arch::cpu
