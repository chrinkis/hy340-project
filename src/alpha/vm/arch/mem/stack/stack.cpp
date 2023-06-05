#include <alpha/vm/arch/mem/stack/stack.h>

#include <utils/warnings.h>

namespace alpha::vm::arch::mem::stack {

Stack::Stack() {
  WARN_EMPTY_FUNC_IMPL();
}

size_t Stack::get_size() const {
  WARN_EMPTY_FUNC_IMPL(0);
}

Cell& Stack::operator[](const Index index) {
  WARN_EMPTY_FUNC_IMPL((data.emplace_back(), data.at(0)));
}

}  // namespace alpha::vm::arch::mem::stack
