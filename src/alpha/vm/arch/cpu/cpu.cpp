#include <alpha/vm/arch/cpu/cpu.h>
#include <alpha/vm/arch/mem/consts/consts.h>

#include <utils/warnings.h>

namespace alpha::vm::arch::cpu {

Cpu::Cpu(MemStack& memory_stack, ConstTable& const_table)
    : memory_stack(memory_stack), const_table(const_table) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_cycle() {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_assign(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_arithmetic(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
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

void Cpu::execute_boolean(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_and(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_or(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_not(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_jump(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_cmp_jump(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_jeq(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_jne(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_jle(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_jge(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_jlt(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_jgt(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_call(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_pushargs(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_funcenter(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_funcexit(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_newtable(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_tablegetelem(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_tablesetelem(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_nop(const AbcInstruction& instr) {
  WARN_EMPTY_FUNC_IMPL();
}

mem::Cell Cpu::translate_arg_to_cell(const AbcArg& arg) {
  WARN_EMPTY_FUNC_IMPL(mem::Cell());
}

mem::Cell Cpu::translate_arg_to_cell(const AbcArg& arg, mem::Cell& reg) {
  WARN_EMPTY_FUNC_IMPL(mem::Cell());
}

void Cpu::assign(mem::Cell& lval, const mem::Cell& rval) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::call_save_enviroment() {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::call_lib_func(const std::string& lib_func_name) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::call_lib_functor(const runtime::table::Table& table) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::push_table_arg(const runtime::table::Table& table) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::call_functor(const runtime::table::Table& table) {
  WARN_EMPTY_FUNC_IMPL();
}

std::optional<mem::Cell> table_get_elem(const runtime::table::Table& table,
                                        const mem::Cell& index) {
  WARN_EMPTY_FUNC_IMPL(std::optional<mem::Cell>());
}

void table_set_elem(runtime::table::Table& table,
                    const mem::Cell& index,
                    const mem::Cell& content) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::decrease_top() {
  WARN_EMPTY_FUNC_IMPL();
}

unsigned Cpu::get_enviroment_value(const MemStack::Index& index) {
  WARN_EMPTY_FUNC_IMPL(0);
}

unsigned get_total_actuals_from_stack() {
  WARN_EMPTY_FUNC_IMPL(0);
}

mem::Cell& get_actual_from_stack_at(unsigned i) {
  WARN_EMPTY_FUNC_IMPL(*(new mem::Cell));
}

}  // namespace alpha::vm::arch::cpu
