#include <assert.h>
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

void stack_free(stack_t self) {
  assert(self);

  while (!stack_isEmpty(self)) {
    stack_pop(self, NULL);
  }

  free(self);
  self = NULL;
}

int stack_isEmpty(const stack_t self) {
  assert(self);

  return !self->tail;
}
