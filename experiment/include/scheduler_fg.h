#ifndef _SCHEDULER_FG_H
#define _SCHEDULER_FG_H

#include <map>
#include <queue>
#include <algorithm>
#include <cmath>
#include "scheduler.h"

#define DEBUG
#define MAX_TIME_SLOTS 100

#ifdef DEBUG

#include <iostream>
#include <cstdio>

#endif

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

private:
    void ReorderRequest(vector<Request> &vec, unordered_map<int, double>& utility_rate);

    vector<Request> GetNextRequests(queue<Request> &q);

    void Allocate(vector<Request> &vec, vector<Allocation> &alloc);

private:
    // define maximum allocation size
    double max_alloc_size;
    // store the timestamp of first RB
    int time_shift;
    // maximum number of time slots in block frame
    int max_time_slots;

    map<int, double> alloc_record;
    
    vector<vector<bool> > block_frame;
};

struct RequestPriority {
    int index;
    double priority;
    double bandwidth;

    RequestPriority(int _index = 0, int _priority = 0, double _bandwidth = 0):
        index(_index), priority(_priority), bandwidth(_bandwidth) {} 
};

#endif