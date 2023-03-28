#pragma once

#include <alpha/symbol/symbol.h>

#include <string>

namespace alpha {
namespace symbol {

class Variable : public Symbol {
  const std::string name;
  const Scope scope;
  const Location location;
  const Type type;

 public:
  Variable(const std::string& name,
           Scope scope,
           const Location& location,
           Type type);

 public:
  std::string get_name() const override;

  Scope get_scope() const override;

  Location get_location() const override;

  Type get_type() const override;
};

}  // namespace symbol
}  // namespace alpha
