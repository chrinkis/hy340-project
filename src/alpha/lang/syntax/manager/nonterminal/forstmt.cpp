#include <alpha/lang/syntax/manager/nonterminal/forstmt.h>

#include <alpha/lang/syntax/manager/nonterminal/forstmt_n.h>
#include <alpha/lang/syntax/manager/nonterminal/forstmt_pre.h>
#include <alpha/lang/syntax/manager/nonterminal/loopstmt.h>

#include <alpha/lang/icode/quad/table.h>

using namespace alpha::syntax::manager::nonterminal;

void Forstmt::forstmtPre_N_elist_rParTkn_N_loopstmt_N(
    const ForstmtPre& forstmt_pre,
    const ForstmtN& N1,
    const ForstmtN& N2,
    const Loopstmt& loopstmt,
    const ForstmtN& N3) {
  quadTable.patch_label(forstmt_pre.get_enter(), N2.get_quad_address() + 1);
  quadTable.patch_label(N1.get_quad_address(), quadTable.get_next_label());
  quadTable.patch_label(N2.get_quad_address(), forstmt_pre.get_test());
  quadTable.patch_label(N3.get_quad_address(), N1.get_quad_address() + 1);

  quadTable.patch_list(loopstmt.get_breaklist(), quadTable.get_next_label());
  quadTable.patch_list(loopstmt.get_contlist(), N1.get_quad_address() + 1);
}
