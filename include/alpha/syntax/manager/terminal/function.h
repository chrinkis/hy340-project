#pragma once

#include <alpha/syntax/location.h>

#include <string>

namespace alpha {
namespace syntax {
namespace manager {
namespace terminal {

class Function {
 private:
  using Location = alpha::syntax::location;

 private:
  const Location location;

 public:
  Function(const Location& location);

 public:
  Location get_location() const;
};

}  // namespace terminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
