#include <alpha/symbol/variable.h>

#include <cassert>

using namespace alpha::symbol;

Variable::Variable(const std::string& name, Scope scope, Line line, Type type)
    : name(name), scope(scope), line(line), type(type) {
  assert(this->type == Type::GLOBAL || this->type == Type::FORMAL ||
         this->type == Type::LOCAL);
}
