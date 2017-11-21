#ifndef _ALLOCATION_H
#define _ALLOCATION_H

#include <unordered_map>
#include <vector>

using namespace std;

struct Allocation {
    int total_RB;
    int first_RB;
    int last_RB;
    unordered_map<int, vector<pair<int, int>>> RB_intervals;

    Allocation(): total_RB(0), first_RB(INT_MAX), last_RB(INT_MIN) {}
    bool add(int channel, int start_RB, int num_RB) {
        if (channel < 0 || start_RB < 0 || num_RB <= 0) return false;
        pair<int, int> interval = make_pair(start_RB, num_RB);
        if (RB_intervals.count(channel) == 0) RB_intervals[channel] = vector<pair<int, int>>();
        RB_intervals[channel].push_back(make_pair(start_RB, num_RB));
        total_RB += num_RB;
        first_RB = min(first_RB, start_RB);
        last_RB = max(last_RB, start_RB + num_RB);
        return true;
    }
};

#endif