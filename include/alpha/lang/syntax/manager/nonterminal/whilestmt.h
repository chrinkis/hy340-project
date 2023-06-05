#pragma once

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class WhilestmtWhile;
class WhilestmtCond;
class Loopstmt;

class Whilestmt {
 public:
  static void whilestmtWhile_whilestmtCond_loopstmt(
      const WhilestmtWhile& whilestmt_while,
      const WhilestmtCond& whilestmt_cond,
      const Loopstmt& loopstmt);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
