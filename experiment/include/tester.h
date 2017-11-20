#ifndef _TESTER_H
#define _TESTER_H

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "allocation.h"
#include "pattern.h"
#include "request.h"
#include "scheduler.h"

using namespace std;

class Tester {
private:
    int num_channel;
    double RB_time;
    double RB_size;
    double RB_bandwidth;
    double start_time;
    double end_time;
    unordered_map<string, Pattern> traffic_pattern_table;
    unordered_map<int, double> utility_rate;
    vector<Request> requests;

    int ReadTestcase(string testcase_file);
    vector<Allocation> GetAllocation();
    int Analyze(vector<Allocation>, string output_file);

public:
    Tester();
    int RunTest(string testcase_file, string output_file);
};

#endif