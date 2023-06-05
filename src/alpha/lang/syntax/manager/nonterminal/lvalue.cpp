#include <alpha/lang/syntax/manager/nonterminal/lvalue.h>

#include <alpha/lang/icode/expr.h>
#include <alpha/lang/symbol/table_manager.h>
#include <alpha/lang/syntax/error.h>
#include <alpha/lang/syntax/manager/nonterminal/member.h>

#include <cassert>

using namespace alpha::syntax::manager::nonterminal;

using Member = alpha::syntax::manager::nonterminal::Member;

Lvalue Lvalue::from_idTkn(const Identifier& id) {
  Lvalue lvalue;

  auto result_opt = symTable.search_for_visible_symbol(id.get_name());

  if (!result_opt) {
    assert(symTable.can_add_variable(id.get_name()));

    auto symbol = symTable.add_variable(id.get_name(), id.get_location());

    lvalue.set_expr_from_symbol(symbol);
  } else {
    auto result = result_opt.value();

    if (!result.accessible) {
      error::inaccessible_refference_to_var(id.get_name(), id.get_location());
    } else {
      lvalue.set_expr_from_symbol(result.symbol);
    }
  }

  return lvalue;
}

Lvalue Lvalue::from_localIdTkn(const Identifier& id) {
  Lvalue lvalue;

  auto result_opt = symTable.search_for_visible_local_symbol(id.get_name());

  if (result_opt) {
    auto result = result_opt.value();

    lvalue.set_expr_from_symbol(result.symbol);
  } else {
    if (!symTable.can_add_local_variable(id.get_name())) {
      error::local_var_shadows_lib_function(id.get_name(), id.get_location());
    } else {
      symbol::Symbol::SharedPtr symbol =
          symTable.add_local_variable(id.get_name(), id.get_location());

      lvalue.set_expr_from_symbol(symbol);
    }
  }

  return lvalue;
}

Lvalue Lvalue::from_doubleColonTkn_localIdTkn(const Identifier& identifier) {
  Lvalue lvalue;

  std::string name = identifier.get_name();
  auto result_opt = symTable.search_for_visible_global_symbol(name);

  if (!result_opt) {
    error::undefined_refference_to_global_var(name, identifier.get_location());
  } else {
    auto result = result_opt.value();
    lvalue.set_expr_from_symbol(result.symbol);
  }

  return lvalue;
}

Lvalue Lvalue::from_member(const Member& member) {
  Lvalue lvalue;

  lvalue.set_expr(member.get_expr());

  return lvalue;
}

alpha::icode::Expr Lvalue::get_expr() const {
  return this->expr;
}

void Lvalue::set_expr(const icode::Expr& expr) {
  this->expr = expr;
}

void Lvalue::set_expr_from_symbol(const Symbol::SharedPtr& symbol) {
  icode::Expr icode_expr;

  switch (symbol->get_type()) {
    case Symbol::Type::GLOBAL:
    case Symbol::Type::LOCAL:
    case Symbol::Type::FORMAL:
      icode_expr = icode::Expr::for_var(symbol);
      break;
    case Symbol::Type::USER_FUNCTION:
      icode_expr = icode::Expr::for_program_func(symbol);
      break;
    case Symbol::Type::LIBRARY_FUNCTION:
      icode_expr = icode::Expr::for_library_func(symbol);
      break;
    default:
      assert(0);
  }

  this->expr = icode_expr;
}
