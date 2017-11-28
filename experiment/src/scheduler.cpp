#include "scheduler.h"

Scheduler::Scheduler(int _num_channel, double _rb_time, double _rb_size, double _rb_bandwidth):
    num_channel(_num_channel), rb_time(_rb_time), rb_size(_rb_size), rb_bandwidth(_rb_bandwidth) {}

vector<Allocation> Scheduler::GetAllocation(vector<Request>& requests, unordered_map<int, double>& utility_rate) {
    return vector<Allocation>(requests.size());
}

Scheduler::~Scheduler() {}