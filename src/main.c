#include "sim.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s #customers #tellers simulationTime averageServiceTime\n", argv[0]);
        return 1;
    }

    int numCustomers = atoi(argv[1]);
    int numTellers = atoi(argv[2]);
    double simTime = atof(argv[3]);
    double avgService = atof(argv[4]);


    run_simulation(numCustomers, numTellers, simTime, avgService, 0);


    run_simulation(numCustomers, numTellers, simTime, avgService, 1);

    return 0;
}
