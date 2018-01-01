#include "potential.h"
#include "initialization.h"

void doPairComputation(unsigned int a_N, double a_L, double a_rcut, double* a_r, potfunc_t a_potfunc, double* a_forces, double* a_U) {
	//define some convenience values
	double	force[DIM];
	double 	energy;
	double 	deltar[DIM];
	double 	deltar2;
	double 	rcut2 = a_rcut*a_rcut;

	//reset forces in a_forces array to all zeros
	for (int i = 0; i < a_N*DIM; i++) {
		a_forces[i] = 0.0;
	}

	//reset a_U to zero
	*(a_U) = 0;

	//loop through all pairs to compute forces
	for (int i = 0; i < a_N; i++) {
		for (int j = 0; j < a_N; j++) {
			//do not compute self-interactions
			if (i != j) {
				//compute distance between pairs, adjusting for periodic boundary conditions
				for (int k = 0; k < DIM; k++) {
					deltar[k] = a_r[i*DIM + k] - a_r[j*DIM +k];
					deltar[k] = deltar[k] - a_L*rint(deltar[k]/a_L);
				}

				//compute magnitude of this deltar vector, store in deltar2
				deltar2 = 0.0;
				for (int k = 0; k < DIM; k++) {
					deltar2 += deltar[k]*deltar[k];
				}

				//reset force array for this pair to all zeros
				for (int k = 0; k < DIM; k++) {
					force[k] = 0.0;
				}

				//reset energy to 0.0 for this pair
				energy = 0.0;

				//get new force and energy for this pair
				(*a_potfunc)(rcut2,deltar2,force,&energy);

				//add the force contribution from this i,j pair to the force on particle i
				for (int k = 0; k < DIM; k++) {
					a_forces[i*DIM + k] += force[k]*deltar[k];
				}

				//add the potential between this pair to the total potential
				*(a_U) += energy;
			}
		}
	}

	//correct energy for double counting
	*(a_U) = *(a_U)/2.0;
}

void lj_6_12(double a_rcut2, double a_deltar2, double* a_force, double* a_energy) {
	//declare higher powers of deltar
	double deltar4, deltar8, deltar14;

	//check rcut
	if (a_deltar2 < a_rcut2) {
		//compute higher powers of deltar2
		deltar4 = a_deltar2*a_deltar2;
		deltar8 = deltar4*deltar4;
		deltar14 = deltar8*deltar4*a_deltar2;

		//assign force into a_force
		for (int k = 0; k < DIM; k++) {
			a_force[k] += 48*((1.0/deltar14) - 0.5*(1.0/deltar8));
		}

		//finally return the energy of this pair
		*(a_energy) = 4*(pow(a_deltar2,-6) - pow(a_deltar2,-3)) - 4*(pow(a_rcut2,-6) - pow(a_rcut2,-3));
	}
	//else if outside rcut just assign zero force for all components, return 0.0 for energy
	else {
		for (int k = 0; k < DIM; k++) {
			a_force[k] = 0.0;
		}
		*(a_energy) = 0.0;
	}
}