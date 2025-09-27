#ifndef TELLER_H
#define TELLER_H

#include "customer.h"

typedef struct Teller {
    int id;
    double totalServiceTime;
    struct Customer *queueHead;
    struct Customer *queueTail;
    int queueLen;
} Teller;

void initTeller(Teller *t, int id);
void teller_enqueue(Teller *t, Customer *c);
Customer* teller_dequeue(Teller *t);
int teller_queue_length(Teller *t);

#endif
