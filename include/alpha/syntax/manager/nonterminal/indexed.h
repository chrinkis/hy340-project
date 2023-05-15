#pragma once

#include <alpha/icode/expr.h>
#include <utility>
#include <vector>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Indexedelem;
class IndexedOpt;

class Indexed {
 public:
  using ExprPair = std::pair<icode::Expr, icode::Expr>;
  using IndexedCollection = std::vector<ExprPair>;

 private:
  IndexedCollection indexed_list;

 public:
  static Indexed from_indexedElem_indexedOpt(const Indexedelem& indexedelem,
                                             const IndexedOpt& indexed_opt);

 public:
  IndexedCollection get_indexed_list() const;
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
