#pragma once

#include <alpha/symbol/symbol.h>

#include <string>

namespace alpha {
namespace symbol {

class Variable : public Symbol {
  const std::string name;
  const Scope scope;
  const Line line;
  const Type type;

 public:
  Variable(const std::string& name, Scope scope, Line line, Type type);

 public:
  std::string get_name() const override;

  Scope get_scope() const override;

  Line get_line() const override;

  Type get_type() const override;
};

}  // namespace symbol
}  // namespace alpha