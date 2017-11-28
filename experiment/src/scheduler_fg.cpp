#include "scheduler_fg.h"

void PrintRequests(vector<Request> &req) {
    for(auto it = req.begin(); it < req.end(); it++) {
        printf("[ALOC]: %.2lf\t%d\t%d\t%.2lf\t%.2lf\t%.2lf\n", it->time, it->id, it->priority, 
            it->bandwidth, it->delay, it->size);
    }
}

SchedulerFairGreedy::SchedulerFairGreedy(int _num_channel, double _rb_time, double _rb_size, double _rb_bandwidth):
    Scheduler(_num_channel, _rb_time, _rb_size, _rb_bandwidth) {
        this->num_channel = _num_channel;
        this->rb_time = _rb_time;
        this->rb_size = _rb_size;
        this->rb_bandwidth = _rb_bandwidth;

        this->max_alloc_size = 500;
        this->max_time_slots = MAX_TIME_SLOTS;
        this->time_shift = 0;
        
        for(int i = 0; i < _num_channel; i++)
            this->block_frame.push_back(vector<bool>(this->max_time_slots, false));
}

vector<Allocation> SchedulerFairGreedy::GetAllocation(vector<Request>& requests, unordered_map<int, double>& utility_rate) {
    vector<Allocation> allocations;
    queue<Request> requests_queue;
    vector<Request> current_requests;

    for(auto it = requests.begin(); it < requests.end(); it++)
        requests_queue.push(Request(it->time, it->id, it->priority, it->bandwidth, it->delay, it->size));

    while( !requests_queue.empty() ) {
        current_requests = this->GetNextRequests(requests_queue);

        this->ReorderRequest(current_requests, utility_rate);

        this->Allocate(current_requests, allocations);
    }

    return allocations;
}

void SchedulerFairGreedy::ReorderRequest(vector<Request> &vec, unordered_map<int, double>& utility_rate) {
    for(auto it = vec.begin(); it < vec.end(); it++) {
        // limit the size the allocation
        it->size = min(this->max_alloc_size, it->size);
    }

    vector<RequestPriority> vec_idx;
    for(int i = 0; i < vec.size(); i++) {
        double priority = vec[i].priority / utility_rate[vec[i].id];

        RequestPriority req_idx(i, priority, vec[i].bandwidth);
        vec_idx.push_back(req_idx);
    }

    // define compare function for std::sort
    struct {
        bool operator()(const RequestPriority &a, const RequestPriority &b) {
            if(a.priority != b.priority)
                return (a.priority < b.priority);
            
            if(a.bandwidth != b.bandwidth)
                return (a.bandwidth > b.bandwidth);

            return true;
        }
    }PriorityLess;

    // sort request index instead of requests themselves
    sort(vec_idx.begin(), vec_idx.end(), PriorityLess);

    vector<Request> ret_vec;
    // reorder requestion based on sorted indices
    for(auto it = vec_idx.begin(); it < vec_idx.end(); it++) {
        ret_vec.push_back(vec[it->index]);
    }
    // assigned ordered requests vector to original vector
    vec = ret_vec;
}

vector<Request> SchedulerFairGreedy::GetNextRequests(queue<Request> &q) {
    vector<Request> next_requests;
    double timestamp = q.front().time;

    while(q.front().time == timestamp)
    {
        next_requests.push_back(q.front());
        q.pop();
    }

    return next_requests;
}

void SchedulerFairGreedy::Allocate(vector<Request> &vec, vector<Allocation> &allocations) {
    for(auto it = vec.begin(); it < vec.end(); it++) {
        int ch_needed = ceil(it->bandwidth / this->rb_bandwidth);
        int rb_needed = ceil(it->size / this->rb_size);

        printf("%.2lf\t%.2lf\t%d\n", it->bandwidth, this->rb_bandwidth, ch_needed);
        
        Allocation new_alloc;
        allocations.push_back(new_alloc);
    }
}