#pragma once

#include <alpha/icode/expr.h>
#include <utility>
#include <vector>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Indexedelem;

class IndexedOpt {
 public:
  using ExprPair = std::pair<icode::Expr, icode::Expr>;
  using IndexedCollection = std::vector<ExprPair>;

 private:
  IndexedCollection indexed_list;

 public:
  static IndexedOpt from_empty();
  static IndexedOpt from_commaTkn_indexedElem_indexedOpt(
      const Indexedelem& indexedelem,
      const IndexedOpt& indexed_opt);

 public:
  IndexedCollection get_indexed_list() const;
  void set_indexed_list(const IndexedCollection& indexed_list);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
