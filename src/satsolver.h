//
//  satsolver.h
//  caqe
//
//  Copyright (c) 2015 - 2016, Leander Tentrup, Saarland University
//
//  Licensed under Apache License v2.0, see LICENSE.txt for information
//

#ifndef SATSOLVER_H
#define SATSOLVER_H

#define SATSOLVER_SATISFIABLE 10
#define SATSOLVER_UNSATISFIABLE 20
#define SATSOLVER_UNKNOWN 0

#include <stdbool.h>

typedef struct SATSolver SATSolver;

typedef enum {
    SATSOLVER_RESULT_SAT     = SATSOLVER_SATISFIABLE,
    SATSOLVER_RESULT_UNSAT   = SATSOLVER_UNSATISFIABLE
} sat_res;

SATSolver* satsolver_init(void);
void satsolver_free(SATSolver*);

int satsolver_new_variable(SATSolver*); 
void satsolver_add(SATSolver*, int lit);
void satsolver_assume(SATSolver*, int lit);
sat_res satsolver_sat(SATSolver*);
int satsolver_value(SATSolver*, int lit);
int satsolver_failed(SATSolver*, int lit);

void satsolver_print(SATSolver*);

const char* satsolver_get_name(void);
const char* satsolver_get_version(void);
const char* satsolver_copyright(void);

#endif
