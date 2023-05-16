#include <alpha/syntax/manager/nonterminal/whilestmt.h>

#include <alpha/icode/quad/table.h>
#include <alpha/syntax/manager/nonterminal/loopstmt.h>
#include <alpha/syntax/manager/nonterminal/whilestmt_cond.h>
#include <alpha/syntax/manager/nonterminal/whilestmt_while.h>

using namespace alpha::syntax::manager::nonterminal;

void Whilestmt::whilestmtWhile_whilestmtCond_loopstmt(
    const WhilestmtWhile& whilestmt_while,
    const WhilestmtCond& whilestmt_cond,
    const Loopstmt& loopstmt) {
  quadTable.emit_jump(whilestmt_while.get_quad_address());

  quadTable.patch_label(whilestmt_cond.get_quad_address(),
                        quadTable.get_next_label());

  quadTable.patch_list(loopstmt.get_breaklist(), quadTable.get_next_label());
  quadTable.patch_list(loopstmt.get_contlist(),
                       whilestmt_while.get_quad_address());
}
