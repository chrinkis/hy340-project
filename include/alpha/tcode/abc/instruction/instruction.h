#pragma once

#include <alpha/icode/quad/quad.h>
#include <alpha/tcode/abc/instruction/arg.h>
#include <alpha/tcode/abc/instruction/opcode.h>

#include <optional>

namespace alpha::tcode::abc::instruction {

class Instruction {
 public:
  using SrcLine = unsigned;

 private:
  Opcode opcode;

  std::optional<Arg> result;
  std::optional<Arg> arg_a;
  std::optional<Arg> arg_b;

  SrcLine src_line;

 private:
  void init_as_unary(const Opcode& opcode, const icode::quad::Quad& quad);
  void init_as_binary(const Opcode& opcode, const icode::quad::Quad& quad);
  void init_as_relational(const Opcode& opcode, const icode::quad::Quad& quad);

 public:
  Instruction(const icode::quad::Quad& quad);

  Opcode get_opcode() const;

  std::optional<Arg> get_result() const;
  std::optional<Arg> get_arg_a() const;
  std::optional<Arg> get_arg_b() const;

  SrcLine get_src_line() const;
};

}  // namespace alpha::tcode::abc::instruction
