#include "event.h"
#include <stdio.h>
#include <stdlib.h>

static Event *eventQueue = NULL;

void resetEventQueue() {
    Event *e;
    while ((e = event_pop()) != NULL) {
        event_free(e);
    }
}

Event* createEvent(EventType type, Customer *cust, Teller *teller, double time) {
    Event *e = malloc(sizeof(Event));
    e->type = type;
    e->cust = cust;
    e->teller = teller;
    e->time = time;
    e->next = NULL;
    return e;
}

void insertEvent(Event *e) {
    if (!eventQueue || e->time < eventQueue->time) {
        e->next = eventQueue;
        eventQueue = e;
        return;
    }
    Event *cur = eventQueue;
    while (cur->next && cur->next->time < e->time) cur = cur->next;
    e->next = cur->next;
    cur->next = e;
}

int isEventQueueEmpty() {
    return eventQueue == NULL;
}

Event* event_pop() {
    if (!eventQueue) return NULL;
    Event *e = eventQueue;
    eventQueue = eventQueue->next;
    e->next = NULL;
    return e;
}

void event_free(Event *e) {
    free(e);
}

// Simple event handling: assume single service time distribution
void handleArrival(Event *e, Teller *tellers, int numTellers, double avgService, int singleQueue) {
    Customer *c = e->cust;
    Teller *chosenTeller = &tellers[0];

    // choose teller with shortest queue
    if (!singleQueue) {
        int minQueue = chosenTeller->queueLen;
        for (int i = 1; i < numTellers; i++) {
            if (tellers[i].queueLen < minQueue) {
                chosenTeller = &tellers[i];
                minQueue = tellers[i].queueLen;
            }
        }
    }

    // start service immediately if teller free
    c->startService = (chosenTeller->queueLen == 0) ? c->arrival : chosenTeller->queueTail->completion;
    c->completion = c->startService + avgService;

    teller_enqueue(chosenTeller, c);
    chosenTeller->totalServiceTime += avgService;

    // schedule departure
    Event *dep = createEvent(EVT_DEPARTURE, c, chosenTeller, c->completion);
    insertEvent(dep);
}

void handleDeparture(Event *e, Teller *tellers, int numTellers, double avgService, int singleQueue) {
    Teller *t = e->teller;
    teller_dequeue(t);
}
