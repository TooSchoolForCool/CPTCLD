#ifndef _ALLOCATION_H
#define _ALLOCATION_H

#include <unordered_map>

struct Allocation {
    unordered_map<int, vector<pair<int, int>>> RB_intervals;

    Allocation();
    void add(int channel, int start_RB, int num_RB) {
        RB_intervals[channel].push_back(make_pair(start_RB, num_RB));
    }
};

#endif