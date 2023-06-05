#include <alpha/vm/arch/mem/code/table.h>

#include <utils/warnings.h>

namespace alpha::vm::arch::mem::code {

void Table::emit(const Instruction& instruction) {
  WARN_EMPTY_FUNC_IMPL();
}

size_t Table::get_size() const {
  WARN_EMPTY_FUNC_IMPL(0);
}

Table::Instruction::SrcLine Table::get_next_label() const {
  WARN_EMPTY_FUNC_IMPL(0);
}

Table::ConstIterator Table::begin() const {
  return this->table.begin();
}

Table::ConstIterator Table::end() const {
  return this->table.end();
}

}  // namespace alpha::vm::arch::mem::code
