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

class Tester {
private:
    int num_channel;
    int num_pattern;
    int num_UE;
    int num_request;
    double RB_time;
    double RB_size;
    double RB_bandwidth;
    unordered_map<string, Pattern> traffic_pattern_table;
    unordered_map<int, double> utility_rate;
    vector<Request> requests;
    vector<string> claimed_usage;
    vector<string> actual_usage;

    int ReadTestcase(string testcase_file);
    vector<Allocation> GetAllocation(string scheduling_algorithm);
    int Analyze(vector<Allocation>& allocations, string scheduling_algorithm, string testcase_file, string result_file);

public:
    Tester();
    int RunTest(string scheduling_algorithm, string testcase_file, string result_file);
};

#endif