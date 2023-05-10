#pragma once

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Forstmt_pre;
class Forstmt_N;
class Loopstmt;

class Forstmt {
 public:
  static void forstmtPre_N_elist_rParTkn_N_loopstmt_N(
      const Forstmt_pre& forstmt_pre,
      const Forstmt_N& N1,
      const Forstmt_N& N2,
      const Loopstmt& loopstmt,
      const Forstmt_N& N3);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
