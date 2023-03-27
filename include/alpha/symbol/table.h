#pragma once

#include <alpha/symbol/symbol.h>

#include <functional>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

namespace alpha {
namespace symbol {

class Table {
 private:
  struct Entry {
    bool is_active;
    Symbol::SharedPtr symbol;
  };

  using Key = std::string;
  using Map = std::unordered_multimap<Key, Entry>;

 private:
  Symbol::Scope current_scope;
  std::stack<Symbol::Scope> max_scope;

  std::vector<Map> scope_list;

  std::function<Symbol::Line()> get_current_line;

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
