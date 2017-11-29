#ifndef _SCHEDULER_FG_H
#define _SCHEDULER_FG_H

#include <map>
#include <queue>
#include <algorithm>
#include <cmath>
#include "scheduler.h"

#define DEBUG

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
    vector<int> ReorderRequest(vector<Request> &vec, unordered_map<int, double>& utility_rate, int &num_of_request);

    vector<Request> GetNextRequests(queue<Request> &q);

    void Allocate(vector<Request> &vec, vector<Allocation> &alloc, vector<int> &index);

    bool CompeteRB(Request &req);

    void Refresh(int current_time);

private:
    // store the timestamp of first RB
    int timestamp;
    // maximum number of time slots in block frame
    int max_time_slots;
    // the maximum ratio of a request that can acquire w.r.t the total RBs
    // in its time interval
    // ratio = size * interval / rb_size * num_channel * interval
    double alloc_threshold;
    // max number of intervals allocated
    int max_intervals;
    // record num of blocks that assigned to a specific user
    map<int, double> alloc_record;
    
    vector<vector<bool> > block_frame;
    vector<int> rb_available;
};

struct RequestPriority {
    int index;
    double priority;
    double rate;

    RequestPriority(int _index = 0, int _priority = 0, double _rate = 0):
        index(_index), priority(_priority), rate(_rate) {} 
};

#endif