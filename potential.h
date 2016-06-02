#ifndef POTENTIAL_H
#define POTENTIAL_H

#include "dimensions.h"
#include <math.h>

//typedef for a single potential function for pair computation (LJ, Buckingham, Yukawa, etc.)
typedef void (*potfunc_t) (double,double,double*,double*);

void 	doPairComputation(unsigned int a_N, double a_L, double  a_rcut, double* a_r, potfunc_t a_potfunc, double* a_forces, double* a_U);
void	lj_6_12(double a_rcut2, double a_deltar2, double* a_force, double* a_energy);

#endif //POTENTIAL_H