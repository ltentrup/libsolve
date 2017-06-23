
extern "C" {
#include "satsolver.h"
}

#include <cryptominisat5/cryptominisat.h>
#include <assert.h>
#include <vector>
#include <stdbool.h>
#include <set>


struct SATSolver {
    CMSat::SATSolver* instance;
    std::vector<CMSat::Lit> clause;
    std::vector<CMSat::Lit> assumptions;
    //const std::vector<CMSat::Lit>* conflict;
    //std::vector<CMSat::Lit>::const_iterator conflict_iterator;
    std::set<CMSat::Lit> conflict;
    bool last_sat_call;
};

static CMSat::Lit lit_from_int(SATSolver* solver, int lit) {
    bool neg = lit < 0;
    int var = neg ? -lit : lit;
    
    assert(var > 0);
    return CMSat::Lit(var - 1, neg);
}

static int int_from_lit(SATSolver* solver, CMSat::Lit lit) {
    CMSat::Lit var = lit.unsign();
    assert(!var.sign());
    bool negated = lit != var;
    int variable = var.var() + 1;
    return negated ? -variable : variable;
}

SATSolver* satsolver_init() {
    SATSolver* solver = new SATSolver;
    solver->instance = new CMSat::SATSolver();
    solver->last_sat_call = false;
    
    //solver->instance->set_no_simplify();
    //solver->instance->set_greedy_undef();
    solver->instance->set_num_threads(1);
    
    return solver;
}

void satsolver_free(SATSolver* solver) {
    delete solver->instance;
    delete solver;
}

int satsolver_new_variable(SATSolver* solver) {
    solver->instance->new_var();
    CMSat::Lit var = CMSat::Lit(solver->instance->nVars() - 1, false);
    return int_from_lit(solver, var);
}

void satsolver_add(SATSolver* solver, int lit) {
    if (lit == 0) {
        solver->instance->add_clause(solver->clause);
        solver->clause.clear();
    } else {
        CMSat::Lit l = lit_from_int(solver, lit);
        solver->clause.push_back(l);
    }
}

void satsolver_assume(SATSolver* solver, int lit) {
    if (solver->last_sat_call) {
        solver->assumptions.clear();
        solver->last_sat_call = false;
    }
    solver->assumptions.push_back(lit_from_int(solver, lit));
}

sat_res satsolver_sat(SATSolver* solver) {
    if (solver->last_sat_call) {
        solver->assumptions.clear();
        solver->last_sat_call = false;
    }
    CMSat::lbool satisfiable = solver->instance->solve(&solver->assumptions);
    sat_res res = (satisfiable == CMSat::l_True) ? SATSOLVER_RESULT_SAT : SATSOLVER_RESULT_UNSAT;
    solver->last_sat_call = true;
    if (res == SATSOLVER_RESULT_UNSAT) {
        solver->conflict.clear();
        solver->conflict.insert(solver->instance->get_conflict().begin(), solver->instance->get_conflict().end());
    }
    return res;
}

int satsolver_value(SATSolver* solver, int lit) {
    CMSat::Lit l = lit_from_int(solver, lit);
    CMSat::lbool res = solver->instance->get_model()[l.var()];
    int result = l.sign() ? -1 : 1;
    if (res == CMSat::l_True) {
        return result;
    } else if (res == CMSat::l_False) {
        return -result;
    } else if (res == CMSat::l_Undef) {
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
    return "cryptominisat";
}

const char* satsolver_get_version() {
    return "5.0.0";
}

const char* satsolver_copyright() {
    return "Copyright 2009-2015 Mate Soos";
}
