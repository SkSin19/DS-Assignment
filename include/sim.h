#ifndef SIM_H
#define SIM_H

#include "customer.h"
#include "teller.h"
#include "event.h"

void run_simulation(int numCustomers, int numTellers, double simTime, double avgService, int mode);

#endif
