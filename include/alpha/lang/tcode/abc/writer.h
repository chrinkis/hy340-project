#pragma once

#include <alpha/lang/tcode/abc/consts/user_func.h>
#include <alpha/lang/tcode/abc/instruction/arg.h>
#include <alpha/lang/tcode/abc/instruction/instruction.h>
#include <alpha/lang/tcode/abc/instruction/opcode.h>

#include <fstream>
#include <string>

namespace alpha::tcode::abc {

class Writer {
 private:
  enum class FileType { TEXT, BINARY };

 private:
  using StreamOptions = std::ios_base::openmode;
  using byte = char;
  using string = std::string;
  using UserFunc = consts::UserFunc;
  using Instruction = instruction::Instruction;
  using Opcode = instruction::Opcode;
  using Arg = instruction::Arg;
  using Type = instruction::Arg::Type;

 private:
  std::ofstream ofs;
  FileType file_type;

 private:
  FileType get_file_type() const;

 private:
  void write_double_binary(const double value);
  void write_unsigned_binary(const unsigned value);
  void write_char_binary(const char value);
  void write_byte_binary(const byte value);

  void write_double_text(const double value);
  void write_unsigned_text(const unsigned value);
  void write_char_text(const char value);
  void write_byte_text(const byte& value);

 private:
  void write_avm_file();

  void write_magic_number();

  void write_arrays();

  void write_string_array();

  void write_total(const unsigned total);

  void write_string(const string& str);

  void write_size(const unsigned size);

  void write_number_array();

  void write_user_func_array();

  void write_user_func(const UserFunc& user_func);

  void write_address(const unsigned address);

  void write_local_size(const unsigned local_size);

  void write_id(const string& id);

  void write_lib_functions();

  void write_code();

  void write_instruction(const Instruction& instruction);

  void write_opcode(const Opcode& opcode);

  void write_operand(const Arg& arg);

  void write_type(const Type& type);

  void write_value(const unsigned value);

  void write(const string& file_name, const StreamOptions& options);

 public:
  void write_binary(const string& file_name);
  void write_text(const string& file_name);
};

}  // namespace alpha::tcode::abc
