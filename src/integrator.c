#include "integrator.h"

void advanceVelocityVerletTimestep(unsigned int a_N, double a_L, double a_rcut, double a_dt, double* a_r, double* a_v, potfunc_t a_potfunc, double* a_forces, double* a_U) {
	//convenience variables
	double halfdt = a_dt/2.0;

	//advance velocities first
	for (int i = 0; i < a_N; i++) {
		for (int k = 0; k < DIM; k++) {
			a_v[i*DIM + k] += halfdt*a_forces[i*DIM + k];
		}
	}

	//then advance positions, correcting for periodic boundary conditions
	for (int i = 0; i < a_N; i++) {
		for (int k = 0; k < DIM; k++) {
			a_r[i*DIM + k] += a_dt*a_v[i*DIM + k];
			a_r[i*DIM + k] -= a_L*rint(a_r[i*DIM + k]/a_L);
		}
	}

	//do pair computation to get new U,F
	doPairComputation(a_N,a_L,a_rcut,a_r,a_potfunc,a_forces,a_U);

	//advance velocities again
	for (int i = 0; i < a_N; i++) {
		for (int k = 0; k < DIM; k++) {
			a_v[i*DIM + k] += halfdt*a_forces[i*DIM + k];
		}
	}
}