#ifndef EVENT_H
#define EVENT_H

#include "customer.h"
#include "teller.h"

typedef enum { EVT_ARRIVAL, EVT_DEPARTURE } EventType;

typedef struct Event {
    EventType type;
    double time;
    Customer *cust;
    Teller *teller;
    struct Event *next;
} Event;

void resetEventQueue();
Event* createEvent(EventType type, Customer *cust, Teller *teller, double time);
void insertEvent(Event *e);
int isEventQueueEmpty();
Event* event_pop();
void event_free(Event *e);

void handleArrival(Event *e, Teller *tellers, int numTellers, double avgService, int singleQueue);
void handleDeparture(Event *e, Teller *tellers, int numTellers, double avgService, int singleQueue);

#endif
