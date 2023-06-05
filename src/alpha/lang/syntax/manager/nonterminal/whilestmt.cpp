#include <alpha/lang/syntax/manager/nonterminal/whilestmt.h>

#include <alpha/lang/icode/quad/table.h>
#include <alpha/lang/syntax/manager/nonterminal/loopstmt.h>
#include <alpha/lang/syntax/manager/nonterminal/whilestmt_cond.h>
#include <alpha/lang/syntax/manager/nonterminal/whilestmt_while.h>

using namespace alpha::syntax::manager::nonterminal;
using Opcode = alpha::icode::quad::Quad::Opcode;

void Whilestmt::whilestmtWhile_whilestmtCond_loopstmt(
    const WhilestmtWhile& whilestmt_while,
    const WhilestmtCond& whilestmt_cond,
    const Loopstmt& loopstmt) {
  quadTable.emit(Opcode::JUMP, emptyExpr, emptyExpr, emptyExpr,
                 whilestmt_while.get_quad_address());

  quadTable.patch_label(whilestmt_cond.get_quad_address(),
                        quadTable.get_next_label());

  quadTable.patch_list(loopstmt.get_breaklist(), quadTable.get_next_label());
  quadTable.patch_list(loopstmt.get_contlist(),
                       whilestmt_while.get_quad_address());
}
