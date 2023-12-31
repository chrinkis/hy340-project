#include <alpha/lang/token/token.h>

using namespace alpha::token;

Token::Token() {}

Token::Token(unsigned int line,
             unsigned int sequence_number,
             const std::string& content,
             Token::Category category)
    : line(line),
      sequence_number(sequence_number),
      content(content),
      category(category) {}

unsigned int Token::get_line() const {
  return this->line;
}

void Token::set_line(unsigned int line) {
  this->line = line;
}

unsigned int Token::get_sequence_number() const {
  return this->sequence_number;
}

void Token::set_sequence_number(unsigned int sequence_number) {
  this->sequence_number = sequence_number;
}

std::string Token::get_content() const {
  return this->content;
}

void Token::set_content(const std::string& content) {
  this->content = content;
}

Token::Category Token::get_category() const {
  return this->category;
}

void Token::set_category(Token::Category category) {
  this->category = category;
}
