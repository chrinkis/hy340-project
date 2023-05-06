#pragma once

#define quadTable (alpha::icode::quad::Table::get())

#include <alpha/icode/quad/quad.h>

#include <vector>

namespace alpha::icode::quad {

class Table {
 private:
  using Collection = std::vector<Quad>;

 public:
  static Table& get() {
    static Table quad_table;

    return quad_table;
  }

 private:
  Collection table;

 public:
  void emit(const Quad& quad);
};

}  // namespace alpha::icode::quad
