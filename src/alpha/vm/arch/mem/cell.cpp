#include <alpha/vm/arch/mem/cell.h>

#include <utils/warnings.h>

namespace alpha::vm::arch::mem {

Cell::Cell(const Type& type) {
  WARN_EMPTY_FUNC_IMPL();
}

Cell::Cell() {
  WARN_EMPTY_FUNC_IMPL();
}

Cell::Cell(const Cell& cell) {
  WARN_EMPTY_FUNC_IMPL();
}

Cell& Cell::operator=(const Cell& cell) {  // NOTE! returns itself
  WARN_EMPTY_FUNC_IMPL(*this);
}

std::string Cell::to_string() const {
  WARN_EMPTY_FUNC_IMPL(std::string("steve vai"));
}

bool Cell::to_bool() const {
  WARN_EMPTY_FUNC_IMPL(false);
}

void Cell::clear() {
  WARN_EMPTY_FUNC_IMPL();
}

Cell Cell::for_number(double number) {
  WARN_EMPTY_FUNC_IMPL(Cell());
}

Cell Cell::for_string(const std::string& string) {
  WARN_EMPTY_FUNC_IMPL(Cell());
}

Cell Cell::for_boolean(bool boolean) {
  WARN_EMPTY_FUNC_IMPL(Cell());
}

Cell Cell::for_table(const runtime::table::Table& table) {
  WARN_EMPTY_FUNC_IMPL(Cell());
}

Cell Cell::for_user_func(const consts::UserFunc& user_func) {
  WARN_EMPTY_FUNC_IMPL(Cell());
}

Cell Cell::for_lib_func(const std::string& func_name) {
  WARN_EMPTY_FUNC_IMPL(Cell());
}

Cell Cell::for_nil() {
  WARN_EMPTY_FUNC_IMPL(Cell());
}

Cell Cell::for_undef() {
  WARN_EMPTY_FUNC_IMPL(Cell());
}

Cell::Type Cell::get_type() const {
  return this->type;
}

std::string Cell::get_type_as_string() const {
  WARN_EMPTY_FUNC_IMPL(std::string("john petrucci"));
}

double Cell::get_number() const {
  WARN_EMPTY_FUNC_IMPL(0.);
}

std::string Cell::get_string() const {
  WARN_EMPTY_FUNC_IMPL(std::string("animals as leaders"));
}

bool Cell::get_boolean() const {
  WARN_EMPTY_FUNC_IMPL(true);
}

runtime::table::Table Cell::get_table() const {
  WARN_EMPTY_FUNC_IMPL(runtime::table::Table());
}

consts::UserFunc Cell::get_user_func() const {
  WARN_EMPTY_FUNC_IMPL(consts::UserFunc(0, "", 0));
}

std::string Cell::get_lib_func() const {
  WARN_EMPTY_FUNC_IMPL(std::string("king crimson"));
}

}  // namespace alpha::vm::arch::mem
