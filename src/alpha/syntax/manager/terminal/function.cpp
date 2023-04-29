#include <alpha/syntax/location.h>
#include <alpha/syntax/manager/terminal/function.h>

using namespace alpha::syntax::manager::terminal;

using Location = alpha::syntax::location;

Function::Function(const Location& location) : location(location) {}

Location Function::get_location() const {
  return this->location;
}
