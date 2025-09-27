#ifndef CUSTOMER_H
#define CUSTOMER_H

typedef struct Customer {
    int id;
    double arrival;
    double startService;
    double completion;
    struct Customer *next;
} Customer;

void initCustomer(Customer *c, int id, double arrival);

#endif
