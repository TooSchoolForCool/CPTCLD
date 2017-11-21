#ifndef _ALLOCATION_H
#define _ALLOCATION_H

#include <unordered_map>
#include <vector>
#include <climits>

using namespace std;

// The Allocation class stores an allocation result for a request.
// To create an Allocation, declare it and add RB intervals to it.
//
// Example - create an Allocation that contains RB[2-10] on channel 0 and RB[4-15] on channel 2:
//  Allocation allocation;
//  allocation.Add(0, 2, 9);
//  allocation.Add(2, 4, 12);
struct Allocation {
    // Total number of allocated RB
    int total_rb;
    // The index of the first RB in this allocation
    int first_rb;
    // The index of the RB behind the last one in this allocation
    int last_rb;
    unordered_map<int, vector<pair<int, int>>> rb_intervals;

    Allocation(): total_rb(0), first_rb(INT_MAX), last_rb(INT_MIN) {}

    // Add an RB interval of num_rb size starting from start_rb on specified channel.
    // Return true if succeeded, false if failed.
    bool add(int channel, int start_rb, int num_rb) {
        if (channel < 0 || start_rb < 0 || num_rb <= 0) return false;
        if (rb_intervals.count(channel) == 0) rb_intervals[channel] = vector<pair<int, int>>();
        rb_intervals[channel].push_back(make_pair(start_rb, num_rb));
        total_rb += num_rb;
        first_rb = min(first_rb, start_rb);
        last_rb = max(last_rb, start_rb + num_rb);
        return true;
    }
};

#endif