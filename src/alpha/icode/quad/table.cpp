#include <alpha/icode/quad/table.h>

namespace alpha::icode::quad {

void Table::emit(const Quad& quad) {
  this->table.push_back(quad);
}

std::ostream& operator<<(std::ostream& os, const Table& qt) {
  os << std::left;

  for (auto quad : qt.table) {
    os << quad << std::endl;
  }

  return os << qt.table.size();
}

}  // namespace alpha::icode::quad
