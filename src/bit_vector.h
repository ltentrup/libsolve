#pragma once

#include <stdbool.h>
#include <stddef.h>

#define BIT_VECTOR_NO_ENTRY UINT64_MAX

typedef struct bit_vector bit_vector;

bit_vector* bit_vector_init(size_t offset, size_t max_num);
void bit_vector_free(bit_vector*);
void bit_vector_reset(bit_vector*);
void bit_vector_add(bit_vector*, size_t);
void bit_vector_remove(bit_vector*, size_t);
bool bit_vector_contains(bit_vector*, size_t);
void bit_vector_update_or(bit_vector* target, const bit_vector* source);
void bit_vector_update_and(bit_vector* target, const bit_vector* source);
size_t bit_vector_min(bit_vector*);
size_t bit_vector_max(bit_vector*);
bool bit_vector_equal(bit_vector*, bit_vector*);

// Iteration
size_t bit_vector_init_iteration(bit_vector*);
bool bit_vector_iterate(bit_vector*);
size_t bit_vector_next(bit_vector*);

