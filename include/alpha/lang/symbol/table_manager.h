#pragma once

#define symTable (alpha::symbol::TableManager::get())

#include <alpha/lang/symbol/function.h>
#include <alpha/lang/symbol/scope_space_manager.h>
#include <alpha/lang/symbol/symbol.h>
#include <alpha/lang/symbol/table.h>

#include <optional>
#include <ostream>
#include <stack>

namespace alpha {
namespace symbol {

class TableManager {
 public:
  static TableManager& get() {
    static TableManager table_manager;

    return table_manager;
  }

 public:
  struct SearchResult {
    bool accessible;

    Symbol::SharedPtr symbol;
  };

  using SearchResultOpt = std::optional<SearchResult>;
  using Counter = unsigned int;

 private:
  Table table;

  std::stack<Function::SharedPtr> current_function;

  Symbol::Scope current_scope;
  std::stack<Symbol::Scope> max_scope;

  std::stack<Counter> temp_var_counter;

  ScopeSpaceManager scope_space_manager;

 public:
  TableManager();

 public:
  void increase_scope();
  void decrease_scope();

 public:
  SearchResultOpt search_for_visible_symbol(const std::string& name) const;

  SearchResultOpt search_for_visible_local_symbol(
      const std::string& name) const;

  SearchResultOpt search_for_visible_global_symbol(
      const std::string& name) const;

  bool can_add_variable(const std::string& name) const;

  Symbol::SharedPtr add_variable(const std::string& name,
                                 const Symbol::Location& location);

  bool can_add_local_variable(const std::string& name) const;

  Symbol::SharedPtr add_local_variable(const std::string& name,
                                       const Symbol::Location& location);

  Symbol::SharedPtr new_temp_variable();

  void reset_temp_variables();

  bool can_add_function(const std::string& name) const;

  Symbol::SharedPtr start_function(const Symbol::Location& location,
                                   const Function::Iaddress& iaddress);

  Symbol::SharedPtr start_function(const std::string& name,
                                   const Symbol::Location& location,
                                   const Function::Iaddress& iaddress);

  void end_function();

  bool can_add_argument(const std::string& name) const;

  void add_argument(const std::string& name, const Symbol::Location& location);

  void end_argument_list();

  bool is_in_func_def() const;

 private:
  std::string new_temp_variable_name();

 public:
  friend std::ostream& operator<<(std::ostream& os,
                                  const TableManager& manager);
};

}  // namespace symbol
}  // namespace alpha
