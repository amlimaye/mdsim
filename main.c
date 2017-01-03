#include "dimensions.h"
#include "initialization.h"
#include "potential.h"
#include "integrator.h"
#include "writer.h"
#include "thermostat.h"

int main(int argc, char** argv) {
	//declare simulation inputs struct
	inputs_t inputs;

	//define box length
	inputs.L = 7;
	
	//define number of particles on a side
	unsigned int nSide = 5;
	inputs.N = nSide*nSide;

	//define LJ cutoff distance
	inputs.rcut = 2.5;

	//define number of steps
	inputs.nsteps = 20000;
	inputs.dt = 0.01;

	//define writing interval
	inputs.write_interval = 1000;

	//define rescaling thermostat parameters
	inputs.therm_interval = 1000;
	inputs.thermostat_stop_step = 10000;
	inputs.target_temp = 0.5;

	//seed random number generator
	inputs.randseed = (unsigned int) time(NULL);
	srand(inputs.randseed);

	//choose the potential function we want (LJ in this case)
	potfunc_t potfunc = &lj_6_12;

	//initialize log file, results file, and trajectory file
	FILE* log_fp = initializeLogFile("log.txt");
	FILE* results_fp = initializeResultsFile("results.txt");
	FILE* traj_fp = initializeTrjFile("traj.xyz");

	//write log entries with simulation parameters
	writeFirstLogEntry(log_fp,inputs);

	//calculate particle spacing
	double spacing = (double) inputs.L/nSide;

	//declare postion, velocity, and forces arrays
	double* r;
	double* v;
	double* F;

	//declare and initialize U,T,Teff variables
	double U = 0.0;
	double T = 0.0;
	double Teff = 0.0;

	//initialize position, velocity, and forces arrays
	r = initializeVectorArray(inputs.N,0.0);
	v = initializeVectorArray(inputs.N,0.0);
	F = initializeVectorArray(inputs.N,0.0);

	//place particles on a square lattice
	placeOnSquareLattice(nSide,spacing,r);

	//initialize velocities
	drawRandomVelocities(inputs.N,v);

	//remove COM velocity
	removeCOMVelocity(inputs.N,v);

	//do first pair computation
	doPairComputation(inputs.N,inputs.L,inputs.rcut,r,potfunc,F,&U);

	//main loop through Verlet integrator timesteps
	for (int step = 0; step < inputs.nsteps; step++) {
		advanceVelocityVerletTimestep(inputs.N,inputs.L,inputs.rcut,inputs.dt,r,v,potfunc,F,&U);

		//thermostat every thermostat interval
		if ((step % inputs.therm_interval == 0) && (step < inputs.thermostat_stop_step)) {
			Teff = rescaleVelocities(inputs.N,v,inputs.target_temp);

			//write message to log file
			char buffer[81];
			sprintf(buffer,"Rescaled velocities at step: %12d, previous Teff: %12.8f",step,Teff);
			writeLogEntry(log_fp,buffer);
		}

		//write to log and results file every writing interval
		if (step % inputs.write_interval == 0) {
			//compute kinetic energy for writing
			T = computeKE(inputs.N,v);

			//write to results file
			writeTimestep(results_fp,step,inputs.dt,U,T);

			//write to log file
			char buffer[38];
			sprintf(buffer,"Dumped results at step: %12d",step);
			writeLogEntry(log_fp,buffer);
		}

		//write to trajectory file each trajectory interval
		if (step % inputs.trajectory_interval == 0) {
			writePositions(traj_fp,inputs.N,step/inputs.trajectory_interval,r);
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
