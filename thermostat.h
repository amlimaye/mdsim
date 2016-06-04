#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "dimensions.h"
#include <math.h>

double computeKE(unsigned int a_N, double* a_v);
double rescaleVelocities(unsigned int a_N, double* a_v, double a_T);

#endif