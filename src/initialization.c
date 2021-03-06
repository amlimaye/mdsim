#include "initialization.h"

static inline double myrand() {
	return (double) rand() / (double) RAND_MAX;
}

void removeCOMVelocity(unsigned int a_N, double* a_velocityPtr) {
	//compute center of mass velocity
	double comVelocity[DIM];
	for (int i = 0; i < a_N; i++) {
		for (int k = 0; k < DIM; k++) {
			comVelocity[k] += a_velocityPtr[i*DIM + k]/a_N;
		}
	}

	//subtract off COM velocity
	for (int i =0; i < a_N; i++) {
		for (int k = 0; k < DIM; k++){
			a_velocityPtr[i*DIM + k] -= comVelocity[k];
		}
	}
}

void drawRandomVelocities(unsigned int a_N, double* a_velocityPtr) {
	for (int i = 0; i < a_N; i++) {
		for (int k = 0; k < DIM; k++) {
			//draw velocities from a symmetric random distribution over [-0.5, 0.5)
			a_velocityPtr[i*DIM + k] = myrand() - 0.5;
		}
	}
}

void placeOnSquareLattice(unsigned int a_nSide, double a_spacing, double* a_positionsPtr) {
	//some declarations
	int index = 0;
	double xPos;
	double yPos;
	double zPos;

	//double loop through particles on a side in each dimension
	for (int i = 0; i < a_nSide; i++) {
		for (int j = 0; j < a_nSide; j++) {
			for (int k = 0; k < a_nSide; k++) {
				//set positions for this particle
				xPos = i*a_spacing;
				yPos = j*a_spacing;
				zPos = k*a_spacing;

				//write these positions into positions array
				a_positionsPtr[index*DIM] = xPos;
				a_positionsPtr[index*DIM+1] = yPos;
				a_positionsPtr[index*DIM+2] = zPos;

				//increment index variable
				index++;	
			}
		}
	}
}

double* initializeVectorArray(unsigned int a_N, double a_initValue) {
	//calculate number of elements in array
	int nElements = DIM*a_N;

	//malloc array space for all elements
	double *v_array;
	v_array = (double*) malloc(sizeof(double)*nElements);

	//initialize all array elements to zero
	for (int i = 0; i < a_N; i++) {
		for (int j = 0; j < DIM; j++) {
			v_array[i*DIM + j] = a_initValue;
		}
	}

	//return pointer to vector array
	return v_array;
}

void printVectorArray(unsigned int a_N, double* a_arrayPtr) {
	//iterate through vector array and print it
	for (int i = 0; i < a_N; i++) {

		//print vector open bracket
		printf("%s", VEC_OB);

		//loop through vector elements
		for (int j = 0; j < DIM; j++) {

			//don't print last comma if at last element of the vector
			if (j < DIM-1){
				printf("%0.4f,", a_arrayPtr[i*DIM + j]);
			} else {
				printf("%0.4f", a_arrayPtr[i*DIM + j]);
			}
		}

		//print vector close bracket
		printf("%s\n", VEC_CB);
	}
}