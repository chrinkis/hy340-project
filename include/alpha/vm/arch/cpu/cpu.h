#pragma once

#include <alpha/vm/abc/instruction/arg.h>
#include <alpha/vm/abc/instruction/instruction.h>
#include <alpha/vm/arch/mem/cell.h>
#include <alpha/vm/arch/mem/code/table.h>
#include <alpha/vm/arch/mem/consts/consts.h>
#include <alpha/vm/arch/mem/stack/stack.h>
#include <alpha/vm/runtime/table/table.h>

#include <optional>

namespace alpha::vm::arch::cpu {

class Cpu {
 private:
  using MemStack = mem::stack::Stack;
  using AbcInstruction = abc::instruction::Instruction;
  using AbcArg = abc::instruction::Arg;
  using CodeTable = mem::code::Table;
  using ConstTable = mem::consts::Consts;

 public:
  // FIXME: should this be private?
  struct {
    mem::Cell result;
    mem::Cell arg_a;
    mem::Cell arg_b;
    mem::Cell retval;
    MemStack::Index top;
    MemStack::Index topsp;
  } registers;

 private:
  bool execution_finished;
  CodeTable::Index pc;
  AbcInstruction::SrcLine current_line;

  unsigned total_actuals;

  MemStack& memory_stack;
  ConstTable& const_table;
  CodeTable& code_table;

 public:
  Cpu(MemStack& memory_stack, ConstTable& const_table, CodeTable& code_table);
  void execute_cycle();

 private:
  void execute_assign(const AbcInstruction& instr);

  void execute_arithmetic(const AbcInstruction& instr);
  void execute_add(const AbcInstruction& instr);
  void execute_sub(const AbcInstruction& instr);
  void execute_mul(const AbcInstruction& instr);
  void execute_div(const AbcInstruction& instr);
  void execute_mod(const AbcInstruction& instr);

  void execute_umninus(const AbcInstruction& instr);

  void execute_boolean(const AbcInstruction& instr);
  void execute_and(const AbcInstruction& instr);
  void execute_or(const AbcInstruction& instr);

  void execute_not(const AbcInstruction& instr);

  void execute_jump(const AbcInstruction& instr);

  void execute_cmp_jump(const AbcInstruction& instr);
  void execute_jeq(const AbcInstruction& instr);
  void execute_jne(const AbcInstruction& instr);
  void execute_jle(const AbcInstruction& instr);
  void execute_jge(const AbcInstruction& instr);
  void execute_jlt(const AbcInstruction& instr);
  void execute_jgt(const AbcInstruction& instr);

  void execute_call(const AbcInstruction& instr);
  void execute_pushargs(const AbcInstruction& instr);
  void execute_funcenter(const AbcInstruction& instr);
  void execute_funcexit(const AbcInstruction& instr);

  void execute_newtable(const AbcInstruction& instr);
  void execute_tablegetelem(const AbcInstruction& instr);
  void execute_tablesetelem(const AbcInstruction& instr);

  void execute_nop(const AbcInstruction& instr);

 private:
  mem::Cell translate_arg_to_cell(const AbcArg& arg);
  mem::Cell translate_arg_to_cell(const AbcArg& arg, mem::Cell& reg);

  void assign(mem::Cell& lval, const mem::Cell& rval);

  void call_save_enviroment();
  void call_lib_func(const std::string& lib_func_name);
  void call_lib_functor(const runtime::table::Table& table);

  void push_table_arg(const runtime::table::Table& table);

  void call_functor(const runtime::table::Table& table);

  std::optional<mem::Cell> table_get_elem(const runtime::table::Table& table,
                                          const mem::Cell& index);

  void table_set_elem(runtime::table::Table& table,
                      const mem::Cell& index,
                      const mem::Cell& content);

  void decrease_top();
  unsigned get_enviroment_value(const MemStack::Index& index);

  unsigned get_total_actuals_from_stack();

  mem::Cell& get_actual_from_stack_at(unsigned i);
};

}  // namespace alpha::vm::arch::cpu
