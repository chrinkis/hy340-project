#pragma once

#include <memory>

namespace alpha::vm::runtime::table {

class _Table {
 public:
  using SharedPtr = std::shared_ptr<_Table>;

 private:
  _Table();

 public:
  static _Table::SharedPtr create();

  void increase_counter();
  void deccrease_counter();
};

using Table = _Table::SharedPtr;

}  // namespace alpha::vm::runtime::table
