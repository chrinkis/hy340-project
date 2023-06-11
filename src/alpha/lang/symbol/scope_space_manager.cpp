#include <alpha/lang/symbol/scope_space_manager.h>

#include <cassert>

#define CHECK_INVARIANTS \
  { assert(!this->ofsset.function_local.empty()); }

using namespace alpha::symbol;

ScopeSpaceManager::ScopeSpaceManager() {
  assert(this->ofsset.formal_arg == 0);
  assert(this->ofsset.global_var == 0);

  this->ofsset.function_local.push(0);

  CHECK_INVARIANTS
}

Symbol::ScopeSpace ScopeSpaceManager::get_current_scope_space() {
  CHECK_INVARIANTS

  if (this->scope_space == 1) {
    return Symbol::ScopeSpace::PROGRAM_VAR;
  } else if (this->scope_space % 2 == 0) {
    return Symbol::ScopeSpace::FORMAL_ARG;
  } else {
    return Symbol::ScopeSpace::FUNCTION_LOCAL;
  }

  assert(0);
}

Symbol::Offset ScopeSpaceManager::get_current_scope_offset() {
  CHECK_INVARIANTS

  switch (get_current_scope_space()) {
    case Symbol::ScopeSpace::PROGRAM_VAR:
      return this->ofsset.global_var;
    case Symbol::ScopeSpace::FORMAL_ARG:
      return this->ofsset.formal_arg;
    case Symbol::ScopeSpace::FUNCTION_LOCAL:
      return this->ofsset.function_local.top();
    default:
      assert(0);
      return -1;
  }

  assert(0);
}

void ScopeSpaceManager::increase_current_scope_offset() {
  CHECK_INVARIANTS

  switch (get_current_scope_space()) {
    case Symbol::ScopeSpace::PROGRAM_VAR:
      this->ofsset.global_var++;
      break;
    case Symbol::ScopeSpace::FORMAL_ARG:
      this->ofsset.formal_arg++;
      break;
    case Symbol::ScopeSpace::FUNCTION_LOCAL:
      this->ofsset.function_local.top()++;
      break;
    default:
      assert(0);
  }

  CHECK_INVARIANTS
}

void ScopeSpaceManager::enter_scope_space() {
  CHECK_INVARIANTS

  this->scope_space++;

  switch (this->get_current_scope_space()) {
    case Symbol::ScopeSpace::PROGRAM_VAR:
      assert(0);  // No man's land
      break;
    case Symbol::ScopeSpace::FORMAL_ARG:
      this->ofsset.formal_arg = 0;
      break;
    case Symbol::ScopeSpace::FUNCTION_LOCAL:
      this->ofsset.function_local.push(0);
      break;
    default:
      assert(0);
  }

  CHECK_INVARIANTS
}

void ScopeSpaceManager::exit_scope_space() {
  CHECK_INVARIANTS
  assert(this->scope_space > 1);

  switch (this->get_current_scope_space()) {
    case Symbol::ScopeSpace::PROGRAM_VAR:
      assert(0);
    case Symbol::ScopeSpace::FORMAL_ARG:
      this->ofsset.formal_arg = 0;
      break;
    case Symbol::ScopeSpace::FUNCTION_LOCAL:
      this->ofsset.function_local.pop();
      break;
    default:
      break;
  }

  this->scope_space--;

  CHECK_INVARIANTS
}
