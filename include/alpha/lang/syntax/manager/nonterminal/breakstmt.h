#pragma once

#include <alpha/lang/icode/quad/quad.h>
#include <alpha/lang/syntax/location.h>

namespace alpha {
namespace syntax {
namespace manager {
namespace nonterminal {

class Breakstmt {
 private:
  using Quad = icode::quad::Quad;

 private:
  Quad::Label break_list_head = 0;
  Quad::Label continue_list_head = 0;

 public:
  static Breakstmt from_breakTkn(const location& loc);

 public:
  Breakstmt();

 public:
  Quad::Label get_break_list_head() const;
  void set_break_list_head(const Quad::Label& label);

  Quad::Label get_continue_list_head() const;
  void set_continue_list_head(const Quad::Label& label);
};

}  // namespace nonterminal
}  // namespace manager
}  // namespace syntax
}  // namespace alpha
