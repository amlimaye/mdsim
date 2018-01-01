SRC_DIR=src
BUILD_DIR=.

all:
	gcc -g -c $(SRC_DIR)/initialization.c -o $(BUILD_DIR)/initialization.o
	gcc -g -c $(SRC_DIR)/potential.c -o $(BUILD_DIR)/potential.o
	gcc -g -c $(SRC_DIR)/integrator.c -o $(BUILD_DIR)/integrator.o
	gcc -g -c $(SRC_DIR)/writer.c -o $(BUILD_DIR)/writer.o
	gcc -g -c $(SRC_DIR)/thermostat.c -o $(BUILD_DIR)/thermostat.o
	gcc -g -c $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.o
	gcc -g -o $(BUILD_DIR)/mdsim $(BUILD_DIR)/main.o \
		$(BUILD_DIR)/initialization.o $(BUILD_DIR)/potential.o \
		$(BUILD_DIR)/integrator.o $(BUILD_DIR)/writer.o \
		$(BUILD_DIR)/thermostat.o

clean:
	rm -f $(BUILD_DIR)/mdsim $(BUILD_DIR)/*.o $(BUILD_DIR)log.txt \
		$(BUILD_DIR)/traj.xyz
