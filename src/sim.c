#include "sim.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void run_simulation(int numCustomers, int numTellers, double simTime, double avgService, int mode) {
    Customer customers[numCustomers];
    Teller tellers[numTellers];
    resetEventQueue();

    // init customers and tellers
    for (int i = 0; i < numCustomers; i++) initCustomer(&customers[i], i+1, rand()/(double)RAND_MAX*simTime);
    for (int i = 0; i < numTellers; i++) initTeller(&tellers[i], i+1);

    // schedule all arrivals
    for (int i = 0; i < numCustomers; i++) {
        Event *arr = createEvent(EVT_ARRIVAL, &customers[i], NULL, customers[i].arrival);
        insertEvent(arr);
    }

    // process events
    while (!isEventQueueEmpty()) {
        Event *e = event_pop();
        if (e->type == EVT_ARRIVAL) handleArrival(e, tellers, numTellers, avgService, mode);
        else handleDeparture(e, tellers, numTellers, avgService, mode);
        event_free(e);
    }

    // compute stats
    double totalTime = 0.0, totalTime2 = 0.0, maxWait = 0.0;
    for (int i = 0; i < numCustomers; i++) {
        double wait = customers[i].completion - customers[i].arrival;
        totalTime += wait;
        totalTime2 += wait*wait;
        if (wait > maxWait) maxWait = wait;
    }
    double avgTime = totalTime/numCustomers;
    double stdDev = sqrt(totalTime2/numCustomers - avgTime*avgTime);

    double totalService = 0.0, totalIdle = 0.0;
    for (int i = 0; i < numTellers; i++) {
        totalService += tellers[i].totalServiceTime;
        double idle = simTime - tellers[i].totalServiceTime;
        if (idle < 0) idle = 0.0;
        totalIdle += idle;
    }

    printf("=== Simulation with %d tellers, %s ===\n", numTellers, mode==0?"SINGLE common queue":"SEPARATE queues");
    printf("Total customers served: %d\n", numCustomers);
    printf("Total simulation time: %.2f minutes\n", simTime);
    printf("Average time in bank: %.2f minutes\n", avgTime);
    printf("Std deviation of time in bank: %.2f\n", stdDev);
    printf("Max wait time: %.2f minutes\n", maxWait);
    printf("Total teller service time: %.2f minutes\n", totalService);
    printf("Total teller idle time: %.2f minutes\n\n", totalIdle);
}
