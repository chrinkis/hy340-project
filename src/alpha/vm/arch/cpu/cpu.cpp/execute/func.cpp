#include <alpha/vm/arch/cpu/cpu.h>

#include <alpha/vm/runtime/messages/error.h>

#include <utils/warnings.h>

#include <cassert>

namespace alpha::vm::arch::cpu {

void Cpu::execute_call(const AbcInstruction& instr) {
  mem::Cell& func =
      this->translate_arg_to_cell(instr.get_result(), this->registers.arg_a);

  FIXME;  // add missing assertion

  switch (func.get_type()) {
    case mem::Cell::Type::USER_FUNC: {
      using Opcode = abc::instruction::Opcode;

      this->call_save_enviroment();
      this->pc = func.get_func_val();

      assert(this->pc < this->code_table.get_size());
      assert(this->code_table.at(this->pc).get_opcode() == Opcode::FUNC_ENTER);

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
      runtime::messages::warning("call: cannot bind `" + func.to_string() +
                                 "` to function!");
      this->execution_finished = true;

      break;
    }
    default:
      assert(0);
  }
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

}  // namespace alpha::vm::arch::cpu
