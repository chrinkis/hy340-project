#include <alpha/symbol/variable.h>

#include <alpha/symbol/symbol.h>

#include <cassert>

using namespace alpha::symbol;

Variable::Variable(const std::string& name,
                   Scope scope,
                   const Location& location,
                   Type type)
    : name(name), scope(scope), location(location), type(type) {
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

Symbol::Type Variable::get_type() const {
  return this->type;
}
