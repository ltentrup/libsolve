//
//  satsolver_glucose.cc
//  caqe
//
//  Copyright (c) 2015 - 2016, Leander Tentrup, Saarland University
//
//  Licensed under Apache License v2.0, see LICENSE.txt for information
//

extern "C" {
#include "satsolver.h"
}

#include <set>

#include <assert.h>
#include <stdbool.h>
#include "core/Solver.h"
#include "mtl/Vec.h"

using namespace Glucose;
using namespace std;

struct SATSolver {
    Solver* instance;
    vec<Lit> clause;
    vec<Lit> assumptions;
    std::set<Lit> conflict;
    bool last_sat_call;
};

static Lit lit_from_int(SATSolver* solver, int lit) {
    bool neg = lit < 0;
    int var = neg ? -lit : lit;
    
    assert(var > 0);
    return mkLit(var - 1, neg);
}

static int int_from_lit(SATSolver* solver, Lit lit) {
    int variable = var(lit) + 1;
	assert(variable >= 0);
    bool negated = sign(lit);
    return negated ? -variable : variable;
}

SATSolver* satsolver_init() {
    SATSolver* solver = new SATSolver;
    solver->instance = new Solver();
    solver->last_sat_call = false;
    
    return solver;
}

void satsolver_free(SATSolver* solver) {
    delete solver->instance;
    delete solver;
}

int satsolver_new_variable(SATSolver* solver) {
	Var var = solver->instance->newVar();
    return int_from_lit(solver, mkLit(var, false));
}

void satsolver_add(SATSolver* solver, int lit) {
    if (lit == 0) {
        solver->instance->addClause(solver->clause);
        solver->clause.clear();
    } else {
        Lit l = lit_from_int(solver, lit);
        solver->clause.push(l);
    }
}

void satsolver_assume(SATSolver* solver, int lit) {
    if (solver->last_sat_call) {
        solver->assumptions.clear();
        solver->last_sat_call = false;
    }
    solver->assumptions.push(lit_from_int(solver, lit));
}

sat_res satsolver_sat(SATSolver* solver) {
    if (solver->last_sat_call) {
        solver->assumptions.clear();
        solver->last_sat_call = false;
    }
    sat_res res = solver->instance->solve(solver->assumptions) ? SATSOLVER_RESULT_SAT : SATSOLVER_RESULT_UNSAT;
    solver->last_sat_call = true;
    if (res == SATSOLVER_RESULT_UNSAT) {
        solver->conflict.clear();
        for (int i = 0; i < solver->instance->conflict.size(); i++) {
            solver->conflict.insert(solver->instance->conflict[i]);
        }
    }
    return res;
}

int satsolver_value(SATSolver* solver, int lit) {
    lbool res = solver->instance->modelValue(lit_from_int(solver, lit));
    if (res == l_True) {
        return 1;
    } else if (res == l_False) {
        return -1;
    } else if (res == l_Undef) {
        return 0;
    }
    assert(false);
    return 0;
}

int satsolver_failed(SATSolver* solver, int lit) {
    return solver->conflict.find(~lit_from_int(solver, lit)) != solver->conflict.end();
}

void satsolver_print(SATSolver* solver) {
	printf("\"satsolver_print\" is not implemented\n");
}

const char* satsolver_get_name() {
    return "Glucose";
}

const char* satsolver_get_version() {
    return "4.1";
}

const char* satsolver_copyright() {
    return "Copyright 2009-2014, Gilles Audemard, Laurent Simon";
}


