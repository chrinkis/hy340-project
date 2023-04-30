#include <alpha/symbol/table_manager.h>

#include <alpha/symbol/function.h>
#include <alpha/symbol/variable.h>

#include <cassert>
#include <memory>
#include <string>
#include <unordered_set>

#define LIBRARY_FUNCTIONS (GET_LIBRARY_FUNCTIONS())
#define IS_LIBRAY_FUNCTION(name) \
  (LIBRARY_FUNCTIONS.find(name) != LIBRARY_FUNCTIONS.cend())

const std::unordered_set<std::string>& GET_LIBRARY_FUNCTIONS() {
  static const std::unordered_set<std::string> library_functions = {
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

TableManager::TableManager() : current_scope(0) {
  this->max_scope.push(this->current_scope);

  for (auto lib_func_name : LIBRARY_FUNCTIONS) {
    this->table.insert(Function(lib_func_name, 0, Symbol::Location(),
                                Symbol::Type::LIBRARY_FUNCTION));
  }

  assert(this->current_scope == 0);
  assert(this->max_scope.top() == this->current_scope);
  assert(this->max_scope.size() == 1);
}

void TableManager::increase_scope() {
  Symbol::Scope prev = this->current_scope;

  this->current_scope++;

  assert(this->current_scope > prev);
}

void TableManager::decrease_scope() {
  assert(this->current_scope > 0);

  Symbol::Scope prev = this->current_scope;

  this->table.hide(this->current_scope);
  this->current_scope--;

  assert(this->current_scope < prev);
}

TableManager::SearchResultOpt TableManager::search_for_visible_symbol(
    const std::string& name) const {
  auto result = this->table.lookup(name, this->current_scope, 0);

  if (!result) {
    assert(!IS_LIBRAY_FUNCTION(name));

    return SearchResultOpt();
  }

  Symbol::SharedPtr symbol = result->get_symbol();
  bool is_accesible = true;

  switch (symbol->get_type()) {
    case Symbol::Type::GLOBAL:
    case Symbol::Type::LOCAL:
    case Symbol::Type::FORMAL:
      is_accesible = symbol->get_scope() >= this->max_scope.top() ||
                     symbol->get_scope() == 0;
      break;
    case Symbol::Type::USER_FUNCTION:
    case Symbol::Type::LIBRARY_FUNCTION:
      is_accesible = true;
      break;
    default:
      assert(0);
  }

  return SearchResultOpt(SearchResult{
      .accessible = is_accesible,
      .symbol = symbol,
  });
}

TableManager::SearchResultOpt TableManager::search_for_visible_local_symbol(
    const std::string& name) const {
  auto result =
      this->table.lookup(name, this->current_scope, this->current_scope);

  if (!result) {
    return SearchResultOpt();
  }

  Symbol::SharedPtr symbol = result->get_symbol();

  return SearchResultOpt(SearchResult{
      .accessible = true,
      .symbol = symbol,
  });
}

TableManager::SearchResultOpt TableManager::search_for_visible_global_symbol(
    const std::string& name) const {
  auto result = this->table.lookup(name, 0, 0);

  if (!result) {
    return SearchResultOpt();
  }

  Symbol::SharedPtr symbol = result->get_symbol();

  return SearchResultOpt(SearchResult{
      .accessible = true,
      .symbol = symbol,
  });
}

bool TableManager::can_add_variable(const std::string& name) const {
  return !this->table.lookup(name, this->current_scope, 0);
}

Symbol::SharedPtr TableManager::add_variable(const std::string& name,
                                             const Symbol::Location& location) {
  assert(this->can_add_variable(name));

  using Type = Symbol::Type;

  Type type = this->current_scope ? Type::LOCAL : Type::GLOBAL;

  return this->table.insert(
      Variable(name, this->current_scope, location, type));
}

bool TableManager::can_add_local_variable(const std::string& name) const {
  return !IS_LIBRAY_FUNCTION(name) &&
         !this->table.lookup(name, this->current_scope, this->current_scope);
}

Symbol::SharedPtr TableManager::add_local_variable(
    const std::string& name,
    const Symbol::Location& location) {
  assert(this->can_add_local_variable(name));

  using Type = Symbol::Type;

  Type type = this->current_scope ? Type::LOCAL : Type::GLOBAL;

  return this->table.insert(
      Variable(name, this->current_scope, location, type));
}

bool TableManager::can_add_function(const std::string& name) const {
  return !IS_LIBRAY_FUNCTION(name) &&
         !this->table.lookup(name, this->current_scope, this->current_scope);
}

Symbol::SharedPtr TableManager::start_function(
    const Symbol::Location& location) {
  static unsigned int counter = 0;

  return this->start_function("$fn_" + std::to_string(counter++), location);
}

Symbol::SharedPtr TableManager::start_function(
    const std::string& name,
    const Symbol::Location& location) {
  assert(this->can_add_function(name));
  assert(!this->current_function);

  using Type = Symbol::Type;

  Function function =
      Function(name, this->current_scope, location, Type::USER_FUNCTION);

  Symbol::SharedPtr symbol = this->table.insert(function);

  this->current_function = std::dynamic_pointer_cast<Function>(symbol);
  this->increase_scope();
  this->max_scope.push(current_scope);

  assert(this->current_function);

  return symbol;
}

void TableManager::end_function() {
  assert(!this->current_function);  // last arg didn't passed
  assert(this->max_scope.size() > 1 && this->max_scope.top() != 0);

  this->max_scope.pop();

  assert(this->max_scope.size() > 1 && this->max_scope.top() != 0 ||
         this->max_scope.size() == 1 && this->max_scope.top() == 0);
}

bool TableManager::can_add_argument(const std::string& name) const {
  assert(this->current_function);

  return !IS_LIBRAY_FUNCTION(name) &&
         !this->table.lookup(name, this->current_scope, this->current_scope);
}

void TableManager::add_argument(const std::string& name,
                                const Symbol::Location& location) {
  assert(this->can_add_argument(name));
  assert(this->current_function);
  assert(this->current_function->get_type() == Symbol::Type::USER_FUNCTION);

  using Type = Symbol::Type;

  Symbol::SharedPtr arg = this->table.insert(
      Variable(name, this->current_scope, location, Type::FORMAL));

  assert(arg);

  this->current_function->add_arg(arg);
}

void TableManager::end_argument_list() {
  assert(this->current_function);

  this->current_scope--;
  this->current_function = Function::SharedPtr();
}

namespace alpha {
namespace symbol {

std::ostream& operator<<(std::ostream& os, const TableManager& manager) {
  os << manager.table;

  return os;
}

}  // namespace symbol
}  // namespace alpha
