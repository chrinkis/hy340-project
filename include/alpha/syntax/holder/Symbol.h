#pragma once

#include <alpha/symbol/table_manager.h>

#include <optional>

namespace alpha {
namespace syntax {
namespace holder {

class Symbol {
 public:
  using Optional = std::optional<symbol::Symbol::SharedPtr>;

 private:
  Optional symbol_opt;

 public:
  Optional get_symbol() const;
  void set_symbol(const Optional& optional_symbol);
};

}  // namespace holder
}  // namespace syntax
}  // namespace alpha
