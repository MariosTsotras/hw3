#ifndef EVENT_H
#define EVENT_H
#include "wire.h"

struct Event
{
    uint64_t time;
    Wire* wire;
    char state;
};

typedef struct EventLess {
        //write the operator() required to make this a functor that compares Events by time
    bool operator()(Event* event1, Event* event2) {
        if (event1->time <= event2->time) {
            return true;
        }
        return false;
    }
} EventLess;
	
#endif
