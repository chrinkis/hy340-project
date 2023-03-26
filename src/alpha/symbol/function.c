#include <alpha/symbol/function.h>

#include <cassert>

using namespace alpha::symbol;

Function::Function(const std::string& name, Scope scope, Line line, Type type)
    : name(name), scope(scope), line(line), type(type) {
  assert(this->type == Type::LIBRARY_FUNCTION ||
         this->type == Type::USER_FUNCTION);
}
