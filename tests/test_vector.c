#include <stdio.h>
#include <assert.h>

#include "vector.h"

static bool insert_sorted_empty() {
	int_vector* vector = int_vector_init();
	size_t index = int_vector_add_sorted(vector, 2);
	assert(index == 0);
	assert(int_vector_count(vector) == 1);
	assert(int_vector_get(vector, 0) == 2);
	return true;
}

static bool create_simple() {
    int_vector* vector = int_vector_init();
    for (int i = 0; i < 10000; i++) {
        int_vector_add(vector, i);
    }
	return true;
}


int main(int argc, const char* argv[]) {
    
	assert(create_simple());
	assert(insert_sorted_empty());
    
    return 0;
}