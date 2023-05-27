#include <alpha/symbol/function.h>

#include <alpha/symbol/symbol.h>

#include <cassert>
#include <iomanip>
#include <sstream>

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
      scope_space(scope_space),
      total_locals(0) {
  assert(this->type == Type::LIBRARY_FUNCTION ||
         this->type == Type::USER_FUNCTION);

  assert(this->scope_space == ScopeSpace::PROGRAM_VAR ||
         this->scope_space == ScopeSpace::FUNCTION_LOCAL);
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

std::string Function::to_string() const {
  auto ident = [](int w = 16) { return std::setw(w); };

  std::stringstream os;

  os << Symbol::to_string() << std::left;

  os << ident() << "locals: " + std::to_string(this->get_total_locals());

  os << ident() << "args: " + std::to_string(this->list_of_args.size());

  os << ident() << "iaddr: " + std::to_string(this->get_iaddress());

  return os.str();
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

Function::LocalCounter Function::get_total_locals() const {
  return this->total_locals;
}

void Function::set_total_locals(const LocalCounter& total_locals) {
  this->total_locals = total_locals;
}

Function::Iaddress Function::get_iaddress() const {
  return this->iaddress;
}

void Function::set_iaddress(const Iaddress& iaddress) {
  this->iaddress = iaddress;
}
