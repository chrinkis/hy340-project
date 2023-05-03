#include <alpha/icode/quad/table.h>

namespace alpha::icode::quad {

void QuadTable::emit(const Quad& quad) {
  this->table.push_back(quad);
}

}  // namespace alpha::icode::quad
