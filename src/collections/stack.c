#include <stack.h>
#include <stdlib.h>

typedef struct _node* node_t;

struct _node {
  void* data;
  struct _node* previous;
};

struct _stack {
  size_t element_size;

  node_t tail;
};

stack_t stack_new(size_t element_size) {
  stack_t self = malloc(sizeof(struct _stack));

  if (!self) {
    return NULL;
  }

  self->element_size = element_size;
  self->tail = NULL;

  return self;
}
