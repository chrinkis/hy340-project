#pragma once

#include <map>
#include <memory>

namespace alpha::vm::arch::mem {
class Cell;
}

namespace alpha::vm::runtime::table {

class Table {
 private:
  using MemCell = alpha::vm::arch::mem::Cell;

 private:
  struct InternalTable {
    using SharedPtr = std::shared_ptr<InternalTable>;

    std::map<MemCell, MemCell> data;
  };

 private:
  InternalTable::SharedPtr table;

 private:
  Table();

 public:
  static Table create();

  bool operator==(const Table& other) const;

  void increase_counter();
  void deccrease_counter();

  const MemCell& get_element(const MemCell& index) const noexcept(false);
  void set_element(const MemCell& index, const MemCell& value);
};

}  // namespace alpha::vm::runtime::table
