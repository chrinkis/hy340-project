#pragma once

#include <alpha/syntax/location.h>

#include <memory>
#include <ostream>
#include <string>

namespace alpha {
namespace symbol {

class Symbol {
 public:
  using Scope = unsigned int;
  using Offset = unsigned int;
  using Location = syntax::location;

  using SharedPtr = std::shared_ptr<Symbol>;

  enum class Type {
    GLOBAL,
    LOCAL,
    FORMAL,
    USER_FUNCTION,
    LIBRARY_FUNCTION,
  };

  enum class ScopeSpace {
    PROGRAM_VAR,
    FORMAL_ARG,
    FUNCTION_LOCAL,
  };

 public:
  virtual std::string get_name() const = 0;

  virtual Scope get_scope() const = 0;

  virtual Location get_location() const = 0;

  virtual Type get_type() const = 0;

  virtual Offset get_offset() const = 0;

  virtual ScopeSpace get_space() const = 0;

  virtual Symbol* clone() const = 0;

  bool has_function_type() const;

  friend std::ostream& operator<<(std::ostream& os, const Symbol& symbol);
};

}  // namespace symbol
}  // namespace alpha
