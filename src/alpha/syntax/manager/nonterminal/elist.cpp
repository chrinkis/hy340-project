#include <alpha/syntax/manager/nonterminal/elist.h>

#include <alpha/syntax/manager/nonterminal/elist_opt.h>
#include <alpha/syntax/manager/nonterminal/expr.h>

using namespace alpha::syntax::manager::nonterminal;

Elist Elist::from_empty() {
  Elist elist;

  return elist;
}

Elist Elist::from_expr_elistOpt(const Expr& expr, const ElistOpt& elist_opt) {
  Elist elist;

  Elist::ExprCollection icode_elist = elist_opt.get_icode_elist();
  icode_elist.push_back(expr.get_expr());

  elist.set_icode_elist(icode_elist);

  return elist;
}

Elist::ExprCollection Elist::get_icode_elist() const {
  return this->icode_elist;
}

void Elist::set_icode_elist(const ExprCollection& icode_elist) {
  this->icode_elist = icode_elist;
}
