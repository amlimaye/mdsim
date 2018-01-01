#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <math.h>
#include "dimensions.h"
#include "potential.h"

void advanceVelocityVerletTimestep(unsigned int a_N, double a_L, double a_rcut, double a_dt, double* a_r, double* a_v, potfunc_t a_potfunc, double* a_forces, double* a_U);

#endif