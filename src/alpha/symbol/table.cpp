#include <alpha/symbol/table.h>

#include <alpha/symbol/function.h>
#include <alpha/symbol/variable.h>

#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>

#define LIBRARY_FUNCTIONS (GET_LIBRARY_FUNCTIONS())

const std::unordered_set<const char*>& GET_LIBRARY_FUNCTIONS() {
  static const std::unordered_set<const char*> library_functions = {
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

  return library_functions;
}

using namespace alpha::symbol;

Table::Pair Table::pairForVariable(const std::string& name,
                                   Symbol::Type type,
                                   const Symbol::Location& location) {
  assert(type == Symbol::Type::GLOBAL && this->current_scope == 0 ||
         type == Symbol::Type::FORMAL && this->current_scope > 0 ||
         type == Symbol::Type::LOCAL && this->current_scope > 0);

  Entry entry(new Variable(name, this->current_scope, location, type));
  Key key(entry.get_symbol()->get_name(), entry.get_symbol()->get_scope());

  Pair pair(key, entry);

  assert(pair.second.get_symbol()->get_name() == name);
  assert(pair.second.get_symbol()->get_type() == type);
  assert(pair.second.get_symbol()->get_scope() == this->current_scope);
  assert(pair.first.get_symbol_name() == pair.second.get_symbol()->get_name());
  assert(pair.first.get_symbol_scope() ==
         pair.second.get_symbol()->get_scope());

  assert(pair.second.get_symbol()->get_location().begin.line ==
         location.begin.line);
  assert(pair.second.get_symbol()->get_location().begin.column ==
         location.begin.column);
  assert(pair.second.get_symbol()->get_location().end.line ==
         location.end.line);
  assert(pair.second.get_symbol()->get_location().end.column ==
         location.end.column);

  return pair;
}

Table::Pair Table::pairForFunction(const std::string& name,
                                   const Symbol::Location& location) {
  Entry entry(new Function(name, this->current_scope, location,
                           Symbol::Type::USER_FUNCTION));
  Key key(entry.get_symbol()->get_name(), entry.get_symbol()->get_scope());

  Pair pair(key, entry);

  assert(pair.second.get_symbol()->get_name() == name);
  assert(pair.second.get_symbol()->get_type() == Symbol::Type::USER_FUNCTION);
  assert(pair.second.get_symbol()->get_scope() == this->current_scope);
  assert(pair.first.get_symbol_name() == pair.second.get_symbol()->get_name());
  assert(pair.first.get_symbol_scope() ==
         pair.second.get_symbol()->get_scope());

  assert(pair.second.get_symbol()->get_location().begin.line ==
         location.begin.line);
  assert(pair.second.get_symbol()->get_location().begin.column ==
         location.begin.column);
  assert(pair.second.get_symbol()->get_location().end.line ==
         location.end.line);
  assert(pair.second.get_symbol()->get_location().end.column ==
         location.end.column);

  return pair;
}

Table::Table() : current_scope(0) {
  this->max_scope.push(this->current_scope);

  for (const char* lib_func_name : LIBRARY_FUNCTIONS) {
    Key key(lib_func_name, 0);
    Entry entry(new Function(lib_func_name, 0, Symbol::Location(),
                             Symbol::Type::LIBRARY_FUNCTION));

    this->symbol_map.insert(Pair(key, entry));
  }

  assert(this->current_scope == 0);
  assert(this->max_scope.top() == this->current_scope);
  assert(this->max_scope.size() == 1);
  assert(this->symbol_map.size() == LIBRARY_FUNCTIONS.size());
}

void Table::increase_scope() {
  Symbol::Scope prev = this->current_scope;

  this->current_scope++;

  assert(this->current_scope > prev);
}

void Table::decrease_scope() {
  Symbol::Scope prev = this->current_scope;

  for (auto pair : this->symbol_map) {  // TODO slow peformance
    if (pair.second.get_symbol()->get_scope() == this->current_scope) {
      pair.second.deactivate();
    }
  }

  this->current_scope--;

  assert(this->current_scope < prev);
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

void Table::add_variable(const std::string& name,
                         const Symbol::Location& location) {
  assert(this->can_add_variable(name));

  if (this->current_scope == 0) {  // global scope
    this->symbol_map.insert(
        pairForVariable(name, Symbol::Type::GLOBAL, location));
  } else if (this->current_scope > 0) {  // local scope
    this->symbol_map.insert(
        pairForVariable(name, Symbol::Type::LOCAL, location));
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

void Table::add_local_variable(const std::string& name,
                               const Symbol::Location& location) {
  assert(this->can_add_local_variable(name));

  if (this->current_scope == 0) {  // global scope
    this->symbol_map.insert(
        pairForVariable(name, Symbol::Type::GLOBAL, location));
  } else if (this->current_scope > 0) {  // local scope
    this->symbol_map.insert(
        pairForVariable(name, Symbol::Type::LOCAL, location));
  } else {
    assert(0);  // No man's land ;)
  }
}

bool Table::can_add_function(const std::string& name) const {
  if (LIBRARY_FUNCTIONS.find(name.c_str()) != LIBRARY_FUNCTIONS.cend()) {
    return false;  // It's a library function
  }

  Key key(name, this->current_scope);
  auto symbols = this->symbol_map.equal_range(key);

  for (auto symbol = symbols.first; symbol != symbols.second; symbol++) {
    if (symbol->second.get_is_active()) {
      return false;  // Found an active homonymous-symbol in current scope
    }
  }

  return true;
}

void Table::start_function(const Symbol::Location& location) {
  static unsigned int counter = 0;

  this->start_function("$anonymous$" + std::to_string(counter++), location);
}

void Table::start_function(const std::string& name,
                           const Symbol::Location& location) {
  assert(this->can_add_function(name));
  assert(!this->current_function);

  Pair pair = pairForFunction(name, location);

  this->symbol_map.insert(pair);
  this->current_function = pair.second.get_symbol();
  this->current_scope++;
  this->max_scope.push(current_scope);

  assert(this->current_function);
}

void Table::end_function() {
  assert(!this->current_function);  // last arg didn't passed
  assert(this->max_scope.size() > 1 && this->max_scope.top() != 0);

  this->max_scope.pop();

  assert(this->max_scope.size() > 1 && this->max_scope.top() != 0 ||
         this->max_scope.size() == 1 && this->max_scope.top() == 0);
}

bool Table::can_add_argument(const std::string& name) const {
  assert(this->current_function);

  if (LIBRARY_FUNCTIONS.find(name.c_str()) != LIBRARY_FUNCTIONS.cend()) {
    return false;  // It's a library function
  }

  Key key(name, this->current_scope);
  auto symbols = this->symbol_map.equal_range(key);

  for (auto symbol = symbols.first; symbol != symbols.second; symbol++) {
    if (symbol->second.get_is_active()) {
      return false;  // Found an active homonymous-symbol in current scope
    }
  }

  return true;
}

void Table::add_argument(const std::string& name,
                         const Symbol::Location& location) {
  assert(this->can_add_argument(name));
  assert(this->current_function);

  Pair pair = pairForVariable(name, Symbol::Type::FORMAL, location);

  this->symbol_map.insert(pair);

  Function* current_function =
      dynamic_cast<Function*>(this->current_function.get());

  assert(current_function);
  assert(current_function->get_type() == Symbol::Type::USER_FUNCTION);

  current_function->add_arg(pair.second.get_symbol());
}

void Table::end_argument_list() {
  assert(this->current_function);

  this->current_scope--;
  this->current_function = Symbol::SharedPtr();
}

namespace alpha {
namespace symbol {

std::ostream& operator<<(std::ostream& os, const Table& st) {
  auto ident = [](int w = 26) { return std::setw(w); };

  os << std::left;

  os << "\x1B[42m";
  os << "\x1B[30m";

  for (auto pair : st.symbol_map) {
    Symbol::SharedPtr symbol = pair.second.get_symbol();

    os << ident();
    os << "\"" + symbol->get_name() + "\"";

    os << ident();
    switch (symbol->get_type()) {
      case Symbol::Type::GLOBAL:
        os << "[global variable]";
        break;
      case Symbol::Type::LOCAL:
        os << "[local variable]";
        break;
      case Symbol::Type::FORMAL:
        os << "[formal argument]";
        break;
      case Symbol::Type::USER_FUNCTION:
        os << "[user function]";
        break;
      case Symbol::Type::LIBRARY_FUNCTION:
        os << "[library function]";
        break;
      default:
        assert(0);
    }

    os << ident();
    std::stringstream location;
    location << "(location " << symbol->get_location() << ')';
    os << location.str();

    os << ident();
    os << "(scope " + std::to_string(symbol->get_scope()) + ')';

    os << std::endl;
  }

  os << "\033[0m\t\t";

  return os;
}

}  // namespace symbol
}  // namespace alpha
