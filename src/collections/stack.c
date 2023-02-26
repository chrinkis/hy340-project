#include <stack.h>

typedef struct _node* node_t;

struct _node {
  void* data;
  struct _node* previous;
};

struct _stack {
  size_t element_size;

  node_t tail;
};
