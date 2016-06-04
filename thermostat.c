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

double rescaleVelocities(unsigned int a_N, double* a_v, double a_temp) {
	//declare variables
	double KE;
	double Teff;
	double sumvsq;
	double scalefactor;

	//compute kinetic energy
	KE = computeKE(a_N,a_v);

	//compute effective temperature
	sumvsq = 2.0*KE;
	Teff = sumvsq/(DIM*(a_N-1));

	//compute scaling factor
	scalefactor = sqrt(a_temp/Teff);

	//scale all velocities by this factor
	for (int i = 0; i < a_N; i++) {
		for (int j = 0; j < DIM; j++) {
			a_v[i*DIM + j] = a_v[i*DIM + j]*scalefactor;
		}
	}

	//return previous effective temperature
	return Teff;
}