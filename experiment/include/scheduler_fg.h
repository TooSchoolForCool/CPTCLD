#ifndef _SCHEDULER_FG_H
#define _SCHEDULER_FG_H

#include "scheduler.h"

// The SchedulerNull class derives from Scheduler.
// It implements the null scheduling algorithm that returns empty allocation for every request.
//
// Example:
//  Scheduler* scheduler = new SchedulerNull();
//  vector<Allocation> allocations = scheduler->GetAllocation(requests, utility_rate);
//  delete scheduler;
class SchedulerFairGreedy: public Scheduler {
public:
    SchedulerFairGreedy(int _num_channel, double _rb_time, double _rb_size, double _rb_bandwidth);

    // Returns the allocation vector which contains empty allocations for every request in requests.
    vector<Allocation> GetAllocation(vector<Request>& requests, unordered_map<int, double>& utility_rate);
};

#endif