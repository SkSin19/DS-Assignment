#include "customer.h"
#include <stdio.h>

void initCustomer(Customer *c, int id, double arrival) {
    c->id = id;
    c->arrival = arrival;
    c->startService = 0.0;
    c->completion = 0.0;
    c->next = NULL;
}
