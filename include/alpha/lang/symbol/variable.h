#pragma once

#include <alpha/lang/symbol/symbol.h>

#include <memory>
#include <string>

namespace alpha {
namespace symbol {

class Variable : public Symbol {
 public:
  using SharedPtr = std::shared_ptr<Variable>;

 private:
  const std::string name;
  const Scope scope;
  const Location location;
  const Type type;
  const Offset offset;
  const ScopeSpace scope_space;

 public:
  Variable(const std::string& name,
           Scope scope,
           const Location& location,
           Type type,
           Offset offset,
           ScopeSpace scope_space);

 public:
  std::string get_name() const override;

  Scope get_scope() const override;

  Location get_location() const override;

  Variable* clone() const override;

  Type get_type() const override;

  Offset get_offset() const override;

  ScopeSpace get_space() const override;
};

}  // namespace symbol
}  // namespace alpha
