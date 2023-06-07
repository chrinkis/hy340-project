#pragma once

#include <alpha/vm/abc/instruction/instruction.h>

#include <cstddef>
#include <vector>

namespace alpha::vm::arch::mem::code {

class Table {
 public:
  using Index = unsigned;

 private:
  using Instruction = abc::instruction::Instruction;

 private:
  using Collection = std::vector<Instruction>;

 private:
  Collection table;

 public:
  void emit(const Instruction& instruction);

  size_t get_size() const;

  Instruction::SrcLine get_next_label() const;

  const Instruction& at(const Index& index);

 public: /* Iterators */
  using ConstIterator = Collection::const_iterator;

  ConstIterator begin() const;
  ConstIterator end() const;
};

}  // namespace alpha::vm::arch::mem::code
