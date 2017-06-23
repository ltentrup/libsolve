//
//  satsolver_picosat.c
//  caqe
//
//  Copyright (c) 2015 - 2016, Leander Tentrup, Saarland University
//
//  Licensed under Apache License v2.0, see LICENSE.txt for information
//

#include "satsolver.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include "picosat.h"

// Sanity check, make sure the return values are cotrrect
#if (PICOSAT_SATISFIABLE != SATSOLVER_SATISFIABLE) || (PICOSAT_UNSATISFIABLE != SATSOLVER_UNSATISFIABLE) || (PICOSAT_UNKNOWN != SATSOLVER_UNKNOWN)
#error "Return values of SAT solver and the generic SAT solver interface mismatch"
#endif


#define PICOSAT_DECISION_LIMIT -1

struct SATSolver {
    PicoSAT* instance;
};

SATSolver* satsolver_init() {
    SATSolver* solver = malloc(sizeof(SATSolver));
    solver->instance = picosat_init();
    return solver;
}

void satsolver_free(SATSolver* solver) {
    picosat_reset(solver->instance);
    free(solver);
}

int satsolver_new_variable(SATSolver* solver) {
	return picosat_inc_max_var(solver->instance);
}

void satsolver_add(SATSolver* solver, int lit) {
    picosat_add(solver->instance, lit);
}

void satsolver_assume(SATSolver* solver, int lit) {
    picosat_assume(solver->instance, lit);
}

sat_res satsolver_sat(SATSolver* solver) {
    return picosat_sat(solver->instance, PICOSAT_DECISION_LIMIT);
}

int satsolver_value(SATSolver* solver, int lit) {
    return picosat_deref(solver->instance, lit);
}

int satsolver_failed(SATSolver* solver, int lit) {
	return picosat_failed_assumption(solver->instance, lit);
}

void satsolver_print(SATSolver* solver) {
	picosat_print(solver->instance, stdout);
}

const char* satsolver_get_name() {
    return "PicoSAT";
}

const char* satsolver_get_version() {
    return "965";
}

const char* satsolver_copyright() {
    return picosat_copyright();
}
