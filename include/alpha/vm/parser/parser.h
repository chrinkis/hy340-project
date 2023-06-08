#pragma once

#include <alpha/vm/abc/instruction/arg.h>
#include <alpha/vm/abc/instruction/instruction.h>
#include <alpha/vm/abc/instruction/opcode.h>
#include <alpha/vm/arch/mem/code/table.h>
#include <alpha/vm/arch/mem/consts/consts.h>
#include <alpha/vm/arch/mem/consts/user_func.h>

#include <fstream>
#include <string>

namespace vm::parser {

class Parser {
 private:
  enum class FileType { TEXT, BINARY };

 private:
  using StreamOptions = std::ios_base::openmode;
  using byte = char;

  using Instruction = alpha::vm::abc::instruction::Instruction;
  using SrcLine = alpha::vm::abc::instruction::Instruction::SrcLine;
  using Opcode = alpha::vm::abc::instruction::Opcode;
  using Arg = alpha::vm::abc::instruction::Arg;
  using ArgType = alpha::vm::abc::instruction::Arg::Type;
  using UserFunc = alpha::vm::arch::mem::consts::UserFunc;

  using ConstTable = alpha::vm::arch::mem::consts::Consts;
  using InstructionTable = alpha::vm::arch::mem::code::Table;

 private:
  FileType file_type;
  std::ifstream ifs;

  ConstTable& const_table;
  InstructionTable& instruction_table;
  struct {
    unsigned max;
    bool exists;
  } global_offset;

 public:
  Parser(ConstTable& const_table, InstructionTable& instruction_table);

 private:
  FileType get_file_type() const;

 private:
  double read_double_binary();
  unsigned read_unsigned_binary();
  char read_char_binary();
  byte read_byte_binary();

  double read_double_text();
  unsigned read_unsigned_text();
  char read_char_text();
  byte read_byte_text();

 private:
  void read_avm_file();

  void read_magic_number();

  void read_arrays();

  void read_string_array();

  unsigned read_total();

  std::string read_string_text();
  std::string read_string_binary();
  std::string read_string();

  unsigned read_size();

  void read_number_array();

  void read_user_func_array();

  UserFunc read_user_func();

  unsigned read_address();

  unsigned read_local_size();

  std::string read_id();

  void read_lib_functions();

  std::string read_lib_function();

  void read_code();

  Instruction read_instruction(const SrcLine& instr_no);

  Opcode read_opcode_binary();
  Opcode read_opcode_text();
  Opcode read_opcode();

  Arg read_arg();

  ArgType read_type_binary();
  ArgType read_type_text();
  ArgType read_type();

  byte read_value();

 public:
  void parse(std::string file_name);
  unsigned get_total_globals() const;
};

}  // namespace vm::parser
