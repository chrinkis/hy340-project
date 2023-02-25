#include "../../include/token/alpha_token_t.h"

struct _alpha_token_t {
  unsigned int line;
  unsigned int sequence_number;

  char* content;
  enum alpha_token_category category;

  struct alpha_token_t* next;
};
