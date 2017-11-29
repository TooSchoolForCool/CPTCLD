#include "scheduler_fg.h"

void PrintRequests(vector<Request> &req) {
    for(auto it = req.begin(); it < req.end(); it++) {
        printf("[ALOC]: %.2lf\t%d\t%d\t%.2lf\t%.2lf\t%.2lf\n", it->time, it->id, it->priority, 
            it->rate, it->interval, it->size);
    }
}

SchedulerFairGreedy::SchedulerFairGreedy(int _num_channel, double _rb_time, double _rb_size, double _rb_rate):
    Scheduler(_num_channel, _rb_time, _rb_size, _rb_rate) {
        this->num_channel = _num_channel;
        this->rb_time = _rb_time;
        this->rb_size = _rb_size;
        this->rb_rate = _rb_rate;

        this->max_time_slots = 5000;
        this->timestamp = 0;
        this->alloc_threshold = 0.1;
        this->max_intervals = 5;

        rb_available.resize(this->max_time_slots, 0);

        for(int i = 0; i < num_channel; i++)
            block_frame.push_back(vector<bool>(this->max_time_slots, false));
}

vector<Allocation> SchedulerFairGreedy::GetAllocation(vector<Request>& requests, unordered_map<int, double>& utility_rate) {
    vector<Allocation> allocations(requests.size());
    queue<Request> requests_queue;

    for(auto it = requests.begin(); it < requests.end(); it++)
        requests_queue.push(Request(it->time, it->id, it->priority, it->rate, it->interval, it->size));

    int num_of_request = 0;
    while( !requests_queue.empty() ) {
        // get next requests of next timestamp
        vector<Request> current_requests = this->GetNextRequests(requests_queue);

        // reorder all current requests based on their priority
        vector<int> index = this->ReorderRequest(current_requests, utility_rate, num_of_request);

        // update timestamp block_frame, and rb_available
        this->Refresh(current_requests.front().time);

        // run allocation algorithm, and update allocation vector
        this->Allocate(current_requests, allocations, index);
    }

    return allocations;
}

vector<int> SchedulerFairGreedy::ReorderRequest(vector<Request> &vec, unordered_map<int, double>& utility_rate, int &num_of_request) {
    vector<RequestPriority> vec_idx;
    vector<int> index;

    for(int i = 0; i < vec.size(); i++) {
        double priority = vec[i].priority / utility_rate[vec[i].id];

        RequestPriority req_idx(i, priority, vec[i].rate);
        vec_idx.push_back(req_idx);
    }

    // define compare function for std::sort
    struct {
        bool operator()(const RequestPriority &a, const RequestPriority &b) {
            if(a.priority != b.priority)
                return (a.priority < b.priority);
            
            if(a.rate != b.rate)
                return (a.rate > b.rate);

            return true;
        }
    }PriorityLess;

    // sort request index instead of requests themselves
    sort(vec_idx.begin(), vec_idx.end(), PriorityLess);

    vector<Request> ret_vec;
    // reorder requestion based on sorted indices
    for(auto it = vec_idx.begin(); it < vec_idx.end(); it++) {
        ret_vec.push_back(vec[it->index]);
        index.push_back(it->index + num_of_request);
    }
    // assigned ordered requests vector to original vector
    vec = ret_vec;

    // update current total number of request
    num_of_request += vec.size();

    return index;
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

void SchedulerFairGreedy::Allocate(vector<Request> &vec, vector<Allocation> &allocations, vector<int> &index) {
    for(int k = 0; k < vec.size(); k++) {
        Allocation new_alloc;

        int num_blocks = ceil(vec[k].rate * vec[k].interval / this->rb_size);
        num_blocks = min(num_blocks, (int)ceil(this->num_channel * vec[k].interval * this->alloc_threshold));

        int total_blocks = ceil(vec[k].size / this->rb_size);
        total_blocks = min(total_blocks, num_blocks * this->max_intervals);

        int num_intervals = floor(total_blocks / num_blocks);

        // printf("[INFO]: num_b: %d\ttotal_b: %d\tnum_inter: %d\tsize: %lf\n", 
        //     num_blocks, total_blocks, num_intervals, vec[k].size);

        int time_slot_begin = 0;
        while(num_intervals--)
        {
            int blocks_remained = num_blocks;
            int time_slot_end = time_slot_begin + vec[k].interval;

            for(int i = time_slot_begin; i < time_slot_end && blocks_remained != 0; i++)
            {
                for(int j = 0; j < this->num_channel && blocks_remained != 0; j++)
                {
                    if(!block_frame[j][i] || this->CompeteRB(vec[k]))
                    {
                        block_frame[j][i] = true;
                        new_alloc.add(j, i + this->timestamp, 1);
                        blocks_remained--;
                    }
                }
            }            
            // record how many blocks assigned to a specific user
            if(alloc_record.find(vec[k].id) == alloc_record.end())
                alloc_record[vec[k].id] = num_blocks - blocks_remained;
            else
                alloc_record[vec[k].id] += num_blocks - blocks_remained;

            time_slot_begin += vec[k].interval;
        }

        allocations[index[k]] = new_alloc;
        // printf("[ALOC]: allocate user_%d %d blocks, it request %d blocks\n", vec[k].id, new_alloc.total_rb, total_blocks);
    }
}

bool SchedulerFairGreedy::CompeteRB(Request &req) {
    return true;
}

void SchedulerFairGreedy::Refresh(int current_time) {
    int time_gap = current_time - this->timestamp;
    this->timestamp = current_time;

    // shift remained block to the head of block_frame
    int refresh_end = this->max_time_slots - time_gap;
    for(int i = 0; i < refresh_end; i++)
    {
        for(int j = 0; j < this->num_channel; j++)
            block_frame[j][i] = block_frame[j][i + time_gap];
    }

    // "append" more avaible blocks at the end of the block_frame
    for(int i = refresh_end; i < this->max_time_slots; i++)
    {
        for(int j = 0; j < this->num_channel; j++)
            block_frame[j][i] = false;
    }
}