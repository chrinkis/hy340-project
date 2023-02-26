#ifndef __ALPHA_TOKEN__
#define __ALPHA_TOKEN__

#include "alpha_token_category.h"

/**
 * @brief Represents a token
 */
typedef struct _alpha_token_t* alpha_token_t;

/**
 * @brief Creates a new `alpha_token_t`
 *
 * @param line The line where the token lives in source file
 * @param sequence_number The number of the token
 * @param content The contents of the token
 * @param category The category of the token
 * @return null if creation failed, else the new token
 *
 * @pre @p content != null
 *
 * @post The contents of the @p content will have been copied into token's
 * memory
 * @post User should call `alpha_token_free` to free the memory that this token
 * holds
 *
 * @see alpha_token_free
 */
alpha_token_t alpha_token_new(unsigned int line,
                              unsigned int sequence_number,
                              const char* const content,
                              alpha_token_category_t category);

/**
 * @brief Frees an `alpha_token_t`
 *
 * @param self The token that this function refers to
 *
 * @pre @p self != null
 *
 * @post All the memory that has been allocated by the @p self, will be freed
 *
 * @see alpha_token_new
 */
void alpha_token_free(alpha_token_t self);

/**
 * @pre @p self != null
 */
unsigned int alpha_token_getLine(const alpha_token_t self);

/**
 * @pre @p self != null
 */
void alpha_token_setLine(const alpha_token_t self, unsigned int line);

/**
 * @pre @p self != null
 */
unsigned int alpha_token_getSequenceNumber(const alpha_token_t self);

/**
 * @pre @p self != null
 */
void alpha_token_setSequenceNumber(const alpha_token_t self,
                                   unsigned int sequence_number);

/**
 * @pre @p self != null
 *
 * @post return != null
 *
 * @warning The returned addressed should not, in any circumstances, freed or
 * mutated without using any of the functions that the API provides.
 */
const char* alpha_token_getContent(const alpha_token_t self);

/**
 * @return 0 if operation failed, else non zero
 *
 * @pre @p self != null
 * @pre @p content != null
 *
 * @post The contents of the @p content will have been copied into token's
 * memory
 *
 * @warning The old contents (if there are any) of @p self will be lost, even if
 * this operation fail
 */
int alpha_token_setContent(const alpha_token_t self, const char* const content);

/**
 * @pre @p self != null
 */
alpha_token_category_t alpha_token_getCategory(const alpha_token_t self);

/**
 * @pre @p self != null
 */
void alpha_token_setCategory(const alpha_token_t self,
                             alpha_token_category_t category);

/**
 * @return 0 if it has not next token, else non zero
 *
 * @pre @p self != null
 */
int alpha_token_hasNext(const alpha_token_t self);

/**
 * @pre @p self != null
 * @pre @p self should have a next token
 *
 * @post return != null
 *
 * @see alpha_token_hasNext
 */
alpha_token_t alpha_token_getNext(const alpha_token_t self);

/**
 * @return non zero if added successfully, else 0
 *
 * @pre @p self != null
 *
 * @note @p next can also be null
 *
 * @warning Be aware of memory leaks. This function doesn't free the "previous"
 * `next` of @p self
 */
int alpha_token_setNext(const alpha_token_t self, const alpha_token_t next);

#endif
