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
#include "lglib.h"

// Sanity check, make sure the return values are cotrrect
#if (LGL_SATISFIABLE != SATSOLVER_SATISFIABLE) || (LGL_UNSATISFIABLE != SATSOLVER_UNSATISFIABLE) || (LGL_UNKNOWN != SATSOLVER_UNKNOWN)
#error "Return values of SAT solver and the generic SAT solver interface mismatch"
#endif


struct SATSolver {
    LGL* instance;
};

SATSolver* satsolver_init() {
    SATSolver* solver = malloc(sizeof(SATSolver));
    solver->instance = lglinit();
    return solver;
}

void satsolver_free(SATSolver* solver) {
    lglrelease(solver->instance);
    free(solver);
}

int satsolver_new_variable(SATSolver* solver) {
	return lglincvar(solver->instance);
}

void satsolver_add(SATSolver* solver, int lit) {
    lgladd(solver->instance, lit);
    if (lit != 0) {
        lglfreeze(solver->instance, lit);
    }
}

void satsolver_assume(SATSolver* solver, int lit) {
    //lglfreeze(solver->instance, lit);
    lglassume(solver->instance, lit);
}

sat_res satsolver_sat(SATSolver* solver) {
    return lglsat(solver->instance);
}

int satsolver_value(SATSolver* solver, int lit) {
    return lglderef(solver->instance, lit);
}

int satsolver_failed(SATSolver* solver, int lit) {
    return lglfailed(solver->instance, lit);
}

void satsolver_print(SATSolver* solver) {
	printf("\"satsolver_print\" is not implemented\n");
}

const char* satsolver_get_name() {
    return "Lingeling";
}

const char* satsolver_get_version() {
    return lglversion();
}

const char* satsolver_copyright() {
    return "Copyright 2010-2016 Armin Biere";
}
