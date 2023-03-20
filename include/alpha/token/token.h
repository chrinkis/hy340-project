#pragma once

#include <alpha/token/category.h>
#include <string>

namespace alpha {
namespace token {

class Token {
  unsigned int line;
  unsigned int sequence_number;
  std::string content;
  category::Category category;

 public:
  Token();
  Token(unsigned int line,
        unsigned int sequence_number,
        const std::string& content,
        category::Category category);

  unsigned int get_line() const;
  void set_line(unsigned int line);

  unsigned int get_sequence_number() const;
  void set_sequence_number(unsigned int sequence_number);

  std::string get_content() const;
  void set_content(const std::string& content);

  category::Category get_category() const;
  void set_category(category::Category category);
};

}  // namespace token
}  // namespace alpha
