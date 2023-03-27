#include <alpha/symbol/table.h>

#include <alpha/symbol/function.h>
#include <alpha/symbol/variable.h>

#include <cassert>
#include <string>
#include <unordered_set>
#include <utility>

static const std::unordered_set<const char*> LIBRARY_FUNCTIONS = {
    "print",
    "input",
    "objectmemberkeys",
    "objecttotalmembers",
    "objectcopy",
    "totalarguments",
    "argument",
    "typeof",
    "strtonum",
    "sqrt",
    "cos",
    "sin",
};

using namespace alpha::symbol;

Table::Pair Table::pairForVariable(const std::string& name, Symbol::Type type) {
  assert(type == Symbol::Type::GLOBAL || type == Symbol::Type::FORMAL ||
         type == Symbol::Type::LOCAL);

  Entry entry(
      new Variable(name, this->current_scope, this->get_current_line(), type));
  Key key(entry.get_symbol()->get_name(), entry.get_symbol()->get_scope());

  Pair pair(key, entry);

  assert(pair.second.get_symbol()->get_name() == name);
  assert(pair.second.get_symbol()->get_type() == type);
  assert(pair.second.get_symbol()->get_scope() == this->current_scope);
  assert(pair.second.get_symbol()->get_line() == this->get_current_line());
  assert(pair.first.get_symbol_name() == pair.second.get_symbol()->get_name());
  assert(pair.first.get_symbol_scope() ==
         pair.second.get_symbol()->get_scope());

  return pair;
}

Table::Pair Table::pairForFunction(const std::string& name) {
  ;  // FIXME
}

Table::Table(const std::function<Symbol::Line()>& get_current_line) {
  ;  // FIXME
}

void Table::increase_scope() {
  ;  // FIXME
}

void Table::decrease_scope() {
  ;  // FIXME
}

Table::SearchResult Table::search_for_visible_symbol(
    const std::string& name) const {
  ;  // FIXME
}

Table::SearchResult Table::search_for_visible_local_symbol(
    const std::string& name) const {
  ;  // FIXME
}

Table::SearchResult Table::search_for_visible_global_symbol(
    const std::string& name) const {
  ;  // FIXME
}

bool Table::can_add_variable(const std::string& name) const {
  ;  // FIXME
}

void Table::add_variable(const std::string& name) {
  ;  // FIXME
}

bool Table::can_add_function(const std::string& name) const {
  ;  // FIXME
}

void Table::start_function() {
  ;  // FIXME
}

void Table::start_function(const std::string& name) {
  ;  // FIXME
}

void Table::end_function() {
  ;  // FIXME
}

bool Table::can_add_argument(const std::string& name) const {
  ;  // FIXME
}

void Table::add_argument(const std::string& name) {
  ;  // FIXME
}

void Table::add_last_argument(const std::string& name) {
  ;  // FIXME
}
