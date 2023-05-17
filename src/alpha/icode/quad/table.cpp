#include <alpha/icode/quad/table.h>

#include <cassert>

namespace alpha::icode::quad {

void Table::emit(const Quad::Opcode& opcode,
                 const ExprOpt& result,
                 const ExprOpt& arg_a,
                 const ExprOpt& arg_b,
                 const QuadLabelOpt& address) {
  Quad quad(opcode, this->get_next_label());

  if (result) {
    quad.set_result(result.value());
  }

  if (arg_a) {
    quad.set_arg1(arg_a.value());
  }

  if (arg_b) {
    quad.set_arg2(arg_b.value());
  }

  if (address) {
    quad.set_label(address.value());
  }

  this->table.push_back(quad);

  assert(quad.get_line() == this->get_next_label() - 1);
}

Quad::Label Table::get_next_label() const {
  return 0;  // FIXME
}

std::ostream& operator<<(std::ostream& os, const Table& qt) {
  os << std::left;

  for (auto quad : qt.table) {
    os << quad << std::endl;
  }

  return os;
}

}  // namespace alpha::icode::quad
