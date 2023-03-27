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
  ;  // FIXME
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
  for (Variable::Scope scope = this->current_scope; scope <= 0; scope--) {
    Key key(name, scope);
    auto symbols = this->symbol_map.equal_range(key);

    for (auto symbol = symbols.first; symbol != symbols.second; symbol++) {
      if (symbol->second.get_is_active()) {
        return false;  // Found an active homonymous-symbol in scope
      }
    }
  }

  assert(LIBRARY_FUNCTIONS.find(name.c_str()) == LIBRARY_FUNCTIONS.cend());

  return true;
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
