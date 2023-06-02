#pragma once

#define tcodeTable (alpha::tcode::abc::Table::get())

#include <alpha/tcode/abc/instruction/instruction.h>
#include <alpha/tcode/abc/instruction/opcode.h>

#include <map>
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

 public:
  void parse_quad_table();

  Instruction::SrcLine get_next_label() const;
};

}  // namespace alpha::tcode::abc
