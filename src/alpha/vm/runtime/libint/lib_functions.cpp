#include <alpha/vm/runtime/libint/lib_functions.h>

#include <utils/warnings.h>

#include <cassert>

namespace alpha::vm::runtime::libint {

LibFunctions::LibFunctions() {
  WARN_EMPTY_FUNC_IMPL();
}

LibFunctions::LibFunctions() : lib_funcs{} {}

void LibFunctions::call(const std::string& func_name, const Cpu& cpu) {
  auto pair = this->lib_funcs.find(func_name);

  assert(pair != this->lib_funcs.end());
  assert(pair->first == func_name);

  pair->second(cpu);
}

bool LibFunctions::supports_lib_func(const std::string& func_name) const {
  return this->lib_funcs.find(func_name) != this->lib_funcs.end();
}

}  // namespace alpha::vm::runtime::libint
