#include "scheduler_fg.h"
#include <iostream>

SchedulerFairGreedy::SchedulerFairGreedy(int _num_channel, double _rb_time, double _rb_size, double _rb_bandwidth):
    Scheduler(_num_channel, _rb_time, _rb_size, _rb_bandwidth) {
        cout << "Init FG" << endl;
    }

vector<Allocation> SchedulerFairGreedy::GetAllocation(vector<Request>& requests, unordered_map<int, double>& utility_rate) {
    return vector<Allocation>(requests.size());
}