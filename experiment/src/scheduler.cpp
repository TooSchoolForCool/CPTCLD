#include "scheduler.h"

Scheduler::Scheduler(int _num_channel, double _RB_time, double _RB_size, double _RB_bandwidth):
    num_channel(_num_channel), RB_time(_RB_time), RB_size(_RB_size), RB_bandwidth(_RB_bandwidth) {}

vector<Allocation> Scheduler::GetAllocation(vector<Request>& requests, unordered_map<int, double>& utility_rate) {
    return vector<Allocation>(requests.size());
}