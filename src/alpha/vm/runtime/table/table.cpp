#include <alpha/vm/runtime/table/table.h>

#include <alpha/vm/arch/mem/memory.h>

#include <utils/warnings.h>

#include <exception>

namespace alpha::vm::runtime::table {

Table::Table() : table(new InternalTable()) {}

Table Table::create() {
  return Table();
}

bool Table::operator==(const Table& other) const {
  return this->table.get() == other.table.get();
}

bool Table::operator<(const Table& other) const {
  return this->table.get() < other.table.get();
}

void Table::increase_counter() {
  WARN_EMPTY_FUNC_IMPL();
}

void Table::deccrease_counter() {
  WARN_EMPTY_FUNC_IMPL();
}

const Table::MemCell& Table::get_element(const MemCell& index) const
    noexcept(false) {
  try {
    return this->table->data.at(index);
  } catch (const std::out_of_range& err) {
    throw std::invalid_argument("Could'n find element with index `" +
                                index.to_string() + "`!");
  }
}

void Table::set_element(const MemCell& index, const MemCell& value) {
  if (value.get_type() == MemCell::Type::NIL) {
    this->table->data.erase(index);

    return;
  }

  try {
    this->table->data.at(index) = value;
  } catch (const std::out_of_range& err) {
    this->table->data.insert({index, value});
  }
}

Table::ConstIterator Table::begin() const {
  return this->table->data.begin();
}

Table::ConstIterator Table::end() const {
  return this->table->data.end();
}

}  // namespace alpha::vm::runtime::table
