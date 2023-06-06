#include <alpha/lang/syntax/manager/nonterminal/indexed_opt.h>

#include <alpha/lang/syntax/manager/nonterminal/indexedelem.h>

using namespace alpha::syntax::manager::nonterminal;

IndexedOpt IndexedOpt::from_empty() {
  IndexedOpt indexed_opt;

  return indexed_opt;
}

IndexedOpt IndexedOpt::from_commaTkn_indexedElem_indexedOpt(
    const Indexedelem& indexedelem,
    const IndexedOpt& indexed_opt) {
  IndexedOpt indexed_opt_returning;

  IndexedOpt::IndexedCollection indexed_list = indexed_opt.get_indexed_list();
  indexed_list.insert(indexed_list.begin(), indexedelem.get_icode_epair());

  indexed_opt_returning.set_indexed_list(indexed_list);

  return indexed_opt_returning;
}

IndexedOpt::IndexedCollection IndexedOpt::get_indexed_list() const {
  return this->indexed_list;
}

void IndexedOpt::set_indexed_list(const IndexedCollection& indexed_list) {
  this->indexed_list = indexed_list;
}
