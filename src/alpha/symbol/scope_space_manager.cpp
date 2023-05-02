#include <alpha/symbol/scope_space_manager.h>

using namespace alpha::symbol;

Symbol::ScopeSpace ScopeSpaceManager::get_current_scope_space() {
  if (this->scope_space == 1) {
    return Symbol::ScopeSpace::GLOBAL_VAR;
  } else if (this->scope_space % 2 == 0) {
    return Symbol::ScopeSpace::FORMAL_ARG;
  } else {
    return Symbol::ScopeSpace::FUNCTION_LOCAL;
  }

  assert(0);
}

Symbol::Offset ScopeSpaceManager::get_current_scope_offset() {
  switch (get_current_scope_space()) {
    case Symbol::ScopeSpace::GLOBAL_VAR:
      return this->ofsset.global_var;
    case Symbol::ScopeSpace::FORMAL_ARG:
      return this->ofsset.formal_arg;
    case Symbol::ScopeSpace::FUNCTION_LOCAL:
      return this->ofsset.function_local;
    default:
      assert(0);
  }

  assert(0);
}

void ScopeSpaceManager::increase_current_scope_offset() {
  switch (get_current_scope_space()) {
    case Symbol::ScopeSpace::GLOBAL_VAR:
      this->ofsset.global_var++;
      break;
    case Symbol::ScopeSpace::FORMAL_ARG:
      this->ofsset.formal_arg++;
      break;
    case Symbol::ScopeSpace::FUNCTION_LOCAL:
      this->ofsset.function_local++;
      break;
    default:
      assert(0);
  }

  assert(0);
}

void ScopeSpaceManager::enter_scope_space() {
  this->scope_space++;
}

void ScopeSpaceManager::exit_scope_space() {
  assert(this->scope_space > 1);

  this->scope_space--;
}
