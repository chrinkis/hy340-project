#include <alpha/tcode/abc/table.h>

#include <utils/warnings.h>

namespace alpha::tcode::abc {

void Table::emit(const Instruction& instruction) {
  WARN_EMPTY_FUNC_IMPL()
}

void Table::parse_quad_table() {
  WARN_EMPTY_FUNC_IMPL();
}

Table::Instruction::SrcLine Table::get_next_label() const {
  return this->table.size();
}

}  // namespace alpha::tcode::abc
