#pragma once

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class ForstmtPre;
class ForstmtN;
class Loopstmt;

class Forstmt {
 public:
  static void forstmtPre_N_elist_rParTkn_N_loopstmt_N(
      const ForstmtPre& forstmt_pre,
      const ForstmtN& N1,
      const ForstmtN& N2,
      const Loopstmt& loopstmt,
      const ForstmtN& N3);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
