#include <assert.h>
#include <stdio.h>

#include "satsolver.h"

int main(int argc, const char* argv[]) {
    
    SATSolver* sat = satsolver_init();
    int a = satsolver_new_variable(sat);
    int b = satsolver_new_variable(sat);
	assert(a != b);
	assert(a > 0 && b > 0);
	printf("a: %d, b: %d\n", a, b);
    
    satsolver_add(sat, a);
    satsolver_add(sat, b);
    satsolver_add(sat, 0);
    
    assert(satsolver_sat(sat) == SATSOLVER_RESULT_SAT);
	
	satsolver_add(sat, -b);
	satsolver_add(sat, 0);
	
	assert(satsolver_sat(sat) == SATSOLVER_RESULT_SAT);
	assert(satsolver_value(sat, a) > 0);
	
	satsolver_assume(sat, -a);
	satsolver_assume(sat, -b);
	
	assert(satsolver_sat(sat) == SATSOLVER_RESULT_UNSAT);
	assert(satsolver_failed(sat, -a));
	assert(!satsolver_failed(sat, -b));
    
    return 0;
}