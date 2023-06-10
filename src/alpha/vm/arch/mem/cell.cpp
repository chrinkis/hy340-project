#include <alpha/vm/arch/mem/cell.h>

#include <alpha/vm/arch/mem/consts/consts.h>
#include <utils/warnings.h>

#include <cassert>
#include <sstream>
#include <utility>

#define INDEX_EMPTY 0
#define INDEX_NUMBER 1
#define INDEX_STRING 2
#define INDEX_BOOL 3
#define INDEX_TABLE 4
#define INDEX_USER_FUNC 5
#define INDEX_LIB_FUNC 6

namespace alpha::vm::arch::mem {

Cell::Cell() : type(Type::UNDEF), data(std::monostate()) {}

Cell::Cell(const Cell& cell) : type(cell.type), data(cell.data) {}

Cell& Cell::operator=(const Cell& cell) {  // NOTE! returns itself
  this->type = cell.type;
  this->data = cell.data;
  return *this;
}

std::string Cell::to_string() const {
  switch (this->type) {
    case Type::NUMBER: {
      std::stringstream ss;
      ss << this->get_number();
      return ss.str();
    }

    case Type::STRING:
      return this->get_string();

    case Type::BOOLEAN:
      return this->get_boolean() ? "true" : "false";

    case Type::TABLE:
      // With index or key?
      FIXME;
      return "[]";

    case Type::USER_FUNC:
      return std::string("User Function->") + this->get_user_func().get_id();

    case Type::LIB_FUNC:
      return std::string("Library Function->") + this->get_lib_func();

    case Type::NIL:
      return "nil";

    case Type::UNDEF:
      return "undef";

    default:
      assert(0);
  }
}

bool Cell::to_bool() const {
  switch (this->type) {
    case Type::NUMBER:
      return !!this->get_number();

    case Type::STRING:
      return !this->get_string().empty();

    case Type::BOOLEAN:
      return this->get_boolean();

    case Type::TABLE:
    case Type::USER_FUNC:
    case Type::LIB_FUNC:
      return true;

    case Type::NIL:
      return false;

    case Type::UNDEF:
      assert(0);
      return false;

    default:
      assert(0);
  }
}

void Cell::clear() {
  if (this->type == Type::TABLE) {
    this->get_table()->deccrease_counter();
  }

  *this = Cell();
}

Cell Cell::for_number(double number) {
  Cell cell;

  cell.type = Type::NUMBER;
  cell.data = Variant(std::in_place_index_t<INDEX_NUMBER>(), number);

  return cell;
}

Cell Cell::for_string(const std::string& string) {
  Cell cell;

  cell.type = Type::STRING;
  cell.data = Variant(std::in_place_index_t<INDEX_STRING>(), string);

  return cell;
}

Cell Cell::for_boolean(bool boolean) {
  Cell cell;

  cell.type = Type::BOOLEAN;
  cell.data = Variant(std::in_place_index_t<INDEX_BOOL>(), boolean);

  return cell;
}

Cell Cell::for_table(const runtime::table::Table& table) {
  Cell cell;

  cell.type = Type::TABLE;
  cell.data = Variant(std::in_place_index_t<INDEX_TABLE>(), table);

  return cell;
}

Cell Cell::for_user_func(const consts::UserFunc& user_func) {
  Cell cell;

  cell.type = Type::USER_FUNC;
  cell.data = Variant(std::in_place_index_t<INDEX_USER_FUNC>(), user_func);

  return cell;
}

Cell Cell::for_lib_func(const std::string& func_name) {
  Cell cell;

  cell.type = Type::LIB_FUNC;
  cell.data = Variant(std::in_place_index_t<INDEX_LIB_FUNC>(), func_name);

  return cell;
}

Cell Cell::for_nil() {
  Cell cell;

  cell.type = Type::NIL;
  cell.data = Variant(std::in_place_index_t<INDEX_EMPTY>());

  return cell;
}

Cell Cell::for_undef() {
  Cell cell;

  cell.type = Type::UNDEF;
  cell.data = Variant(std::in_place_index_t<INDEX_EMPTY>());

  return cell;
}

Cell::Type Cell::get_type() const {
  return this->type;
}

std::string Cell::get_type_as_string() const {
  switch (this->type) {
    case Type::NUMBER:
      return "number";

    case Type::STRING:
      return "string";

    case Type::BOOLEAN:
      return "bool";

    case Type::TABLE:
      return "table";

    case Type::USER_FUNC:
      return "user_func";

    case Type::LIB_FUNC:
      return "lib_func";

    case Type::NIL:
      return "nil";

    case Type::UNDEF:
      return "undef";

    default:
      assert(0);
  }
}

double Cell::get_number() const {
  assert(this->data.index() == INDEX_NUMBER);
  return std::get<INDEX_NUMBER>(this->data);
}

std::string Cell::get_string() const {
  assert(this->data.index() == INDEX_STRING);
  return std::get<INDEX_STRING>(this->data);
}

bool Cell::get_boolean() const {
  assert(this->data.index() == INDEX_BOOL);
  return std::get<INDEX_BOOL>(this->data);
}

runtime::table::Table Cell::get_table() const {
  assert(this->data.index() == INDEX_TABLE);
  return std::get<INDEX_TABLE>(this->data);
}

consts::UserFunc Cell::get_user_func() const {
  assert(this->data.index() == INDEX_USER_FUNC);
  return std::get<INDEX_USER_FUNC>(this->data);
}

std::string Cell::get_lib_func() const {
  assert(this->data.index() == INDEX_LIB_FUNC);
  return std::get<INDEX_LIB_FUNC>(this->data);
}

}  // namespace alpha::vm::arch::mem
