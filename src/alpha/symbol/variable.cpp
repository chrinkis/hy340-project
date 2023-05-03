#include <alpha/symbol/variable.h>

#include <alpha/symbol/symbol.h>

#include <cassert>

using namespace alpha::symbol;

Variable::Variable(const std::string& name,
                   Scope scope,
                   const Location& location,
                   Type type,
                   Offset offset,
                   ScopeSpace scope_space)
    : name(name),
      scope(scope),
      location(location),
      type(type),
      offset(offset),
      scope_space(scope_space) {
  assert(this->type == Type::GLOBAL || this->type == Type::FORMAL ||
         this->type == Type::LOCAL);
}

std::string Variable::get_name() const {
  return this->name;
}

Symbol::Scope Variable::get_scope() const {
  return this->scope;
}

Symbol::Location Variable::get_location() const {
  return this->location;
}

Variable* Variable::clone() const {
  return new Variable(*this);
}

Symbol::Type Variable::get_type() const {
  return this->type;
}

Symbol::Offset Variable::get_offset() const {
  return this->offset;
}

Symbol::ScopeSpace Variable::get_space() const {
  return this->scope_space;
}
