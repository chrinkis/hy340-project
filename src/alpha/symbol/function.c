#include <alpha/symbol/function.h>

#include <alpha/symbol/symbol.h>

#include <cassert>

using namespace alpha::symbol;

Function::Function(const std::string& name, Scope scope, Line line, Type type)
    : name(name), scope(scope), line(line), type(type) {
  assert(this->type == Type::LIBRARY_FUNCTION ||
         this->type == Type::USER_FUNCTION);
}

std::string Function::get_name() const {
  return this->name;
}

Symbol::Scope Function::get_scope() const {
  return this->scope;
}
