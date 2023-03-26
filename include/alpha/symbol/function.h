#pragma once

#include <alpha/symbol/symbol.h>

#include <string>
#include <vector>

namespace alpha {
namespace symbol {

class Function : public Symbol {
  const std::string name;
  const Scope scope;
  const Line line;
  const Type type;
  std::vector<Symbol::SharedPtr> list_of_args;

 public:
  Function(const std::string& name, Scope scope, Line line, Type type);

 public:
  std::string get_name() const override;

  Scope get_scope() const override;

  Line get_line() const override;

  Type get_type() const override;

  void add_arg(const Symbol::SharedPtr& arg);
};

}  // namespace symbol
}  // namespace alpha
