
#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdbool.h>

#define VECTOR_NOT_FOUND ((size_t)-1)

typedef struct {
    void** data;
    size_t size;
    size_t count;
} vector;


vector* vector_init(void);
void vector_free(vector*);

size_t vector_count(const vector*);
void* vector_get(const vector*, size_t i);
size_t vector_find(vector*, void* value);
bool vector_contains(vector*, void* value);
void vector_print(vector*);

void vector_add(vector*, void* value);
void vector_set(vector*, size_t i, void* value);
void vector_insert_at(vector*, size_t i, void* value);
bool vector_remove(vector*, void* value);
void vector_remove_index(vector*, size_t i);
void vector_reset(vector*);
void vector_resize(vector*, size_t value);
void vector_copy(const vector* src, vector* dst);

void vector_add_sorted(vector*, void* value, int (*cmp)(void*, void*));
size_t vector_find_sorted(vector*, void* value, int (*cmp)(void*, void*));

/**
 * Removes all occurrences of NULL from vector.
 */
void vector_compress(vector*);

typedef struct {
    int*   data;
    size_t size;
    size_t count;
} int_vector;

int_vector* int_vector_init(void);
size_t int_vector_count(const int_vector*);
void int_vector_add(int_vector*, int value);
size_t int_vector_add_sorted(int_vector*, int value);
void int_vector_insert_at(int_vector*, size_t index, int value);
void int_vector_set(int_vector*, size_t i, int value);
int int_vector_get(const int_vector*, size_t i);
size_t int_vector_find(int_vector*, int value);
size_t int_vector_find_sorted(int_vector*, int value);
bool int_vector_contains_sorted(int_vector*, int value);
int* int_vector_get_data(int_vector*);
void int_vector_free(int_vector*);
void int_vector_print(int_vector*);
void int_vector_reset(int_vector*);
bool int_vector_remove(int_vector*, int value);
void int_vector_remove_index(int_vector*, size_t index);
bool int_vector_is_sorted(int_vector*);
bool int_vector_equal(const int_vector*, const int_vector*);
void int_vector_copy(const int_vector* src, int_vector* dst);

#endif
