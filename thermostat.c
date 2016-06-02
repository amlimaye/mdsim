#include "thermostat.h"

double computeKE(unsigned int a_N, double* a_v) {
	//initialze KE variable
	double T = 0.0;

	//sum up squared velocities from each particle
	for (int i = 0; i < a_N; i++) {
		for (int j = 0; j < DIM; j++) {
			T += a_v[i*DIM + j]*a_v[i*DIM + j];
		}
	}

	//halve squared velocities to obtain KE
	T = T/2.0;

	//return kinetic energy
	return T;
}