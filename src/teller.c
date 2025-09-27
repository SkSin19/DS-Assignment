#include "teller.h"
#include <stdlib.h>

void initTeller(Teller *t, int id) {
    t->id = id;
    t->totalServiceTime = 0.0;
    t->queueHead = t->queueTail = NULL;
    t->queueLen = 0;
}

void teller_enqueue(Teller *t, Customer *c) {
    if (!t->queueTail) {
        t->queueHead = t->queueTail = c;
    } else {
        t->queueTail->next = c;
        t->queueTail = c;
    }
    t->queueLen++;
}

Customer* teller_dequeue(Teller *t) {
    if (!t->queueHead) return NULL;
    Customer *c = t->queueHead;
    t->queueHead = t->queueHead->next;
    if (!t->queueHead) t->queueTail = NULL;
    c->next = NULL;
    t->queueLen--;
    return c;
}

int teller_queue_length(Teller *t) {
    return t->queueLen;
}
