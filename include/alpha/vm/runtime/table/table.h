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
    using Size = std::map<MemCell, MemCell>::size_type;

    std::map<MemCell, MemCell> data;
  };

 public:
  using Size = InternalTable::Size;

 private:
  InternalTable::SharedPtr table;

 private:
  Table();

 public:
  static Table create();

  bool operator==(const Table& other) const;
  bool operator<(const Table& other) const;

  void increase_counter();
  void deccrease_counter();

  Size get_size() const;

  const MemCell& get_element(const MemCell& index) const noexcept(false);
  void set_element(const MemCell& index, const MemCell& value);

 public: /* Iterators */
  using ConstIterator = std::map<MemCell, MemCell>::const_iterator;

  ConstIterator begin() const;
  ConstIterator end() const;
};

}  // namespace alpha::vm::runtime::table
