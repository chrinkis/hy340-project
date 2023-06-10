#pragma once

#include <alpha/vm/abc/instruction/arg.h>
#include <alpha/vm/abc/instruction/instruction.h>
#include <alpha/vm/arch/mem/cell.h>
#include <alpha/vm/arch/mem/memory.h>
#include <alpha/vm/runtime/libint/lib_functions.h>
#include <alpha/vm/runtime/table/table.h>

#include <functional>
#include <optional>

namespace alpha::vm::arch::cpu {

class Cpu {
  friend void runtime::libint::lib_print(arch::cpu::Cpu& _cpu) noexcept(false);
  friend void runtime::libint::lib_typeof(arch::cpu::Cpu& _cpu) noexcept(false);
  friend void runtime::libint::lib_argument(arch::cpu::Cpu& _cpu) noexcept(
      false);
  friend void runtime::libint::lib_totalarguments(
      arch::cpu::Cpu& _cpu) noexcept(false);

 private:
  using Memory = mem::Memory;
  using AbcInstruction = abc::instruction::Instruction;
  using AbcArg = abc::instruction::Arg;
  using LibFunctions = runtime::libint::LibFunctions;

 public:
  // FIXME: should this be private?
  struct {
    mem::Cell result;
    mem::Cell arg_a;
    mem::Cell arg_b;
    mem::Cell retval;
    Memory::Stack::Index top;
    Memory::Stack::Index topsp;
  } registers;

 private:
  bool execution_finished;
  Memory::Code::Index pc;
  AbcInstruction::SrcLine current_line;

  unsigned total_actuals;
  unsigned total_globals;

  Memory& mem;

  LibFunctions& lib_functions;

 public:
  Cpu(Memory& mem, LibFunctions& lib_functions, unsigned total_globals);

  void execute_cycle();
  bool has_finished() const;

 private:
  void execute_instruction(const AbcInstruction& instr);

  void execute_assign(const AbcInstruction& instr);

  void execute_arithmetic(
      const AbcInstruction& instr,
      const std::function<double(double, double)>& do_operation,
      bool extra_division_checks = false);

  void execute_add(const AbcInstruction& instr);
  void execute_sub(const AbcInstruction& instr);
  void execute_mul(const AbcInstruction& instr);
  void execute_div(const AbcInstruction& instr);
  void execute_mod(const AbcInstruction& instr);

  void execute_umninus(const AbcInstruction& instr);

  void execute_boolean(const AbcInstruction& instr,
                       const std::function<bool(bool, bool)>& do_operation);

  void execute_and(const AbcInstruction& instr);
  void execute_or(const AbcInstruction& instr);

  void execute_not(const AbcInstruction& instr);

  void execute_jump(const AbcInstruction& instr);

  void execute_cmp_jump(
      const AbcInstruction& instr,
      const std::function<bool(const mem::Cell&,
                               const mem::Cell&) noexcept(false)>& compare);

  void execute_jeq(const AbcInstruction& instr);
  void execute_jne(const AbcInstruction& instr);
  void execute_jle(const AbcInstruction& instr);
  void execute_jge(const AbcInstruction& instr);
  void execute_jlt(const AbcInstruction& instr);
  void execute_jgt(const AbcInstruction& instr);

  void execute_call(const AbcInstruction& instr);
  void execute_pushargs(const AbcInstruction& instr);
  void execute_funcenter(const AbcInstruction& instr);
  void execute_funcexit();

  void execute_newtable(const AbcInstruction& instr);
  void execute_tablegetelem(const AbcInstruction& instr);
  void execute_tablesetelem(const AbcInstruction& instr);

  void execute_nop(const AbcInstruction& instr);

 private:
  mem::Cell& translate_arg_to_cell(const AbcArg& arg);
  mem::Cell& translate_arg_to_cell(const AbcArg& arg, mem::Cell& reg);

  void assign(mem::Cell& lval, const mem::Cell& rval);

  void call_save_enviroment();
  void call_lib_func(const std::string& lib_func_name);

  void push_table_arg(const runtime::table::Table& table);

  void call_functor(const runtime::table::Table& table);

  void decrease_top();
  void push_enviroment_value(unsigned value);

  unsigned get_enviroment_value(const Memory::Stack::Index& index) const;
  unsigned get_total_actuals_from_stack() const;
  mem::Cell& get_actual_from_stack_at(unsigned i) const;
  const mem::stack::Stack::Index get_global_topsp() const;
};

}  // namespace alpha::vm::arch::cpu
