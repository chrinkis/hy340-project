#include <alpha/syntax/manager/nonterminal/elist_opt.h>

#include <alpha/icode/quad/table.h>
#include <alpha/syntax/manager/nonterminal/elist.h>
#include <alpha/syntax/manager/nonterminal/expr.h>

using namespace alpha::syntax::manager::nonterminal;

ElistOpt ElistOpt::from_empty() {
  ElistOpt elist_opt;

  return elist_opt;
}

ElistOpt ElistOpt::from_commaTkn_expr_elistOpt(const Expr& _expr,
                                               const ElistOpt& elist_opt) {
  ElistOpt elist_opt_returning;

  auto expr =
      quadTable.emit_if_bool_expr(_expr.get_expr(), _expr.get_true_list_head(),
                                  _expr.get_false_list_head());

  ElistOpt::ExprCollection icode_elist = elist_opt.get_icode_elist();
  icode_elist.insert(icode_elist.begin(), expr);

  elist_opt_returning.set_icode_elist(icode_elist);

  return elist_opt_returning;
}

ElistOpt::ExprCollection ElistOpt::get_icode_elist() const {
  return this->icode_elist;
}

void ElistOpt::set_icode_elist(const ExprCollection& icode_elist) {
  this->icode_elist = icode_elist;
}
