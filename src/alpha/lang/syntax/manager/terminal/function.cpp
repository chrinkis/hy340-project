#include <alpha/lang/syntax/manager/terminal/function.h>

#include <alpha/lang/syntax/location.h>

using namespace alpha::syntax::manager::terminal;

using Location = alpha::syntax::location;

Function::Function(const Location& location) : location(location) {}

Location Function::get_location() const {
  return this->location;
}
