#include <alpha/vm/arch/cpu/cpu.h>

#include <alpha/vm/runtime/messages/error.h>

#include <utils/warnings.h>

#include <cassert>

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
  mem::Cell& lv = this->translate_arg_to_cell(instr.get_result());

  const mem::Cell& table = this->translate_arg_to_cell(instr.get_arg_a());

  const mem::Cell& index =
      this->translate_arg_to_cell(instr.get_arg_b(), this->registers.arg_a);

  FIXME;  // add missing assertS

  lv.clear();
  lv = mem::Cell::for_nil();  // default value

  if (table.get_type() != mem::Cell::Type::TABLE) {
    runtime::messages::error("illdegal use of type `" +
                             table.get_type_as_string() + "` as table!");
    this->execution_finished = true;

    return;
  }

  if (index.get_type() == mem::Cell::Type::UNDEF ||
      index.get_type() == mem::Cell::Type::NIL) {
    runtime::messages::error("illegal type `" + table.get_type_as_string() +
                             "` for table-index!");
    this->execution_finished = true;

    return;
  }

  try {
    const mem::Cell& value = table.get_table().get_element(index);

    this->assign(lv, value);
  } catch (const std::invalid_argument& err) {
    runtime::messages::warning(err.what());
  }
}

void Cpu::execute_tablesetelem(const AbcInstruction& instr) {
  mem::Cell& table = this->translate_arg_to_cell(instr.get_result());

  const mem::Cell& index =
      this->translate_arg_to_cell(instr.get_arg_a(), this->registers.arg_a);

  const mem::Cell& value =
      this->translate_arg_to_cell(instr.get_arg_b(), this->registers.arg_b);

  FIXME;  // add missing assertS

  if (table.get_type() != mem::Cell::Type::TABLE) {
    runtime::messages::error("illdegal use of type `" +
                             table.get_type_as_string() + "` as table!");
    this->execution_finished = true;

    return;
  }

  if (index.get_type() == mem::Cell::Type::UNDEF ||
      index.get_type() == mem::Cell::Type::NIL) {
    runtime::messages::error("illegal type `" + table.get_type_as_string() +
                             "` for table-index!");
    this->execution_finished = true;

    return;
  }

  assert(table.get_type() == mem::Cell::Type::TABLE);

  table.get_table().set_element(index, value);
}

}  // namespace alpha::vm::arch::cpu
