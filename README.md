# mdsim
Simple implementation of a molecular dynamics integrator written in C. Mostly done for personal education.

Uses the velocity Verlet algorithm to evolve the dynamics of Lennard-Jones spheres in an arbitrary number of dimensions (set at compile time). Only implemented the (bad) velocity rescaling thermostat. Writes trajectory output to a .xyz file.
