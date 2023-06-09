#include <alpha/vm/runtime/libint/lib_functions.h>

#include <alpha/vm/arch/cpu/cpu.h>
#include <alpha/vm/runtime/messages/error.h>

#include <utils/warnings.h>

#include <cassert>
#include <iostream>
#include <stdexcept>

#define NUM_ACTUALS_OFFSET +4
#define SAVED_TOPSP_OFFSET +1
// FIXME ^^^ defined in multiple files

namespace alpha::vm::runtime::libint {

void lib_print(arch::cpu::Cpu& _cpu) noexcept(false) {
  const auto& cpu = _cpu;

  auto n = cpu.get_total_actuals_from_stack();

  for (unsigned i = 0; i < n; i++) {
    const auto& cell = cpu.get_actual_from_stack_at(i);

    if (cell.get_type() == arch::mem::Cell::Type::UNDEF) {
      throw std::invalid_argument("Can't print an undefined value");
    }

    std::cout << cell.to_string();
    std::cout << std::endl;
  }
}

void lib_typeof(arch::cpu::Cpu& cpu) noexcept(false) {
  auto n = cpu.get_total_actuals_from_stack();

  if (n != 1) {
    throw std::invalid_argument(
        "`typeof` expected `1` argument, but recieved `" + std::to_string(n) +
        "`");
  }

  const auto& cell = cpu.get_actual_from_stack_at(0);

  if (cell.get_type() == arch::mem::Cell::Type::UNDEF) {
    throw std::invalid_argument("Can't use `typeof` with an undefined value");
  }

  cpu.registers.retval.clear();
  cpu.registers.retval = arch::mem::Cell::for_string(cell.get_type_as_string());
}

void lib_totalarguments(arch::cpu::Cpu& cpu) noexcept(false) {
  auto prev_topsp =
      cpu.get_enviroment_value(cpu.registers.topsp + SAVED_TOPSP_OFFSET);

  cpu.registers.retval.clear();

  if (prev_topsp == cpu.get_global_topsp()) {
    runtime::messages::warning("`totalarguments` called outside a function!");
    cpu.registers.retval = arch::mem::Cell::for_nil();

    return;
  }

  auto value = cpu.get_enviroment_value(prev_topsp + NUM_ACTUALS_OFFSET);
  cpu.registers.retval = arch::mem::Cell::for_number(value);
}

LibFunctions::LibFunctions()
    : lib_funcs{
          {"print", lib_print},
          {"typeof", lib_typeof},
          {"totalarguments", lib_totalarguments},
      } {}

void LibFunctions::call(const std::string& func_name,
                        Cpu& cpu) noexcept(false) {
  auto pair = this->lib_funcs.find(func_name);

  assert(pair != this->lib_funcs.end());
  assert(pair->first == func_name);

  pair->second(cpu);
}

bool LibFunctions::supports_lib_func(const std::string& func_name) const {
  return this->lib_funcs.find(func_name) != this->lib_funcs.end();
}

}  // namespace alpha::vm::runtime::libint
