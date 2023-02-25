#include "../../include/token/alpha_token.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define FIXME assert(0);

struct _alpha_token_t {
  unsigned int line;
  unsigned int sequence_number;

  char* content;
  alpha_token_category_t category;

  alpha_token_t next;
};

alpha_token_t alpha_token_new(unsigned int line,
                              unsigned int sequence_number,
                              const char* const content,
                              alpha_token_category_t category) {
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
    self = NULL;
    return NULL;
  }

  assert(self);
  assert(self->line == line);
  assert(self->sequence_number == sequence_number);
  assert(self->content);
  assert(!strcmp(self->content, content));
  assert(self->content != content);
  assert(self->category == category);
  assert(!self->next);
  return self;
}

void alpha_token_free(alpha_token_t self) {
  assert(self);
  assert(self->content);

  free(self->content);
  self->content = NULL;
  free(self);
  self = NULL;
}

unsigned int alpha_token_getLine(const alpha_token_t self) {
  assert(self);

  unsigned int result = self->line;

  assert(result == self->line);
  return result;
}

void alpha_token_setLine(const alpha_token_t self, unsigned int line) {
  assert(self);

  self->line = line;

  assert(self->line == line);
}

unsigned int alpha_token_getSequenceNumber(const alpha_token_t self) {
  assert(self);

  unsigned int result = self->sequence_number;

  assert(result == self->sequence_number);
  return result;
}

void alpha_token_setSequenceNumber(const alpha_token_t self,
                                   unsigned int sequence_number) {
  assert(self);

  self->sequence_number = sequence_number;

  assert(self->sequence_number == sequence_number);
}

const char* alpha_token_getContent(const alpha_token_t self) {
  assert(self);

  const char* const result = self->content;

  assert(result);
  return result;
}

void alpha_token_setContent(const alpha_token_t self,
                            const char* const content) {
  assert(self);
  assert(content);

  if (self->content) {
    free(self->content);
    self->content = NULL;
  }

  self->content = strdup(content);

  if (!self->content) {
    FIXME
  }

  assert(self->content);
  assert(!strcmp(self->content, content));
  assert(self->content != content);
}

alpha_token_category_t alpha_token_getCategory(const alpha_token_t self) {
  assert(self);

  alpha_token_category_t result = self->category;

  assert(result == self->category);
  return result;
}

void alpha_token_setCategory(const alpha_token_t self,
                             alpha_token_category_t category) {
  assert(self);

  self->category = category;

  assert(self->category == category);
}

int alpha_token_hasNext(const alpha_token_t self) {
  assert(self);

  return !!self->next;
}

alpha_token_t alpha_token_getNext(const alpha_token_t self) {
  assert(self);
  assert(alpha_token_hasNext(self));

  alpha_token_t result = self->next;

  assert(result);
  return result;
}

int alpha_token_setNext(const alpha_token_t self, const alpha_token_t next) {
  assert(self);

  self->next = next;

  assert(self->next == next);
  return 1;
}
