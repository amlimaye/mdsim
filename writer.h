#ifndef WRITER_H
#define WRITER_H

#include <stdio.h>
#include <time.h>
#include "dimensions.h"

//typedef for simulation inputs
typedef struct {
	double L;
	unsigned int N;
	double rcut;
	unsigned int nsteps;
	double dt;
	unsigned int randseed;
	unsigned int therm_interval;
	unsigned int thermostat_stop_step;
	double target_temp;
	unsigned int write_interval;
} inputs_t;

FILE* 	initializeResultsFile(char* a_fname);
FILE*	initializeLogFile(char* a_fname);
void	writeFirstLogEntry(FILE* a_fp, inputs_t a_inputs);
void	writeLogEntry(FILE* a_fp, char* a_entry);
void 	writeTimestep(FILE* a_fp, int a_step, double a_dt, double a_U, double a_T);
void	finalizeLogFile(FILE* a_fp);
void 	finalizeResultsFile(FILE* a_fp);

#endif