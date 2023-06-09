#pragma once

#define tcodeTable (alpha::tcode::abc::Table::get())

#include <alpha/lang/icode/quad/table.h>
#include <alpha/lang/symbol/function.h>
#include <alpha/lang/tcode/abc/instruction/instruction.h>
#include <alpha/lang/tcode/abc/instruction/opcode.h>

#include <map>
#include <stack>
#include <utility>
#include <vector>

namespace alpha::tcode::abc {

class Table {
 private:
  using Instruction = instruction::Instruction;

 private:
  using Collection = std::vector<Instruction>;

 public:
  static Table& get() {
    static Table tcode_table;

    return tcode_table;
  }

 private:
  Collection table;

  std::map<icode::quad::Quad::Line, Instruction::SrcLine> iaddr_to_taddr_map;

  std::vector<std::pair<Instruction::SrcLine, icode::quad::Quad::Line>>
      incomplete_jumps;

  std::stack<std::vector<Instruction::SrcLine>> return_list;
  std::stack<Instruction::SrcLine> jump_before_func_start;

 private:
  void emit(const Instruction& instruction);

  void init_instruction_result_from_quad_label(Instruction& instruction,
                                               const icode::quad::Quad& quad);

  void handle_quad(const icode::quad::Quad& quad);

  void handle_quad_as_nullary(const instruction::Opcode& opcode,
                              const icode::quad::Quad& quad);

  void handle_quad_as_unary(const instruction::Opcode& opcode,
                            const icode::quad::Quad& quad);

  void handle_quad_as_unary_void(const instruction::Opcode& opcode,
                                 const icode::quad::Quad& quad);

  void handle_quad_as_binary(const instruction::Opcode& opcode,
                             const icode::quad::Quad& quad);

  void handle_quad_as_relational(const instruction::Opcode& opcode,
                                 const icode::quad::Quad& quad);

  void handle_quad_as_get_ret_val(const icode::quad::Quad& quad);

  void handle_quad_as_jump(const icode::quad::Quad& quad);

  void handle_quad_as_ret(const icode::quad::Quad& quad);

  void handle_quad_as_func_enter(const icode::quad::Quad& quad);

  void handle_quad_as_func_exit(const icode::quad::Quad& quad);

 public:
  unsigned get_size() const;

  void parse_quad_table(const icode::quad::Table& quad_table);

  Instruction::SrcLine get_next_label() const;

 public: /* Iterators */
  using ConstIterator = Collection::const_iterator;

  ConstIterator begin() const;
  ConstIterator end() const;
};

}  // namespace alpha::tcode::abc
