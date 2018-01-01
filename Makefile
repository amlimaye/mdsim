all:
	gcc -g -c initialization.c
	gcc -g -c potential.c
	gcc -g -c integrator.c
	gcc -g -c writer.c
	gcc -g -c thermostat.c
	gcc -g -c main.c
	gcc -g -o mdsim main.o initialization.o potential.o integrator.o writer.o thermostat.o

clean:
	rm -f mdsim *.o log.txt traj.xyz
