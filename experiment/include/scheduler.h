#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include "allocation.h"
#include "requests.h"

class Scheduler {
protected:
    int num_channel;
    double RB_time;
    double RB_size;
    double RB_bandwidth;
    double start_time;
    double end_time;

public:
    Scheduler(int _num_channel, double _RB_time, double _RB_size, double _RB_bandwidth);
    virtual vector<Allocation> GetAllocation(vector<Request>& requests, unordered_map<int, double>& utility_rate);
};

#endif