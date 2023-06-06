#include <alpha/lang/syntax/manager/nonterminal/indexed.h>

#include <alpha/lang/syntax/manager/nonterminal/indexed_opt.h>
#include <alpha/lang/syntax/manager/nonterminal/indexedelem.h>

using namespace alpha::syntax::manager::nonterminal;

Indexed Indexed::from_indexedElem_indexedOpt(const Indexedelem& indexedelem,
                                             const IndexedOpt& indexed_opt) {
  Indexed indexed;

  Indexed::IndexedCollection indexed_list = indexed_opt.get_indexed_list();
  indexed_list.insert(indexed_list.begin(), indexedelem.get_icode_epair());

  indexed.set_indexed_list(indexed_list);

  return indexed;
}

Indexed::IndexedCollection Indexed::get_indexed_list() const {
  return this->indexed_list;
}

void Indexed::set_indexed_list(const IndexedCollection& indexed_list) {
  this->indexed_list = indexed_list;
}
