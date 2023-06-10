#include <alpha/vm/arch/cpu/cpu.h>

#include <utils/warnings.h>

using RunTimeTable = alpha::vm::runtime::table::Table;

namespace alpha::vm::arch::cpu {

void Cpu::execute_newtable(const AbcInstruction& instr) {
  mem::Cell& lv = this->translate_arg_to_cell(instr.get_result());

  FIXME;  // add missing assert

  lv.clear();

  lv = mem::Cell::for_table(RunTimeTable::create());
  lv.get_table().increase_counter();
}

void Cpu::execute_tablegetelem(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_tablesetelem(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

}  // namespace alpha::vm::arch::cpu
