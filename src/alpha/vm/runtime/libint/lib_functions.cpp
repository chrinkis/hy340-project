#include <alpha/vm/runtime/libint/lib_functions.h>

#include <alpha/vm/arch/cpu/cpu.h>

#include <utils/warnings.h>

#include <cassert>
#include <iostream>
#include <stdexcept>

namespace alpha::vm::runtime::libint {

static void lib_print(const arch::cpu::Cpu& cpu) noexcept(false) {
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

LibFunctions::LibFunctions()
    : lib_funcs{
          {"print", lib_print},
      } {}

void LibFunctions::call(const std::string& func_name,
                        const Cpu& cpu) noexcept(false) {
  auto pair = this->lib_funcs.find(func_name);

  assert(pair != this->lib_funcs.end());
  assert(pair->first == func_name);

  pair->second(cpu);
}

bool LibFunctions::supports_lib_func(const std::string& func_name) const {
  return this->lib_funcs.find(func_name) != this->lib_funcs.end();
}

}  // namespace alpha::vm::runtime::libint
