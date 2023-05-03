#include <alpha/symbol/function.h>

#include <alpha/symbol/symbol.h>

#include <cassert>

using namespace alpha::symbol;

Function::Function(const std::string& name,
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
  assert(this->type == Type::LIBRARY_FUNCTION ||
         this->type == Type::USER_FUNCTION);
}

std::string Function::get_name() const {
  return this->name;
}

Symbol::Scope Function::get_scope() const {
  return this->scope;
}

Symbol::Location Function::get_location() const {
  return this->location;
}

Symbol::Type Function::get_type() const {
  return this->type;
}

Function* Function::clone() const {
  return new Function(*this);
}

void Function::add_arg(const Symbol::SharedPtr& arg) {
  assert(arg);

  this->list_of_args.push_back(arg);
}

Symbol::Offset Function::get_offset() const {
  return this->offset;
}

Symbol::ScopeSpace Function::get_space() const {
  return this->scope_space;
}
