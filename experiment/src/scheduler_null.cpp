#include "scheduler_null.h"

SchedulerNull::SchedulerNull(int _num_channel, double _RB_time, double _RB_size, double _RB_bandwidth):
    Scheduler(_num_channel, _RB_time, _RB_size, _RB_bandwidth) {}

vector<Allocation> SchedulerNull::GetAllocation(vector<Request>& requests, unordered_map<int, double>& utility_rate) {
    return vector<Allocation>(requests.size());
}