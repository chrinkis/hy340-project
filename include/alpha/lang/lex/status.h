#pragma once

namespace alpha {
namespace lex {

namespace status {
enum Status {
  SUCCESS,
  NOT_CLOSED_STRING,
  NOT_CLOSED_COMMENT,
  UNKNOWN_ESCAPE_CHAR,
  UNKNOWN_TOKEN,
};
}

}  // namespace lex
}  // namespace alpha
