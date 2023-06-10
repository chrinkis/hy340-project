#include <alpha/vm/arch/cpu/cpu.h>

#include <alpha/vm/arch/mem/consts/user_func.h>
#include <alpha/vm/runtime/messages/error.h>

#include <utils/warnings.h>

#include <cassert>

#define SAVED_TOPSP_OFFSET +1
#define SAVED_TOP_OFFSET +2
#define SAVED_PC_OFFSET +3

namespace alpha::vm::arch::cpu {

void Cpu::execute_call(const AbcInstruction& instr) {
  mem::Cell& func =
      this->translate_arg_to_cell(instr.get_arg_a(), this->registers.arg_a);

  switch (func.get_type()) {
    case mem::Cell::Type::USER_FUNC: {
      using Opcode = abc::instruction::Opcode;

      this->call_save_enviroment();
      this->pc = func.get_user_func().get_address();

      assert(this->pc < this->mem.code.get_size());
      assert(this->mem.code.at(this->pc).get_opcode() == Opcode::FUNC_ENTER);

      break;
    }
    case mem::Cell::Type::STRING: {
      this->call_lib_func(func.get_string());

      break;
    }
    case mem::Cell::Type::LIB_FUNC: {
      this->call_lib_func(func.get_lib_func());

      break;
    }
    case mem::Cell::Type::TABLE: {
      this->call_functor(func.get_table());

      break;
    }
    case mem::Cell::Type::NUMBER:
    case mem::Cell::Type::BOOLEAN:
    case mem::Cell::Type::NIL:
    case mem::Cell::Type::UNDEF: {
      runtime::messages::error("call: cannot bind `" + func.to_string() +
                               "` to function!");
      this->execution_finished = true;

      break;
    }
    default:
      assert(0);
  }
}

void Cpu::execute_pushargs(const AbcInstruction& instr) {
  mem::Cell& arg =
      this->translate_arg_to_cell(instr.get_arg_a(), this->registers.arg_a);

  this->assign(this->mem.stack[this->registers.top], arg);
  this->total_actuals++;
  this->decrease_top();
}

void Cpu::execute_funcenter(const AbcInstruction& instr) {
  mem::Cell& cell_as_func =
      this->translate_arg_to_cell(instr.get_result(), this->registers.arg_a);

  mem::consts::UserFunc func = cell_as_func.get_user_func();

  assert(this->pc == func.get_address());

  /* callee actions: */
  this->total_actuals = 0;
  this->registers.topsp = this->registers.top;
  this->registers.top -= func.get_local_size();
}

void Cpu::execute_funcexit() {
  auto old_top = this->registers.top;

  this->registers.top =
      this->get_enviroment_value(this->registers.topsp + SAVED_TOP_OFFSET);

  this->pc =
      this->get_enviroment_value(this->registers.topsp + SAVED_PC_OFFSET);

  this->registers.topsp =
      this->get_enviroment_value(this->registers.topsp + SAVED_TOPSP_OFFSET);

  while (++old_top <= this->registers.top) {  // MUST skip the firest
    this->mem.stack[old_top].clear();
  }
}

}  // namespace alpha::vm::arch::cpu
