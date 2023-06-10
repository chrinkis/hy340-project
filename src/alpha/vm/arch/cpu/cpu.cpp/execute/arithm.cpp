#include <alpha/vm/arch/cpu/cpu.h>

#include <alpha/vm/runtime/messages/error.h>

#include <utils/warnings.h>

namespace alpha::vm::arch::cpu {

void Cpu::execute_arithmetic(
    const AbcInstruction& instr,
    const std::function<double(double, double)>& do_operation,
    bool extra_division_checks) {
  mem::Cell& lv = this->translate_arg_to_cell(instr.get_result());
  mem::Cell& rv_a =
      this->translate_arg_to_cell(instr.get_arg_a(), this->registers.arg_a);
  mem::Cell& rv_b =
      this->translate_arg_to_cell(instr.get_arg_b(), this->registers.arg_b);

  FIXME;  // add missing assert
  FIXME;  // add missing assert

  if (rv_a.get_type() != mem::Cell::Type::NUMBER ||
      rv_b.get_type() != mem::Cell::Type::NUMBER) {
    runtime::messages::error("not a number in arithmetic!");
    this->execution_finished = true;

    return;
  }

  if (extra_division_checks && rv_b.get_number() == 0) {
    runtime::messages::error("can not devide with zero!");
    this->execution_finished = true;

    return;
  }

  lv =
      mem::Cell::for_number(do_operation(rv_a.get_number(), rv_b.get_number()));
}

void Cpu::execute_add(const AbcInstruction& instr) {
  execute_arithmetic(instr, [](auto a, auto b) { return a + b; });
}

void Cpu::execute_sub(const AbcInstruction& instr) {
  execute_arithmetic(instr, [](auto a, auto b) { return a - b; });
}

void Cpu::execute_mul(const AbcInstruction& instr) {
  execute_arithmetic(instr, [](auto a, auto b) { return a * b; });
}

void Cpu::execute_div(const AbcInstruction& instr) {
  execute_arithmetic(
      instr, [](auto a, auto b) { return a / b; }, true);
}

void Cpu::execute_mod(const AbcInstruction& instr) {
  execute_arithmetic(
      instr,
      [](auto a, auto b) {
        return static_cast<unsigned>(a) % static_cast<unsigned>(b);
      },
      true);
}

void Cpu::execute_umninus(const AbcInstruction& instr) {
  mem::Cell& lv = this->translate_arg_to_cell(instr.get_result());
  mem::Cell& rv =
      this->translate_arg_to_cell(instr.get_arg_a(), this->registers.arg_a);

  FIXME;  // should I assert sth?

  if (rv.get_type() != mem::Cell::Type::NUMBER) {
    runtime::messages::error("not a number in unary `-` operator!");
    this->execution_finished = true;

    return;
  }

  lv = mem::Cell::for_number(-rv.get_number());
}

}  // namespace alpha::vm::arch::cpu
