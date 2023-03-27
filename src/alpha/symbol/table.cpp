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
  // TODO see if this function can be used in `can_add_variable`

  for (Variable::Scope scope = this->current_scope; scope <= 0; scope--) {
    Key key(name, scope);
    auto symbols = this->symbol_map.equal_range(key);

    for (auto symbol = symbols.first; symbol != symbols.second; symbol++) {
      if (symbol->second.get_is_active()) {
        switch (symbol->second.get_symbol()->get_type()) {
          case Symbol::Type::GLOBAL:
          case Symbol::Type::LOCAL:
          case Symbol::Type::FORMAL:
            return SearchResult::MUTABLE;
          case Symbol::Type::USER_FUNCTION:
          case Symbol::Type::LIBRARY_FUNCTION:
            return SearchResult::UNMUTABLE;  // TODO rename to `IMMUTABLE`
          default:
            assert(0);
        }
      }
    }
  }

  assert(LIBRARY_FUNCTIONS.find(name.c_str()) == LIBRARY_FUNCTIONS.cend());

  return SearchResult::NOT_FOUND;
}

Table::SearchResult Table::search_for_visible_local_symbol(
    const std::string& name) const {
  Key key(name, this->current_scope);

  auto symbols = this->symbol_map.equal_range(key);

  for (auto symbol = symbols.first; symbol != symbols.second; symbol++) {
    if (symbol->second.get_is_active()) {
      switch (symbol->second.get_symbol()->get_type()) {
        case Symbol::Type::GLOBAL:
        case Symbol::Type::LOCAL:
        case Symbol::Type::FORMAL:
          return SearchResult::MUTABLE;
        case Symbol::Type::USER_FUNCTION:
        case Symbol::Type::LIBRARY_FUNCTION:
          return SearchResult::UNMUTABLE;  // TODO rename to IMMUTABLE
        default:
          assert(0);
      }
    }
  }

  return SearchResult::NOT_FOUND;
}

Table::SearchResult Table::search_for_visible_global_symbol(
    const std::string& name) const {
  Key key(name, 0);

  auto symbols = this->symbol_map.equal_range(key);

  for (auto symbol = symbols.first; symbol != symbols.second; symbol++) {
    if (symbol->second.get_is_active()) {
      switch (symbol->second.get_symbol()->get_type()) {
        case Symbol::Type::GLOBAL:
        case Symbol::Type::LOCAL:
        case Symbol::Type::FORMAL:
          return SearchResult::MUTABLE;
        case Symbol::Type::USER_FUNCTION:
        case Symbol::Type::LIBRARY_FUNCTION:
          return SearchResult::UNMUTABLE;  // TODO rename to IMMUTABLE
        default:
          assert(0);
      }
    }
  }

  return SearchResult::NOT_FOUND;
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
  assert(this->can_add_variable(name));

  if (this->current_scope == 0) {  // global scope
    this->symbol_map.insert(pairForVariable(name, Symbol::Type::GLOBAL));
  } else if (this->current_scope > 0) {  // local scope
    this->symbol_map.insert(pairForVariable(name, Symbol::Type::LOCAL));
  } else {
    assert(0);  // No man's land ;)
  }
}

bool Table::can_add_local_variable(const std::string& name) const {
  if (LIBRARY_FUNCTIONS.find(name.c_str()) != LIBRARY_FUNCTIONS.cend()) {
    return false;  // Found library function
  }

  Key key(name, this->current_scope);
  auto symbols = this->symbol_map.equal_range(key);

  for (auto symbol = symbols.first; symbol != symbols.second; symbol++) {
    if (symbol->second.get_is_active()) {
      return false;  // Found an active homonymous-symbol in scope
    }
  }

  return true;
}

void Table::add_local_variable(const std::string& name) {
  assert(this->can_add_local_variable(name));

  if (this->current_scope == 0) {  // global scope
    this->symbol_map.insert(pairForVariable(name, Symbol::Type::GLOBAL));
  } else if (this->current_scope > 0) {  // local scope
    this->symbol_map.insert(pairForVariable(name, Symbol::Type::LOCAL));
  } else {
    assert(0);  // No man's land ;)
  }
}

bool Table::can_add_function(const std::string& name) const {
  ;  // FIXME
}

void Table::start_function() {
  static unsigned int counter = 0;

  this->start_function("$anonymous$" + std::to_string(counter++));
}

void Table::start_function(const std::string& name) {
  assert(this->can_add_function(name));
  assert(!this->current_function);

  Pair pair = pairForFunction(name);

  this->symbol_map.insert(pair);
  this->current_function = pair.second.get_symbol();
  this->current_scope++;
  this->max_scope.push(current_scope);
}

void Table::end_function() {
  assert(!this->current_function);  // last arg didn't passed
  assert(this->max_scope.size() > 1 && this->max_scope.top() != 0);

  this->max_scope.pop();

  assert(this->max_scope.size() > 1 && this->max_scope.top() != 0 ||
         this->max_scope.size() == 1 && this->max_scope.top() == 0);
}

bool Table::can_add_argument(const std::string& name) const {
  ;  // FIXME
}

void Table::add_argument(const std::string& name) {
  assert(this->can_add_argument(name));
  assert(this->current_function);

  Pair pair = pairForVariable(name, Symbol::Type::FORMAL);

  this->symbol_map.insert(pair);

  Function* current_function =
      dynamic_cast<Function*>(this->current_function.get());

  assert(current_function);
  assert(current_function->get_type() == Symbol::Type::USER_FUNCTION);

  current_function->add_arg(pair.second.get_symbol());
}

void Table::add_last_argument(const std::string& name) {
  assert(this->can_add_argument(name));
  assert(this->current_function);

  this->add_argument(name);
  this->current_scope--;
  this->current_function = Symbol::SharedPtr();
}
