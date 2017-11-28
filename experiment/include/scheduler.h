#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include <vector>
#include "allocation.h"
#include "request.h"

// The Scheduler class encapsulates the scheduling algorithm and provides the interface to get allocation result based on requests
//
// If called directly, the Scheduler returns empty allocation for every request.
// Example:
//  Scheduler scheduler;
//  vector<Allocation> allocations = scheduler.GetAllocation(requests, utility);
//
// Suggest creating new SchedulerXXX class derving from Scheduler.
// Example:
//  class SchedulerNull: public Scheduler {
//      SchedulerNull(int _num_channel, double _rb_time, double _rb_size, double _rb_rate);
//      vector<Allocation> GetAllocation(vector<Request>& requests, unordered_map<int, double>& utility);
//  } 
class Scheduler {
protected:
    // Number of channels, which indicates how many RB can be used at the same time
    int num_channel;
    // Attributes of RB (rb_size = rb_rate * rb_time)
    double rb_time;
    double rb_size;
    double rb_rate;

public:
    Scheduler(int _num_channel, double _rb_time, double _rb_size, double _rb_rate);
    virtual ~Scheduler();

    // Interface of the Scheduling Algorithm.
    // Should be overrided in derived SchedulerXXX class.
    // Returns the allocation vector of the same size of requests, in which each allocations[i] corresponds to requests[i].
    virtual vector<Allocation> GetAllocation(vector<Request>& requests, unordered_map<int, double>& utility);
};

#endif