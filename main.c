#include "dimensions.h"
#include "initialization.h"
#include "potential.h"
#include "integrator.h"
#include "writer.h"
#include "thermostat.h"

int main(int argc, char** argv) {
	//define box length
	double L = 7;
	
	//define number of particles on a side
	unsigned int nSide = 5;
	unsigned int N = nSide*nSide;

	//define LJ cutoff distance
	double rcut = 2.5;

	//define number of steps
	unsigned int nsteps = 1000000;
	float dt = 0.01;

	//define writing and thermostatting intervals
	unsigned int thermostat_interval = 1;
	unsigned int write_interval = 1000;

	//seed random number generator
	unsigned int randseed = (unsigned int) time(NULL);
	srand(randseed);

	//choose the potential function we want (LJ in this case)
	potfunc_t potfunc = &lj_6_12;

	//initialize log file and results file
	FILE* log_fp = initializeLogFile("log.txt");
	FILE* results_fp = initializeResultsFile("results.txt");

	//write log entries with simulation parameters
	writeFirstLogEntry(log_fp,L,N,rcut,nsteps,dt,randseed,thermostat_interval,write_interval);

	//calculate particle spacing
	double spacing = (double) L/nSide;

	//declare postion, velocity, and forces arrays
	double* r;
	double* v;
	double* F;

	//declare and initialize U,T variables
	double U = 0.0;
	double T = 0.0;

	//initialize position, velocity, and forces arrays
	r = initializeVectorArray(N,0.0);
	v = initializeVectorArray(N,0.0);
	F = initializeVectorArray(N,0.0);

	//place particles on a square lattice
	placeOnSquareLattice(nSide,spacing,r);

	//initialize velocities
	drawRandomVelocities(N,v);

	//remove COM velocity
	removeCOMVelocity(N,v);

	//do first pair computation
	doPairComputation(N,L,rcut,r,potfunc,F,&U);

	//main loop through Verlet integrator timesteps
	for (int step = 0; step < nsteps; step++) {
		advanceVelocityVerletTimestep(N,L,rcut,dt,r,v,potfunc,F,&U);

		//compute KE every time we need to write or thermostat
		if ((step % write_interval == 0) || (step % thermostat_interval == 0)) {
			T = computeKE(N,v);
		}

		//write to log and results file every writing interval
		if (step % write_interval == 0) {
			//write to results file
			writeTimestep(results_fp,step,dt,U,T);

			//write to log file
			char buffer[38];
			sprintf(buffer,"Dumped results at step: %12d",step);
			writeLogEntry(log_fp,buffer);
		}
	}

	//finalize log file and results file
	finalizeLogFile(log_fp);
	finalizeResultsFile(results_fp);

	//free position, velocity, forces arrays
	free(r);
	free(v);
	free(F);

	return 0;
}