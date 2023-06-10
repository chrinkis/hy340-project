#include <alpha/vm/runtime/table/table.h>

#include <utils/warnings.h>

namespace alpha::vm::runtime::table {

Table::Table() {
  WARN_EMPTY_FUNC_IMPL();
}

Table::SharedPtr Table::create() {
  WARN_EMPTY_FUNC_IMPL(Table::SharedPtr());
}

bool Table::operator==(const Table& other) {
  WARN_EMPTY_FUNC_IMPL(false);
}

void Table::increase_counter() {
  WARN_EMPTY_FUNC_IMPL();
}

void Table::deccrease_counter() {
  WARN_EMPTY_FUNC_IMPL();
}

}  // namespace alpha::vm::runtime::table
