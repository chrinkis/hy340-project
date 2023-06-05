#pragma once

#include <alpha/lang/symbol/symbol.h>

#include <cassert>
#include <stack>

namespace alpha::symbol {

class ScopeSpaceManager {
 private:
  using Counter = unsigned;

 private:
  struct {
    Symbol::Offset global_var;
    Symbol::Offset formal_arg;
    std::stack<Symbol::Offset> function_local;
  } ofsset = {0, 0};

  Counter scope_space = 1;

 public:
  ScopeSpaceManager();

  Symbol::ScopeSpace get_current_scope_space();
  Symbol::Offset get_current_scope_offset();
  void increase_current_scope_offset();
  void enter_scope_space();
  void exit_scope_space();
};

}  // namespace alpha::symbol
