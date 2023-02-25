#include "../../include/token/alpha_token_t.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct _alpha_token_t {
  unsigned int line;
  unsigned int sequence_number;

  char* content;
  enum alpha_token_category category;

  struct alpha_token_t* next;
};

alpha_token_t alpha_token_new(unsigned int line,
                              unsigned int sequence_number,
                              const char* const content,
                              enum alpha_token_category category) {
  assert(content);

  alpha_token_t self = malloc(sizeof(struct _alpha_token_t));

  if (!self) {
    return NULL;
  }

  self->line = line;
  self->sequence_number = sequence_number;
  self->category = category;
  self->next = NULL;

  self->content = strdup(content);

  if (!self->content) {
    free(self);
    return NULL;
  }

  assert(self);
  assert(self->line == line);
  assert(self->sequence_number == sequence_number);
  assert(self->content && !strcmp(self->content, content) &&
         self->content != content);
  assert(self->category == category);
  assert(!self->next);

  return self;
}
