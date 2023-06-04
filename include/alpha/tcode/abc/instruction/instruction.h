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

 public:
  static Instruction construct_nullary(const Arg::Mapper& icode_to_tcode,
                                       const SrcLine& src_line,
                                       const Opcode& opcode,
                                       const icode::quad::Quad& quad);

  static Instruction construct_unary(const Arg::Mapper& icode_to_tcode,
                                     const SrcLine& src_line,
                                     const Opcode& opcode,
                                     const icode::quad::Quad& quad);

  static Instruction construct_binary(const Arg::Mapper& icode_to_tcode,
                                      const SrcLine& src_line,
                                      const Opcode& opcode,
                                      const icode::quad::Quad& quad);

  static Instruction construct_with_two_args(const Arg::Mapper& icode_to_tcode,
                                             const SrcLine& src_line,
                                             const Opcode& opcode,
                                             const icode::quad::Quad& quad);

  static Instruction construct_with_one_arg(const Arg::Mapper& icode_to_tcode,
                                            const SrcLine& src_line,
                                            const Opcode& opcode,
                                            const icode::quad::Quad& quad);

  static Instruction construct_get_ret_val(const Arg::Mapper& icode_to_tcode,
                                           const SrcLine& src_line,
                                           const icode::quad::Quad& quad);

  static Instruction construct_for_return(const Arg::Mapper& icode_to_tcode,
                                          const SrcLine& src_line,
                                          const icode::quad::Quad& quad);

 public:
  Instruction(const SrcLine& src_line, const Opcode& opcode);
  Instruction(const Instruction& instruction);

  Opcode get_opcode() const;

  std::optional<Arg> get_result() const;
  void set_result(const Arg& arg);

  std::optional<Arg> get_arg_a() const;

  std::optional<Arg> get_arg_b() const;

  SrcLine get_src_line() const;
};

}  // namespace alpha::tcode::abc::instruction
