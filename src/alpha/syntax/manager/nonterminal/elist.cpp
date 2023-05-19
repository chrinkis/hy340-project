#include <alpha/syntax/manager/nonterminal/elist.h>

#include <alpha/icode/quad/table.h>
#include <alpha/syntax/manager/nonterminal/elist_opt.h>
#include <alpha/syntax/manager/nonterminal/expr.h>

using namespace alpha::syntax::manager::nonterminal;

Elist Elist::from_empty() {
  Elist elist;

  return elist;
}

Elist Elist::from_expr_elistOpt(const Expr& _expr, const ElistOpt& elist_opt) {
  Elist elist;

  auto expr =
      quadTable.emit_if_bool_expr(_expr.get_expr(), _expr.get_true_list_head(),
                                  _expr.get_false_list_head());

  Elist::ExprCollection icode_elist = elist_opt.get_icode_elist();
  icode_elist.insert(icode_elist.begin(), expr);

  elist.set_icode_elist(icode_elist);

  return elist;
}

Elist::ExprCollection Elist::get_icode_elist() const {
  return this->icode_elist;
}

void Elist::set_icode_elist(const ExprCollection& icode_elist) {
  this->icode_elist = icode_elist;
}
