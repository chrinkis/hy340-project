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

#define FOR_EACH_BYTE_DUAL(BYTE_A, ADDRESS_A, BYTE_B, ADDRESS_B, SIZE) \
  for (char *BYTE_A = ADDRESS_A, *BYTE_B = ADDRESS_B;                  \
       BYTE_A < (char*)(ADDRESS_A) + SIZE; BYTE_A++, BYTE_B++)

static node_t node_new(const void* data, size_t element_size, node_t previous) {
  assert(data);

  node_t self = malloc(sizeof(struct _node));

  if (!self) {
    return NULL;
  }

  self->data = malloc(element_size);

  if (!self->data) {
    free(self);
    self = NULL;

    return NULL;
  }

  FOR_EACH_BYTE_DUAL(src, data, dest, self->data, element_size) {
    *dest = *src;
  }

  self->previous = previous;

  return self;
}

static void node_free(node_t self) {
  assert(self);
  assert(self->data);

  free(self->data);
  self->data = NULL;

  free(self);
  self = NULL;
}

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

int stack_push(const stack_t self, const void* const source) {
  assert(self);
  assert(source);

  node_t node = node_new(source, self->element_size, self->tail);

  if (!node) {
    return 0;
  }

  self->tail = node;

  return 1;
}

void stack_pop(const stack_t self, void* const destination) {
  assert(self);
  assert(!stack_isEmpty(self));

  if (destination) {
    FOR_EACH_BYTE_DUAL(src, self->tail->data, dest, destination,
                       self->element_size) {
      *dest = *src;
    }
  }

  node_t node = self->tail;
  self->tail = node->previous;

  node_free(node);
  node = NULL;
}
