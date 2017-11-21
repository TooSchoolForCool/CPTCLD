#ifndef _SCHEDULER_NULL_H
#define _SCHEDULER_NULL_H

#include "scheduler.h"

class SchedulerNull: public Scheduler {
public:
    SchedulerNull(int _num_channel, double _RB_time, double _RB_size, double _RB_bandwidth);
    vector<Allocation> GetAllocation(vector<Request>& requests, unordered_map<int, double>& utility_rate);
};

#endif