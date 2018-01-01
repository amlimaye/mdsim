#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include "dimensions.h"
#include <stdio.h>	//printf()
#include <stdlib.h>	//malloc(),srand(),rand()
#include <time.h>	//time()
#define VEC_OB "<"
#define VEC_CB ">"

void 					drawRandomVelocities(unsigned int a_N, double* a_velocityPtr);
double* 				initializeVectorArray(unsigned int a_N, double a_initValue);
static inline double 	myrand();
void 					placeOnSquareLattice(unsigned int a_nSide, double a_spacing, double* a_positionsPtr);
void 					printVectorArray(unsigned int a_N, double* a_arrayPtr);
void					removeCOMVelocity(unsigned int a_N, double* a_velocityPtr);

#endif //INITIALIZATION_H