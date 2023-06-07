#include <alpha/vm/arch/cpu/cpu.h>

#include <alpha/vm/arch/mem/consts/consts.h>
#include <alpha/vm/runtime/messages/error.h>

#include <utils/warnings.h>

#include <cassert>

namespace alpha::vm::arch::cpu {

Cpu::Cpu(MemStack& memory_stack, ConstTable& const_table, CodeTable& code_table)
    : memory_stack(memory_stack),
      const_table(const_table),
      code_table(code_table) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::execute_cycle() {
  if (this->execution_finished) {
    return;
  }

  if (this->pc == this->code_table.get_size()) {
    this->execution_finished = true;
    return;
  }

  assert(this->pc < this->code_table.get_size());

  AbcInstruction instr = this->code_table.at(this->pc);

  FIXME;  // assert opcode of instr is in range

  if (instr.get_src_line()) {
    this->current_line = instr.get_src_line();
    FIXME;  // at dev time, src line doesn't store line of quad
  }

  auto old_pc = this->pc;
  this->execute_instruction(instr);
  if (this->pc == old_pc) {
    this->pc++;
  }
}

void Cpu::execute_instruction(const AbcInstruction& instr) {
  switch (instr.get_opcode()) {
    case abc::instruction::Opcode::ASSIGN:
      this->execute_assign(instr);
      break;
    case abc::instruction::Opcode::ADD:
      this->execute_add(instr);
      break;
    case abc::instruction::Opcode::SUB:
      this->execute_sub(instr);
      break;
    case abc::instruction::Opcode::MUL:
      this->execute_mul(instr);
      break;
    case abc::instruction::Opcode::DIV:
      this->execute_div(instr);
      break;
    case abc::instruction::Opcode::MOD:
      this->execute_mod(instr);
      break;
    case abc::instruction::Opcode::UMINUS:
      this->execute_umninus(instr);
      break;
    case abc::instruction::Opcode::CALL:
      this->execute_call(instr);
      break;
      break;
    case abc::instruction::Opcode::FUNC_ENTER:
      this->execute_funcenter(instr);
      break;
    case abc::instruction::Opcode::FUNC_EXIT:
      this->execute_funcexit(instr);
      break;
    case abc::instruction::Opcode::AND:
      this->execute_and(instr);
      break;
    case abc::instruction::Opcode::OR:
      this->execute_or(instr);
      break;
    case abc::instruction::Opcode::NOT:
      this->execute_not(instr);
      break;
    case abc::instruction::Opcode::JUMP:
      this->execute_jump(instr);
      break;
    case abc::instruction::Opcode::JEQ:
      this->execute_jeq(instr);
      break;
    case abc::instruction::Opcode::JNE:
      this->execute_jne(instr);
      break;
    case abc::instruction::Opcode::JGT:
      this->execute_jgt(instr);
      break;
    case abc::instruction::Opcode::JLT:
      this->execute_jlt(instr);
      break;
    case abc::instruction::Opcode::JGE:
      this->execute_jge(instr);
      break;
    case abc::instruction::Opcode::JLE:
      this->execute_jle(instr);
      break;
    case abc::instruction::Opcode::NEW_TABLE:
      this->execute_newtable(instr);
      break;
    case abc::instruction::Opcode::TABLE_GET_ELEM:
      this->execute_tablegetelem(instr);
      break;
    case abc::instruction::Opcode::TABLE_SET_ELEM:
      this->execute_tablesetelem(instr);
      break;
    case abc::instruction::Opcode::PUSH_ARG:
      this->execute_pushargs(instr);
      break;
    case abc::instruction::Opcode::NOP:
      this->execute_nop(instr);
      break;
  }
}

mem::Cell& Cpu::translate_arg_to_cell(const AbcArg& arg) {
  WARN_EMPTY_FUNC_IMPL(this->memory_stack[0]);
}

mem::Cell& Cpu::translate_arg_to_cell(const AbcArg& arg, mem::Cell& reg) {
  WARN_EMPTY_FUNC_IMPL(reg);
}

void Cpu::assign(mem::Cell& lval, const mem::Cell& rval) {
  FIXME;  // check if they are the same cells

  FIXME;  // check if they are the same tables

  if (rval.get_type() == mem::Cell::Type::UNDEF) {
    runtime::messages::warning("assign from `undef` content!");
  }

  lval = rval;

  if (lval.get_type() == mem::Cell::Type::STRING) {
    FIXME;  // Nothing to do, right?
  } else if (lval.get_type() == mem::Cell::Type::TABLE) {
    lval.get_table()->increase_counter();
  }
}

void Cpu::call_save_enviroment() {
  using Opcode = abc::instruction::Opcode;

  this->push_enviroment_value(this->total_actuals);

  assert(this->code_table.at(this->pc).get_opcode() == Opcode::CALL);

  this->push_enviroment_value(this->pc + 1);
  this->push_enviroment_value(this->registers.top + this->total_actuals + 2);
  this->push_enviroment_value(this->registers.topsp);
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
  this->registers.result = mem::Cell::for_string("()");

  auto f = this->table_get_elem(table, this->registers.result);

  if (!f) {
    runtime::messages::error("in calling table: no `()` element found!");
    FIXME;  // should `this->execution_finished = true;` here?

  } else if (f->get_type() == mem::Cell::Type::TABLE) {
    this->call_functor(f->get_table());

  } else if (f->get_type() == mem::Cell::Type::USER_FUNC) {
    this->push_table_arg(table);
    this->call_save_enviroment();
    this->pc =
        this->const_table.user_func_at(f->get_func_index()).get_address();

    assert(this->pc < this->code_table.get_size());
    assert(this->code_table.at(this->pc).get_opcode() ==
           abc::instruction::Opcode::FUNC_ENTER);

  } else {
    runtime::messages::error("in calling table: illegal `()` element value!");
    FIXME;  // should `this->execution_finished = true;` here?
  }
}

std::optional<mem::Cell> Cpu::table_get_elem(const runtime::table::Table& table,
                                             const mem::Cell& index) {
  WARN_EMPTY_FUNC_IMPL(std::optional<mem::Cell>());
}

void Cpu::table_set_elem(runtime::table::Table& table,
                         const mem::Cell& index,
                         const mem::Cell& content) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::decrease_top() {
  if (!this->registers.top) {
    runtime::messages::error("stack overflow");
    this->execution_finished = true;

    return;
  }

  this->registers.top--;
}

unsigned Cpu::get_enviroment_value(const MemStack::Index& index) {
  assert(this->memory_stack[index].get_type() == mem::Cell::Type::NUMBER);
  FIXME;  // ^^^ `=` or `==` (see page 23 in lecture for vm)

  unsigned val = (unsigned)this->memory_stack[index].get_number();
  FIXME;  // ^^^ use c-style cast?

  assert(this->memory_stack[index].get_number() == (double)val);
  FIXME;  // ^^^ use c-style cast?

  return val;
}

void Cpu::push_enviroment_value(unsigned value) {
  this->memory_stack[this->registers.top] = mem::Cell::for_number(value);
  this->decrease_top();
}

unsigned get_total_actuals_from_stack() {
  WARN_EMPTY_FUNC_IMPL(0);
}

mem::Cell& get_actual_from_stack_at(unsigned i) {
  WARN_EMPTY_FUNC_IMPL(*(new mem::Cell));
}

}  // namespace alpha::vm::arch::cpu
