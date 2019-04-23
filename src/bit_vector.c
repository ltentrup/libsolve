#include "bit_vector.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef uint64_t word;

// Implement clausal abstraction as bit-vector
struct bit_vector {
    size_t offset;
    size_t max;
    size_t num_words;
    size_t iteration;
    word* data;
};

bit_vector* bit_vector_init(size_t offset, size_t max_num) {
    bit_vector* ca = malloc(sizeof(bit_vector));
    ca->offset = offset;
    ca->max = max_num;
    ca->num_words = max_num / sizeof(word) + 1;
    ca->data = malloc(sizeof(word) * ca->num_words);
    bit_vector_reset(ca);
    return ca;
}

void bit_vector_free(bit_vector* bv) {
    if (bv == NULL) {
        return;
    }
    free(bv->data);
    free(bv);
}

void bit_vector_reset(bit_vector* ca) {
    memset(ca->data, 0, ca->num_words * sizeof(word));
}

void bit_vector_add(bit_vector* ca, size_t index) {
    assert(index < ca->max);
    size_t bv_index = index - ca->offset;
    size_t word_num = bv_index / sizeof(word);
    size_t position = bv_index % sizeof(word);
    ca->data[word_num] |= ((word)1 << position);
}

void bit_vector_remove(bit_vector* ca, size_t index) {
    size_t bv_index = index - ca->offset;
    size_t word_num = bv_index / sizeof(word);
    size_t position = bv_index % sizeof(word);
    ca->data[word_num] &= ~((word)1 << position);
}

bool bit_vector_contains(bit_vector* ca, size_t index) {
    assert(index < ca->max);
    size_t bv_index = index - ca->offset;
    size_t word_num = bv_index / sizeof(word);
    size_t position = bv_index % sizeof(word);
    return ca->data[word_num] & ((word)1 << position);
}

void bit_vector_update_or(bit_vector* target, const bit_vector* source) {
    assert(target->offset == source->offset);
    size_t min = target->num_words > source->num_words ? source->num_words : target->num_words;
    for (size_t i = 0; i < min; i++) {
        target->data[i] |= source->data[i];
    }
}

void bit_vector_update_and(bit_vector* target, const bit_vector* source) {
    assert(target->offset == source->offset);
    size_t min = target->num_words > source->num_words ? source->num_words : target->num_words;
    for (size_t i = 0; i < min; i++) {
        target->data[i] &= source->data[i];
    }
}

size_t bit_vector_min(bit_vector* bv) {
    for (size_t i = 0; i < bv->max; i++) {
        size_t word_num = i / sizeof(word);
        size_t position = i % sizeof(word);
        if (bv->data[word_num] & ((word)1 << position)) {
            return i + bv->offset;
        }
    }
    return BIT_VECTOR_NO_ENTRY;
}

size_t bit_vector_max(bit_vector* bv) {
    for (size_t i = 0; i < bv->max; i++) {
        size_t j = bv->max - i - 1;
        size_t word_num = j / sizeof(word);
        size_t position = j % sizeof(word);
        if (bv->data[word_num] & ((word)1 << position)) {
            return j + bv->offset;
        }
    }
    return BIT_VECTOR_NO_ENTRY;
}

bool bit_vector_equal(bit_vector* lhs, bit_vector* rhs) {
    assert(lhs->offset == rhs->offset);
    size_t min = lhs->num_words > rhs->num_words ? lhs->num_words : rhs->num_words;
    for (size_t i = 0; i < min; i++) {
        if (lhs->data[i] != rhs->data[i]) {
            return false;
        }
    }
    return true;
}

// Iteration

size_t bit_vector_init_iteration(bit_vector* ca) {
    ca->iteration = 0;
    return bit_vector_next(ca);
}

bool bit_vector_iterate(bit_vector* ca) {
    assert(ca->iteration > 0);
    return ca->iteration - 1 < ca->max;
}

size_t bit_vector_next(bit_vector* ca) {
    for (size_t i = ca->iteration; i < ca->max; i++) {
        size_t word_num = i / sizeof(word);
        size_t position = i % sizeof(word);
        if (ca->data[word_num] == 0) {
            i = sizeof(word) * (word_num + 1) - 1;
            continue;
        }
        if (ca->data[word_num] & ((word)1 << position)) {
            ca->iteration = i + 1;
            return i + ca->offset;
        }
    }
    ca->iteration = ca->max + 1;
    return BIT_VECTOR_NO_ENTRY;
}
