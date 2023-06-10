#include <alpha/vm/runtime/table/table.h>

#include <alpha/vm/arch/mem/memory.h>

#include <utils/warnings.h>

namespace alpha::vm::runtime::table {

Table::Table() {
  WARN_EMPTY_FUNC_IMPL();
}

Table Table::create() {
  WARN_EMPTY_FUNC_IMPL(Table());
}

bool Table::operator==(const Table& other) const {
  WARN_EMPTY_FUNC_IMPL(false);
}

void Table::increase_counter() {
  WARN_EMPTY_FUNC_IMPL();
}

void Table::deccrease_counter() {
  WARN_EMPTY_FUNC_IMPL();
}

const Table::MemCell& Table::get_element(const MemCell& index) const
    noexcept(false) {
  WARN_EMPTY_FUNC_IMPL(*(new MemCell));
}

void Table::set_element(const MemCell& index, const MemCell& value) {
  WARN_EMPTY_FUNC_IMPL();
}

}  // namespace alpha::vm::runtime::table
