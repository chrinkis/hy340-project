#pragma once

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Whilestmt_while;
class Whilestmt_cond;
class Loopstmt;

class Whilestmt {
 public:
  static void whilestmtWhile_whilestmtCond_loopstmt(
      const Whilestmt_while& whilestmt_while,
      const Whilestmt_cond& whilestmt_cond,
      const Loopstmt& loopstmt);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
