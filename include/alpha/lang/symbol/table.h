#pragma once

#include <alpha/lang/symbol/table_entry.h>

#include <alpha/lang/symbol/symbol.h>

#include <optional>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace alpha {
namespace symbol {

class Table {
 public:
  using Entry = TableEntry;
  using Key = std::string;
  using Pair = std::pair<Key, Entry>;

  using Map = std::unordered_multimap<Key, Entry>;

 private:
  std::vector<Map> per_scope_map;

 public:
  Symbol::SharedPtr insert(const symbol::Symbol& symbol);

  std::optional<TableEntry> lookup(const std::string& name,
                                   const Symbol::Scope& start,
                                   const Symbol::Scope& end) const;

  void hide(const Symbol::Scope& scope);

 public:
  friend std::ostream& operator<<(std::ostream& os, const Table& st);
};

}  // namespace symbol
}  // namespace alpha
