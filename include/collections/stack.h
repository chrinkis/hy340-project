#ifndef __STACK__
#define __STACK__

#include <stdlib.h>

/**
 * @brief Represents a stack
 */
typedef struct _stack* stack_t;

/**
 * @brief Creates a new `stack_t`
 *
 * @param element_size the size of an element to be stored
 * @return null if creation failed, else the new stack
 *
 * @post User should call `stack_free` to free the memory that this stack
 * holds
 *
 * @see stack_free
 */
stack_t stack_new(size_t element_size);

/**
 * @brief Frees an `stack_t`
 *
 * @param self The stack that this function refers to
 *
 * @pre @p self != null
 *
 * @post All the memory that has been allocated by the @p self, will be freed
 *
 * @see stack_new
 */
void stack_free(stack_t self);

/**
 * @return 0 if there is at least one element in stack, else non zero
 *
 * @pre @p self != null
 */
int stack_isEmpty(const stack_t self);

/**
 * @param source A pointer where this function will copy the element from
 * @return 0 if operation failed, else non zero
 *
 * @pre @p self != null
 * @pre @p source != null
 *
 * @post contents of *(@p source) will be added to stack
 * @post top item in stack will be the *(@p source)
 */
int stack_push(const stack_t self, const void* const source);

/**
 * @param destination A pointer where this function will copy the poped element
 * to
 *
 * @pre @p self != null
 * @pre stack should not be empty
 *
 * @post contents of poped destination will be copied to *(@p destination)
 * @post top item in stack will no longer be in stack
 *
 * @note If @destination is null, then the poped item will not be copied.
 *
 * @see stack_isEmpty
 */
void stack_pop(const stack_t self, void* const destination);

#endif
