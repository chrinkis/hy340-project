#include <alpha/vm/arch/mem/code/table.h>

#include <utils/warnings.h>

#include <cassert>

namespace alpha::vm::arch::mem::code {

void Table::emit(const Instruction& instruction) {
  assert(instruction.get_src_line() == this->get_next_label());

  this->table.push_back(instruction);
}

size_t Table::get_size() const {
  return this->table.size();
}

Table::Instruction::SrcLine Table::get_next_label() const {
  return this->get_size();
}

const Table::Instruction& Table::at(const Index& index) {
  return this->table.at(index);
}

Table::ConstIterator Table::begin() const {
  return this->table.begin();
}

Table::ConstIterator Table::end() const {
  return this->table.end();
}

}  // namespace alpha::vm::arch::mem::code
