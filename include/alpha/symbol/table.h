#pragma once

#include <functional>
#include <stack>
#include <string>

namespace alpha {
namespace symbol {

class Table {
 private:
  std::stack<int> max_scope;

 public:
  Table(const std::function<unsigned int()>& get_current_line);

 public:
  void increase_scope();
  void decrease_scope();

  bool symbol_is_visible(const std::string& name) const;

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
