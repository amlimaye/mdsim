#ifndef WRITER_H
#define WRITER_H

#include <stdio.h>
#include <time.h>
#include "dimensions.h"

FILE* 	initializeResultsFile(char* a_fname);
FILE*	initializeLogFile(char* a_fname);
void	writeFirstLogEntry(FILE* a_fp, double a_L, unsigned int a_N, double a_rcut, unsigned int a_nsteps, double a_dt, unsigned int a_randseed, double a_therm_interval, double a_write_interval);
void	writeLogEntry(FILE* a_fp, char* a_entry);
void 	writeTimestep(FILE* a_fp, int a_step, double a_dt, double a_U, double a_T);
void	finalizeLogFile(FILE* a_fp);
void 	finalizeResultsFile(FILE* a_fp);

#endif