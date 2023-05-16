#include <alpha/syntax/manager/nonterminal/normcall.h>

#include <alpha/syntax/manager/nonterminal/elist.h>

namespace alpha::syntax::manager::nonterminal {

Normcall Normcall::from_lParTkn_elist_rParTkn(const Elist& elist) {
  Normcall normcall;

  normcall.elist = elist.get_icode_elist();
  normcall.method = false;

  return normcall;
}

}  // namespace alpha::syntax::manager::nonterminal
