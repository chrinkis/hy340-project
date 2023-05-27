#pragma once

#include <alpha/symbol/symbol.h>

#include <memory>
#include <string>
#include <vector>

namespace alpha {
namespace symbol {

class Function : public Symbol {
 public:
  using SharedPtr = std::shared_ptr<Function>;
  using LocalCounter = unsigned;
  using Iaddress = unsigned;

 private:
  const std::string name;
  const Scope scope;
  const Location location;
  const Type type;
  std::vector<Symbol::SharedPtr> list_of_args;
  const Offset offset;
  const ScopeSpace scope_space;
  Iaddress iaddress = 0;

  LocalCounter total_locals;

 public:
  Function(const std::string& name,
           Scope scope,
           const Location& location,
           Type type,
           Offset offset,
           ScopeSpace scope_space);

 public:
  std::string get_name() const override;

  Scope get_scope() const override;

  Location get_location() const override;

  Type get_type() const override;

  Function* clone() const override;

  void add_arg(const Symbol::SharedPtr& arg);

  Offset get_offset() const override;

  ScopeSpace get_space() const override;

  LocalCounter get_total_locals() const;

  void set_total_locals(const LocalCounter& total_locals);

  Iaddress get_iaddress() const;

  void set_iaddress(const Iaddress& iaddress);
};

}  // namespace symbol
}  // namespace alpha
