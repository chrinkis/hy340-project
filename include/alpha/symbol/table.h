#pragma once

#include <alpha/symbol/table_entry.h>
#include <alpha/symbol/table_key.h>

#include <alpha/symbol/symbol.h>

#include <functional>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>

namespace alpha {
namespace symbol {

class Table {
 private:
  using Entry = TableEntry;
  using Key = TableKey;
  using Pair = std::pair<Key, Entry>;

  using Map = std::unordered_multimap<Key, Entry>;

 private:
  Symbol::SharedPtr current_function;

 private:
  Symbol::Scope current_scope;
  std::stack<Symbol::Scope> max_scope;

  Map symbol_map;

  std::function<Symbol::Line()> get_current_line;

 private:
  Pair pairForVariable(const std::string& name, Symbol::Type type);
  Pair pairForFunction(const std::string& name);

 public:
  enum class SearchResult {
    NOT_FOUND,
    MUTABLE,
    UNMUTABLE,
  };

 public:
  Table(const std::function<Symbol::Line()>& get_current_line);

 public:
  void increase_scope();
  void decrease_scope();

  SearchResult search_for_visible_symbol(const std::string& name) const;
  SearchResult search_for_visible_local_symbol(const std::string& name) const;
  SearchResult search_for_visible_global_symbol(const std::string& name) const;

  bool can_add_variable(const std::string& name) const;
  void add_variable(const std::string& name);

  bool can_add_function(const std::string& name) const;
  void start_function();
  void start_function(const std::string& name);
  void end_function();

  void can_add_argument(const std::string& name) const;
  void add_argument(const std::string& name);
  void add_last_argument(const std::string& name);
};

}  // namespace symbol
}  // namespace alpha
