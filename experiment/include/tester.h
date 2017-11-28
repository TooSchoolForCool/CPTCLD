#ifndef _TESTER_H
#define _TESTER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "allocation.h"
#include "pattern.h"
#include "request.h"
#include "scheduler.h"
#include "scheduler_null.h"

using namespace std;

// The Tester class provides the interface to run scheduling algorithm on testcases and store results in file.
//
// Example - create a Tester and run SchedulerNull on "testcase_0.txt" and store results in "testresult_0.txt":
//  Tester tester;
//  tester.RunTest("null", "testcase_0.txt", "testresult_0.txt");
class Tester {
private:
    // Number of channels, which indicates how many RB can be used at the same time
    int num_channel;
    // Number of traffic patterns
    int num_pattern;
    int num_ue;
    int num_request;
    // Attributes of RB (rb_size = rb_rate * rb_time)
    double rb_time;
    double rb_size;
    double rb_rate;
    // Traffic pattern table maps pattern name to the pattern properties
    unordered_map<string, Pattern> traffic_pattern_table;
    // Utility rate indicates the effectiveness of a UE using RB (e.g., a UE with utility rate of 0.50 can only successfully use half the RB allocated to it)
    unordered_map<int, double> utility;
    vector<Request> requests;
    // The claimed usage is the requested traffic pattern name of a UE.
    // The actual usage is the actual used traffic pattern of a UE.
    // If not the same, it means the UE is cheating.
    vector<string> claimed_usage;
    vector<string> actual_usage;

    // Read testcase from file, including all the above parameters.
    int ReadTestcase(string testcase_file);
    // Get the allocations for requests by calling the specified scheduling algorithm.
    // When a new sheduling algorithm is added, definition of GetAllocation must be updated to include it.
    vector<Allocation> GetAllocation(string scheduling_algorithm);
    // Analyze the allocations.
    int Analyze(vector<Allocation>& allocations, string scheduling_algorithm, string testcase_file, string result_file);

public:
    Tester();

    // Interface of the running test for scheduling algorithm on testcases and store results in file.
    int RunTest(string scheduling_algorithm, string testcase_file, string result_file);
};

#endif