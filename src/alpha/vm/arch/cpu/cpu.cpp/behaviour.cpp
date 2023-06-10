#include <alpha/vm/arch/cpu/cpu.h>

#include <alpha/vm/arch/mem/consts/consts.h>
#include <alpha/vm/runtime/messages/error.h>

#include <utils/warnings.h>

#include <cassert>
#include <stdexcept>

#define NUM_ACTUALS_OFFSET +4
#define STACK_ENV_SIZE +4

namespace alpha::vm::arch::cpu {

Cpu::Cpu(Memory& mem, LibFunctions& lib_functions, unsigned total_globals)
    : execution_finished(false),
      pc(0),
      current_line(0),
      total_actuals(0),
      total_globals(total_globals),
      mem(mem),
      lib_functions(lib_functions) {
  this->registers.top = this->get_global_topsp();
  this->registers.topsp = this->registers.top;
}

void Cpu::execute_cycle() {
  if (this->execution_finished) {
    return;
  }

  if (this->pc == this->mem.code.get_size()) {
    this->execution_finished = true;
    return;
  }

  assert(this->pc < this->mem.code.get_size());

  AbcInstruction instr = this->mem.code.at(this->pc);

  if (instr.get_src_line()) {
    this->current_line = instr.get_src_line();
  }

  auto old_pc = this->pc;
  this->execute_instruction(instr);
  if (this->pc == old_pc) {
    this->pc++;
  }
}

bool Cpu::has_finished() const {
  return this->execution_finished;
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
    case abc::instruction::Opcode::FUNC_ENTER:
      this->execute_funcenter(instr);
      break;
    case abc::instruction::Opcode::FUNC_EXIT:
      this->execute_funcexit();
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
    default:
      assert(0);
  }
}

mem::Cell& Cpu::translate_arg_to_cell(const AbcArg& arg) {
  auto stack_size = this->mem.stack.get_size();
  const auto& topsp = this->registers.topsp;

  switch (arg.get_type()) {
    case abc::instruction::Arg::Type::GLOBAL: {
      return this->mem.stack[stack_size - 1 - arg.get_value()];
    }
    case abc::instruction::Arg::Type::LOCAL: {
      return this->mem.stack[topsp - arg.get_value()];
    }
    case abc::instruction::Arg::Type::FORMAL: {
      return this->mem.stack[topsp + STACK_ENV_SIZE + 1 + arg.get_value()];
    }
    case abc::instruction::Arg::Type::RET_VAL: {
      return this->registers.retval;
    }
    case abc::instruction::Arg::Type::NUMBER:
    case abc::instruction::Arg::Type::STRING:
    case abc::instruction::Arg::Type::BOOL:
    case abc::instruction::Arg::Type::NIL:
    case abc::instruction::Arg::Type::USER_FUNC:
    case abc::instruction::Arg::Type::LIB_FUNC:
    case abc::instruction::Arg::Type::LABEL:
    case abc::instruction::Arg::Type::EMPTY:
    default:
      assert(0);
  }
}

mem::Cell& Cpu::translate_arg_to_cell(const AbcArg& arg, mem::Cell& reg) {
#define RETURN_WITH(value) \
  {                        \
    reg = value;           \
    return reg;            \
  }

  switch (arg.get_type()) {
    case abc::instruction::Arg::Type::NUMBER: {
      RETURN_WITH(
          mem::Cell::for_number(this->mem.consts.number_at(arg.get_value())));
    }
    case abc::instruction::Arg::Type::STRING: {
      RETURN_WITH(
          mem::Cell::for_string(this->mem.consts.string_at(arg.get_value())));
    }
    case abc::instruction::Arg::Type::BOOL: {
      RETURN_WITH(mem::Cell::for_boolean(arg.get_value()));
    }
    case abc::instruction::Arg::Type::NIL: {
      RETURN_WITH(mem::Cell::for_nil());
    }
    case abc::instruction::Arg::Type::USER_FUNC: {
      RETURN_WITH(mem::Cell::for_user_func(
          this->mem.consts.user_func_at(arg.get_value())));
    }
    case abc::instruction::Arg::Type::LIB_FUNC: {
      RETURN_WITH(mem::Cell::for_lib_func(
          this->mem.consts.lib_func_name_at(arg.get_value())));
    }
    case abc::instruction::Arg::Type::GLOBAL:
    case abc::instruction::Arg::Type::LOCAL:
    case abc::instruction::Arg::Type::FORMAL:
    case abc::instruction::Arg::Type::RET_VAL: {
      return this->translate_arg_to_cell(arg);
    }
    case abc::instruction::Arg::Type::LABEL:
    case abc::instruction::Arg::Type::EMPTY:
    default:
      assert(0);
  }

#undef RETURN_WITH
}

void Cpu::assign(mem::Cell& lval, const mem::Cell& rval) {
  if (&lval == &rval) {
    return;  // Dangerous! See `lval.clear` few lines bellow
  }

  if (lval.get_type() == mem::Cell::Type::TABLE &&
      rval.get_type() == mem::Cell::Type::TABLE &&
      lval.get_table() == rval.get_table()) {
    return;  // no need to assign
  }

  if (rval.get_type() == mem::Cell::Type::UNDEF) {
    runtime::messages::warning("assign from `undef` content!");
  }

  lval.clear();

  lval = rval;

  if (lval.get_type() == mem::Cell::Type::TABLE) {
    lval.get_table()->increase_counter();
  }
}

void Cpu::call_save_enviroment() {
  using Opcode = abc::instruction::Opcode;

  this->push_enviroment_value(this->total_actuals);

  assert(this->mem.code.at(this->pc).get_opcode() == Opcode::CALL);

  this->push_enviroment_value(this->pc + 1);
  this->push_enviroment_value(this->registers.top + this->total_actuals + 2);
  this->push_enviroment_value(this->registers.topsp);
}

void Cpu::call_lib_func(const std::string& lib_func_name) {
  if (!this->lib_functions.supports_lib_func(lib_func_name)) {
    runtime::messages::error("unsupported lib func `" + lib_func_name +
                             "` called!");
    this->execution_finished = true;

    return;
  }

  this->call_save_enviroment();
  this->registers.topsp = this->registers.top;
  this->total_actuals = 0;

  try {
    this->lib_functions.call(lib_func_name, *this);
  } catch (const std::invalid_argument& err) {
    runtime::messages::error(err.what());
    this->execution_finished = true;

    return;
  }

  this->execute_funcexit();
}

void Cpu::call_lib_functor(const runtime::table::Table& table) {
  WARN_EMPTY_FUNC_IMPL();
}

void Cpu::push_table_arg(const runtime::table::Table& table) {
  this->mem.stack[this->registers.top] = mem::Cell::for_table(table);
  this->mem.stack[this->registers.top].get_table()->increase_counter();

  this->total_actuals++;

  this->decrease_top();
}

void Cpu::call_functor(const runtime::table::Table& table) {
  this->registers.result = mem::Cell::for_string("()");

  auto f = this->table_get_elem(table, this->registers.result);

  if (!f) {
    runtime::messages::error("in calling table: no `()` element found!");
    this->execution_finished = true;

    return;
  }

  assert(f.has_value());

  switch (f->get_type()) {
    case mem::Cell::Type::TABLE: {
      this->call_functor(f->get_table());

      break;
    }
    case mem::Cell::Type::USER_FUNC: {
      this->push_table_arg(table);
      this->call_save_enviroment();
      this->pc = f->get_user_func().get_address();

      assert(this->pc < this->mem.code.get_size());
      assert(this->mem.code.at(this->pc).get_opcode() ==
             abc::instruction::Opcode::FUNC_ENTER);

      break;
    }
    case mem::Cell::Type::NUMBER:
    case mem::Cell::Type::STRING:
    case mem::Cell::Type::BOOLEAN:
    case mem::Cell::Type::LIB_FUNC:
    case mem::Cell::Type::NIL:
    case mem::Cell::Type::UNDEF: {
      runtime::messages::error("in calling table: illegal `()` element value!");
      this->execution_finished = true;

      break;
    }
    default:
      assert(0);
  }
}

std::optional<mem::Cell> Cpu::table_get_elem(const runtime::table::Table& table,
                                             const mem::Cell& index) const {
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

unsigned Cpu::get_enviroment_value(const Memory::Stack::Index& index) const {
  assert(this->mem.stack[index].get_type() == mem::Cell::Type::NUMBER);

  unsigned val = static_cast<unsigned>(this->mem.stack[index].get_number());

  assert(this->mem.stack[index].get_number() == static_cast<double>(val));

  return val;
}

void Cpu::push_enviroment_value(unsigned value) {
  this->mem.stack[this->registers.top] = mem::Cell::for_number(value);
  this->decrease_top();
}

unsigned Cpu::get_total_actuals_from_stack() const {
  return this->get_enviroment_value(this->registers.topsp + NUM_ACTUALS_OFFSET);
}

mem::Cell& Cpu::get_actual_from_stack_at(unsigned i) const {
  assert(i < this->get_total_actuals_from_stack());

  return this->mem.stack[this->registers.topsp + STACK_ENV_SIZE + 1 + i];
}

const mem::stack::Stack::Index Cpu::get_global_topsp() const {
  return this->mem.stack.get_size() - this->total_globals - 1;
}

}  // namespace alpha::vm::arch::cpu
