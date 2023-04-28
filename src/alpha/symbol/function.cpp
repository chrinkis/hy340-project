#include <alpha/symbol/function.h>

#include <alpha/symbol/symbol.h>

#include <cassert>

using namespace alpha::symbol;

Function::Function(const std::string& name,
                   Scope scope,
                   const Location& location,
                   Type type)
    : name(name), scope(scope), location(location), type(type) {
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
