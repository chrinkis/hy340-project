#include <alpha/syntax/manager/terminal/identifier.h>

#include <alpha/syntax/location.h>

using namespace alpha::syntax::manager::terminal;

using Location = alpha::syntax::location;

Identifier::Identifier(const std::string& name, const Location& location)
    : name(name), location(location) {}

std::string Identifier::get_name() const {
  return this->name;
}

Location Identifier::get_location() const {
  return this->location;
}
