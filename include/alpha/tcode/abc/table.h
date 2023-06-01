#pragma once

#define tcodeTable (alpha::tcode::abc::Table::get())

#include <alpha/tcode/abc/instruction/instruction.h>

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

 private:
  void emit(const Instruction& instruction);

 public:
  void parse_quad_table();

  Instruction::SrcLine get_next_label() const;
};

}  // namespace alpha::tcode::abc
