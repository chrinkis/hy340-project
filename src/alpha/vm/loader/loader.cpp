#include <alpha/vm/loader/loader.h>

#include <utils/warnings.h>

#include <filesystem>
#include <iterator>
#include <string>

#define BAD_FILE_FORMAT std::runtime_error("Bad file format!")

#define CANNOT_OPEN_FILE \
  std::runtime_error("Cannot open file with given name! Check if it exists.")

#define ASSERT_FILE_FORMAT(condition) \
  if (!(condition)) {                 \
    throw BAD_FILE_FORMAT;            \
  }

#define BAD_FILE_EXTENSION(extension) \
  std::runtime_error("Can't read \"." + extension + "\" files")

#define MAGIC_NUMBER 340200501

#define NULL_CHAR "'\\0'"

#define GET_FILE_TYPE (this->get_file_type())

#define READ_BINARY(type)                                          \
  {                                                                \
    type var;                                                      \
    this->ifs.read(reinterpret_cast<char*>(&(var)), sizeof(type)); \
    ASSERT_FILE_FORMAT(this->ifs.good());                          \
    return var;                                                    \
  }

#define READ_TEXT(value)                  \
  {                                       \
    this->ifs >> (value);                 \
    ASSERT_FILE_FORMAT(this->ifs.good()); \
    char new_line;                        \
    this->ifs >> new_line;                \
    ASSERT_FILE_FORMAT(new_line == '\n'); \
  }

/* -> Try to read a char in order to set eof bit of stream
 * -> (Error checking might need to be reviewed)
 */
#define READ_END_OF_FILE                   \
  FIXME; /* Read comment ^^^ */            \
  char var;                                \
  ASSERT_FILE_FORMAT(!this->ifs.eof());    \
  if (GET_FILE_TYPE == FileType::BINARY) { \
    this->ifs.read(&var, sizeof(var));     \
  } else {                                 \
    this->ifs >> var;                      \
  }                                        \
  ASSERT_FILE_FORMAT(this->ifs.eof());

#define READ_DOUBLE                                               \
  (GET_FILE_TYPE == FileType::BINARY ? this->read_double_binary() \
                                     : this->read_double_text())

#define READ_UNSIGNED                                               \
  (GET_FILE_TYPE == FileType::BINARY ? this->read_unsigned_binary() \
                                     : this->read_unsigned_text())

#define READ_CHAR                                               \
  (GET_FILE_TYPE == FileType::BINARY ? this->read_char_binary() \
                                     : this->read_char_text())

#define READ_BYTE                                               \
  (GET_FILE_TYPE == FileType::BINARY ? this->read_byte_binary() \
                                     : this->read_byte_text())

#define READ_STRING                                               \
  (GET_FILE_TYPE == FileType::BINARY ? this->read_string_binary() \
                                     : this->read_string_text())

#define READ_OPCODE                                               \
  (GET_FILE_TYPE == FileType::BINARY ? this->read_opcode_binary() \
                                     : this->read_opcode_text())

#define READ_TYPE                                               \
  (GET_FILE_TYPE == FileType::BINARY ? this->read_type_binary() \
                                     : this->read_type_text())

#define READ_END_OF_STRING                        \
  std::string null_char_str;                      \
                                                  \
  this->ifs >> null_char_str;                     \
  ASSERT_FILE_FORMAT(this->ifs.good());           \
  ASSERT_FILE_FORMAT(null_char_str == NULL_CHAR); \
                                                  \
  char new_line;                                  \
  this->ifs >> new_line;                          \
  ASSERT_FILE_FORMAT(this->ifs.good());           \
  ASSERT_FILE_FORMAT(new_line == '\n');           \
                                                  \
  ASSERT_FILE_FORMAT(null_char_str == NULL_CHAR);

namespace alpha::vm::loader {

using byte = char;
using Instruction = alpha::vm::abc::instruction::Instruction;
using Opcode = alpha::vm::abc::instruction::Opcode;
using Arg = alpha::vm::abc::instruction::Arg;
using ArgType = alpha::vm::abc::instruction::Arg::Type;
using UserFunc = alpha::vm::arch::mem::consts::UserFunc;

Loader::Loader(ConstTable& const_table, InstructionTable& instruction_table)
    : const_table(const_table),
      instruction_table(instruction_table),
      global_offset(0, false) {}

Loader::FileType Loader::get_file_type() const {
  return this->file_type;
}

double Loader::read_double_binary() {
  READ_BINARY(double);
}

unsigned Loader::read_unsigned_binary() {
  READ_BINARY(unsigned);
}

char Loader::read_char_binary() {
  READ_BINARY(char);
}

byte Loader::read_byte_binary() {
  READ_BINARY(byte);
}

double Loader::read_double_text() {
  double value;
  READ_TEXT(value);
  return value;
}

unsigned Loader::read_unsigned_text() {
  unsigned value;
  READ_TEXT(value);
  return value;
}

char Loader::read_char_text() {
  char value;
  READ_TEXT(value);
  return value;
}

byte Loader::read_byte_text() {
  byte value;
  READ_TEXT(value);
  return value;
}

void Loader::read_avm_file() {
  this->read_magic_number();
  this->read_arrays();
  this->read_code();

  READ_END_OF_FILE;
}

void Loader::read_magic_number() {
  ASSERT_FILE_FORMAT(READ_UNSIGNED == MAGIC_NUMBER);
}

void Loader::read_arrays() {
  this->read_string_array();
  this->read_number_array();
  this->read_user_func_array();
  this->read_lib_functions();
}

void Loader::read_string_array() {
  unsigned total = this->read_total();

  for (int i = 0; i < total; i++) {
    std::string str = this->read_string();
    this->const_table.insert_string(str);
  }
}

unsigned Loader::read_total() {
  return READ_UNSIGNED;
}

std::string Loader::read_string_binary() {
  unsigned size = this->read_size();

  std::string str;

  char cur_char = READ_CHAR;
  while (cur_char) {
    str += cur_char;
    cur_char = READ_CHAR;
  }

  ASSERT_FILE_FORMAT(str.size() == size);

  return str;
}

std::string Loader::read_string_text() {
  unsigned size = this->read_size();

  std::string str;

  for (int i = 0; i < size; i++) {
    str += READ_CHAR;
  }

  READ_END_OF_STRING;

  return str;
}

std::string Loader::read_string() {
  return READ_STRING;
}

unsigned Loader::read_size() {
  return READ_UNSIGNED;
}

void Loader::read_number_array() {
  unsigned total = this->read_total();

  for (int i = 0; i < total; i++) {
    double number = READ_DOUBLE;
    this->const_table.insert_number(number);
  }
}

void Loader::read_user_func_array() {
  unsigned total = this->read_total();

  for (int i = 0; i < total; i++) {
    UserFunc user_func = this->read_user_func();
    this->const_table.insert_user_func(user_func);
  }
}

UserFunc Loader::read_user_func() {
  auto address = this->read_address();
  auto local_size = this->read_local_size();
  auto id = this->read_id();

  return UserFunc(address, id, local_size);
}

unsigned Loader::read_address() {
  return READ_UNSIGNED;
}

unsigned Loader::read_local_size() {
  return READ_UNSIGNED;
}

std::string Loader::read_id() {
  return this->read_string();
}

void Loader::read_lib_functions() {
  unsigned total = this->read_total();

  for (int i = 0; i < total; i++) {
    std::string lib_func = this->read_lib_function();
    this->const_table.insert_lib_func_name(lib_func);
  }
}

std::string Loader::read_lib_function() {
  return this->read_string();
}

void Loader::read_code() {
  unsigned total = this->read_total();

  for (int i = 0; i < total; i++) {
    Instruction instr = this->read_instruction(i);
    this->instruction_table.emit(instr);
  }
}

Instruction Loader::read_instruction(const SrcLine& instr_no) {
  Opcode opcode = this->read_opcode();
  Arg result = this->read_arg();
  Arg arg_a = this->read_arg();
  Arg arg_b = this->read_arg();

  return Instruction(instr_no, opcode, result, arg_a, arg_b);
}

Opcode Loader::read_opcode_binary() {
  return static_cast<Opcode>(READ_BYTE);
}

Opcode Loader::read_opcode_text() {
  return static_cast<Opcode>(READ_UNSIGNED);
}

Opcode Loader::read_opcode() {
  return READ_OPCODE;
}

Arg Loader::read_arg() {
  Arg arg(this->read_type(), this->read_value());

  if (arg.get_type() == ArgType::GLOBAL) {
    this->global_offset.exists = true;
    this->global_offset.max =
        std::max(this->global_offset.max, arg.get_value());
  }

  return arg;
}

ArgType Loader::read_type_binary() {
  return static_cast<ArgType>(READ_BYTE);
}

ArgType Loader::read_type_text() {
  return static_cast<ArgType>(READ_UNSIGNED);
}

ArgType Loader::read_type() {
  return READ_TYPE;
}

unsigned Loader::read_value() {
  return READ_UNSIGNED;
}

void Loader::load_from(std::string file_name) {
  std::filesystem::path file_path(file_name);

  if (file_path.extension() == ".abc") {
    this->file_type = FileType::BINARY;
    this->ifs.open(file_name, std::ios::in | std::ios::binary);
  } else if (file_path.extension() == ".txt") {
    this->file_type = FileType::TEXT;
    this->ifs.open(file_name);
  } else {
    throw BAD_FILE_EXTENSION(file_path.extension().string());
  }

  if (this->ifs.fail()) {
    throw CANNOT_OPEN_FILE;
  }

  this->ifs.unsetf(std::ios_base::skipws);

  this->read_avm_file();
  this->ifs.close();
}

unsigned Loader::get_total_globals() const {
  return this->global_offset.exists ? this->global_offset.max + 1 : 0;
}

}  // namespace alpha::vm::loader
