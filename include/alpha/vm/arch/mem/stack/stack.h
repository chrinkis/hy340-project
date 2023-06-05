#pragma once

#include <alpha/vm/arch/mem/cell.h>

#include <vector>

namespace alpha::vm::arch::mem::stack {

class Stack {
 public:
  using Index = unsigned;

 private:
  std::vector<Cell> data;

 public:
  Stack();

 public:
  size_t get_size() const;

 public:
  Cell& operator[](const Index index);
};

}  // namespace alpha::vm::arch::mem::stack
