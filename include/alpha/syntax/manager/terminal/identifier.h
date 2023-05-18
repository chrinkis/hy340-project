#pragma once

#include <alpha/syntax/location.h>

#include <string>

namespace alpha {
namespace syntax {
namespace manager {
namespace terminal {

class Identifier {
 private:
  using Location = alpha::syntax::location;

 private:
  std::string name;
  Location location;

 public:
  Identifier();
  Identifier(const std::string& name, const Location& location);

 public:
  std::string get_name() const;
  Location get_location() const;
};

}  // namespace terminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
