#pragma once

#include <alpha/syntax/location.h>

#include <memory>
#include <string>

namespace alpha {
namespace symbol {

class Symbol {
 public:
  using Scope = unsigned int;
  using Location = syntax::location;

  using SharedPtr = std::shared_ptr<Symbol>;

  enum class Type {
    GLOBAL,
    LOCAL,
    FORMAL,
    USER_FUNCTION,
    LIBRARY_FUNCTION,
  };

 public:
  virtual std::string get_name() const = 0;

  virtual Scope get_scope() const = 0;

  virtual Location get_location() const = 0;

  virtual Type get_type() const = 0;
};

}  // namespace symbol
}  // namespace alpha
