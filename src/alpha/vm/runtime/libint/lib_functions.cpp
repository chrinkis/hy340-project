#include <alpha/vm/runtime/libint/lib_functions.h>

#include <utils/warnings.h>

namespace alpha::vm::runtime::libint {

LibFunctions::LibFunctions() {
  WARN_EMPTY_FUNC_IMPL();
}

void LibFunctions::load_lib_func(const std::string& func_name) {
  WARN_EMPTY_FUNC_IMPL();
}

void LibFunctions::call(const std::string& func_name) {
  WARN_EMPTY_FUNC_IMPL();
}

bool LibFunctions::supports_lib_func(const std::string& func_name) const {
  WARN_EMPTY_FUNC_IMPL(true);
}

}  // namespace alpha::vm::runtime::libint
