#include "writer.h"

FILE* initializeResultsFile(char* a_fname) {
	//open results file for writing
	FILE* fp;
	fp = fopen(a_fname, "w");

	//write table header into file
	fprintf(fp, "%12s,%12s,%12s,%12s,%12s\n","Step","Time","U","T","H");

	//return file pointer
	return fp;
}

FILE* initializeLogFile(char* a_fname) {
	//open log file for writing
	FILE* fp;
	fp = fopen(a_fname,"w");

	//get current time
	time_t curr_time = time(0);
	char time_buffer[20];
	strftime(time_buffer,20,"%Y-%m-%d %H:%M:%S",localtime(&curr_time));
	
	//write initial message into log file
	fprintf(fp,"Simulation started at: %s\n",time_buffer);

	//return file pointer
	return fp;
}

void writeFirstLogEntry(FILE* a_fp, inputs_t a_inputs) {
	//define a char buffer to hold results from sprintf
	char buffer[46];

	//write various log entries
	writeLogEntry(a_fp,"\nSimulation Parameters:\n");
	sprintf(buffer,"%30s: %12.8f","Box Length",a_inputs.L);
	writeLogEntry(a_fp,buffer);
	sprintf(buffer,"%30s: %12u","Number of Particles",a_inputs.N);
	writeLogEntry(a_fp,buffer);
	sprintf(buffer,"%30s: %12.8f","Lennard-Jones Cutoff Radius",a_inputs.rcut);
	writeLogEntry(a_fp,buffer);
	sprintf(buffer,"%30s: %12u","Number of MD Steps",a_inputs.nsteps);
	writeLogEntry(a_fp,buffer);
	sprintf(buffer,"%30s: %12.8f","Integrator Timestep",a_inputs.dt);
	writeLogEntry(a_fp,buffer);
	sprintf(buffer,"%30s: %12u","Thermostat Interval",a_inputs.therm_interval);
	writeLogEntry(a_fp,buffer);
	sprintf(buffer,"%30s: %12u","Thermostat Stop Step",a_inputs.thermostat_stop_step);
	writeLogEntry(a_fp,buffer);
	sprintf(buffer,"%30s: %12.8f","Target Temperature",a_inputs.target_temp);
	writeLogEntry(a_fp,buffer);
	sprintf(buffer,"%30s: %12u","Writing Interval",a_inputs.write_interval);
	writeLogEntry(a_fp,buffer);
	sprintf(buffer,"%30s: %12u\n","RNG Seed",a_inputs.randseed);
	writeLogEntry(a_fp,buffer);
}

void writeLogEntry(FILE* a_fp, char* a_entry) {
	fprintf(a_fp,"%s\n",a_entry);
}

void writeTimestep(FILE* a_fp, int a_step, double a_dt, double a_U, double a_T) {
	//write log for this timestep into the file
	fprintf(a_fp,"%12d,%12.8f,%12.8f,%12.8f,%12.8f\n",a_step,a_dt*a_step,a_U,a_T,a_U+a_T);
}

void finalizeLogFile(FILE* a_fp) {
	//get current time
	time_t curr_time = time(0);
	char time_buffer[20];
	strftime(time_buffer,20,"%Y-%m-%d %H:%M:%S",localtime(&curr_time));

	//write a final message into log file
	fprintf(a_fp,"Simulation completed at: %s\n",time_buffer);
	
	//close file pointer
	fclose(a_fp);
}

void finalizeResultsFile(FILE* a_fp) {
	//close file pointer
	fclose(a_fp);
}