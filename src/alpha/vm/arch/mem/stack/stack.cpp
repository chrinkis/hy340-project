#include <alpha/vm/arch/mem/stack/stack.h>

#include <cassert>
#include <vector>

#define STACK_SIZE 4096

namespace alpha::vm::arch::mem::stack {

Stack::Stack() : data(std::vector<Cell>(STACK_SIZE)) {}

size_t Stack::get_size() const {
  return this->data.size();
}

Cell& Stack::operator[](const Index index) {
  assert(index < STACK_SIZE);

  return data.at(index);
}

}  // namespace alpha::vm::arch::mem::stack
