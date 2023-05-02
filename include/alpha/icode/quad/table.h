#pragma once

#include <alpha/icode/quad/quad.h>

#include <vector>

namespace alpha::icode::quad {

class QuadTable {
 private:
  using Collection = std::vector<Quad>;

 public:
  static QuadTable& get() {
    static QuadTable quad_table;

    return quad_table;
  }

 private:
  Collection table;

 public:
  void emit(const Quad& quad);
};

}  // namespace alpha::icode::quad
