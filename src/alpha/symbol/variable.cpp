#include <alpha/symbol/variable.h>

#include <alpha/symbol/symbol.h>

#include <cassert>

using namespace alpha::symbol;

Variable::Variable(const std::string& name, Scope scope, Line line, Type type)
    : name(name), scope(scope), line(line), type(type) {
  assert(this->type == Type::GLOBAL || this->type == Type::FORMAL ||
         this->type == Type::LOCAL);
}

std::string Variable::get_name() const {
  return this->name;
}

Symbol::Scope Variable::get_scope() const {
  return this->scope;
}

Symbol::Line Variable::get_line() const {
  return this->line;
}

Symbol::Type Variable::get_type() const {
  return this->type;
}
