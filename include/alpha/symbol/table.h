#pragma once

#define symTable (alpha::symbol::Table::get())

#include <alpha/symbol/table_entry.h>

#include <alpha/symbol/symbol.h>

#include <functional>
#include <ostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace alpha {
namespace symbol {

class Table {
 public:
  static Table& get() {
    static Table table;

    return table;
  }

 private:
  using Entry = TableEntry;
  using Key = std::string;
  using Pair = std::pair<Key, Entry>;

  using Map = std::unordered_multimap<Key, Entry>;

 private:
  Symbol::SharedPtr current_function;

 private:
  Symbol::Scope current_scope;
  std::stack<Symbol::Scope> max_scope;

  std::vector<Map> per_scope_map;

 private:
  Pair pairForVariable(const std::string& name,
                       Symbol::Type type,
                       const Symbol::Location& location);

  Pair pairForFunction(const std::string& name,
                       const Symbol::Location& location);

 public:
  struct SearchResult {
    bool accessible;

    enum {
      NOT_FOUND,
      MUTABLE,
      UNMUTABLE,
    } result;
  };

 public:
  Table();

 public:
  void increase_scope();
  void decrease_scope();

  SearchResult search_for_visible_symbol(const std::string& name) const;
  SearchResult search_for_visible_local_symbol(const std::string& name) const;
  SearchResult search_for_visible_global_symbol(const std::string& name) const;

  bool can_add_variable(const std::string& name) const;

  void add_variable(const std::string& name, const Symbol::Location& location);

  bool can_add_local_variable(const std::string& name) const;

  void add_local_variable(const std::string& name,
                          const Symbol::Location& location);

  bool can_add_function(const std::string& name) const;

  void start_function(const Symbol::Location& location);

  void start_function(const std::string& name,
                      const Symbol::Location& location);

  void end_function();

  bool can_add_argument(const std::string& name) const;

  void add_argument(const std::string& name, const Symbol::Location& location);

  void end_argument_list();

 public:
  friend std::ostream& operator<<(std::ostream& os, const Table& st);
};

}  // namespace symbol
}  // namespace alpha
