#include <alpha/tcode/abc/writer.h>

#include <alpha/tcode/abc/consts/consts.h>
#include <alpha/tcode/abc/table.h>

#include <cassert>

#include <utils/warnings.h>

#define MAGIC_NUMBER 340200501

#define WRITE_BINARY(value) \
  this->ofs.write(reinterpret_cast<const char*>(&(value)), sizeof(value))

#define WRITE_TEXT(value) this->ofs << (value) << " "

#define GET_FILE_TYPE (this->get_file_type())

#define WRITE_DOUBLE(value)                                             \
  (GET_FILE_TYPE == FileType::BINARY ? this->write_double_binary(value) \
                                     : this->write_double_text(value))

#define WRITE_UNSIGNED(value)                                             \
  (GET_FILE_TYPE == FileType::BINARY ? this->write_unsigned_binary(value) \
                                     : this->write_unsigned_text(value))

#define WRITE_CHAR(value)                                             \
  (GET_FILE_TYPE == FileType::BINARY ? this->write_char_binary(value) \
                                     : this->write_char_text(value))

#define WRITE_BYTE(value)                                             \
  (GET_FILE_TYPE == FileType::BINARY ? this->write_byte_binary(value) \
                                     : this->write_byte_text(value))

using namespace alpha::tcode::abc;

Writer::FileType Writer::get_file_type() const {
  return this->file_type;
}

void Writer::write_double_binary(const double value) {
  WRITE_BINARY(value);
}

void Writer::write_unsigned_binary(const unsigned value) {
  WRITE_BINARY(value);
}

void Writer::write_char_binary(const char value) {
  WRITE_BINARY(value);
}

void Writer::write_byte_binary(const byte value) {
  WRITE_BINARY(value);
}

void Writer::write_double_text(const double value) {
  WRITE_TEXT(value);
}

void Writer::write_unsigned_text(const unsigned value) {
  WRITE_TEXT(value);
}

void Writer::write_char_text(const char value) {
  WRITE_TEXT(value);
}

void Writer::write_byte_text(const byte& value) {
  WRITE_TEXT(value);
}

void Writer::write_avm_file() {
  this->write_magic_number();
  this->write_arrays();
  this->write_code();
}

void Writer::write_magic_number() {
  WRITE_UNSIGNED(MAGIC_NUMBER);
}

void Writer::write_arrays() {
  this->write_string_array();
  this->write_number_array();
  this->write_user_func_array();
  this->write_lib_functions();
}

void Writer::write_string_array() {
  unsigned total = tcodeConsts.get_strings().size();
  this->write_total(total);

  for (auto str : tcodeConsts.get_strings()) {
    this->write_string(str);
  }
}

void Writer::write_total(const unsigned total) {
  WRITE_UNSIGNED(total);
}

void Writer::write_string(const string& str) {
  unsigned size = str.size() + 1;  // include '\0'
  this->write_size(size);

  for (auto str_char : str) {
    WRITE_CHAR(str_char);
  }

  WRITE_CHAR('\0');
}

void Writer::write_size(const unsigned size) {
  WRITE_UNSIGNED(size);
}

void Writer::write_number_array() {
  unsigned total = tcodeConsts.get_numbers().size();
  this->write_total(total);

  for (auto number : tcodeConsts.get_numbers()) {
    WRITE_DOUBLE(number);
  }
}

void Writer::write_user_func_array() {
  unsigned total = tcodeConsts.get_user_funcs().size();
  this->write_total(total);

  for (auto user_func : tcodeConsts.get_user_funcs()) {
    this->write_user_func(user_func);
  }
}

void Writer::write_user_func(const UserFunc& user_func) {
  auto address = user_func.get_address();
  this->write_address(address);

  auto local_size = user_func.get_local_size();
  this->write_local_size(local_size);

  auto id = user_func.get_id();
  this->write_id(id);
}

void Writer::write_address(const unsigned address) {
  WRITE_UNSIGNED(address);
}

void Writer::write_local_size(const unsigned local_size) {
  WRITE_UNSIGNED(local_size);
}

void Writer::write_id(const string& id) {
  this->write_string(id);
}

void Writer::write_lib_functions() {
  unsigned total = tcodeConsts.get_lib_func_names().size();
  this->write_total(total);

  for (auto lib_func_name : tcodeConsts.get_lib_func_names()) {
    this->write_string(lib_func_name);
  }
}

void Writer::write_code() {
  unsigned total = tcodeTable.get_size();
  this->write_total(total);

  for (auto instruction : tcodeTable) {
    this->write_instruction(instruction);
  }
}

void Writer::write_instruction(const Instruction& instruction) {
  auto opcode = instruction.get_opcode();
  this->write_opcode(opcode);

  auto result = instruction.get_result();
  this->write_operand(result);

  auto arg_a = instruction.get_arg_a();
  this->write_operand(arg_a);

  auto arg_b = instruction.get_arg_b();
  this->write_operand(arg_b);
}

void Writer::write_opcode(const Opcode& opcode) {
  FIXME;
  WRITE_BYTE(static_cast<byte>(opcode));
}

void Writer::write_operand(const Arg& arg) {
  auto type = arg.get_type();
  this->write_type(type);

  unsigned value = arg.get_value();
  this->write_value(value);
}

void Writer::write_type(const Type& type) {
  FIXME;
  WRITE_BYTE(static_cast<byte>(type));
}

void Writer::write_value(const unsigned value) {
  WRITE_UNSIGNED(value);
}

void Writer::write(const string& file_name, const StreamOptions& options) {
  this->ofs.open(file_name, options);

  FIXME;  // Handle stream failure
  assert(ofs);

  this->write_avm_file();

  this->ofs.close();
}

void Writer::write_binary(string file_name) {
  this->file_type = FileType::BINARY;
  this->write(file_name, std::ios::out | std::ios::binary);
}

void Writer::write_text(string file_name) {
  this->file_type = FileType::TEXT;
  this->write(file_name, std::ios::out);
}
