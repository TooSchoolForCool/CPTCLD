#include "scheduler_null.h"

SchedulerNull::SchedulerNull(int _num_channel, double _rb_time, double _rb_size, double _rb_bandwidth):
    Scheduler(_num_channel, _rb_time, _rb_size, _rb_bandwidth) {}

vector<Allocation> SchedulerNull::GetAllocation(vector<Request>& requests, unordered_map<int, double>& utility_rate) {
    return vector<Allocation>(requests.size());
}