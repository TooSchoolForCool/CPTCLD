#include "tester.h"

Tester::Tester() {}

int Tester::RunTest(string scheduling_algorithm, string testcase_file, string result_file) {
    cout << "Test on " << testcase_file << " begins..." << endl;
    int read_status = ReadTestcase(testcase_file);
    if (read_status == -1) {
        cout << "Test failed: ReadTestCase error." << endl;
        return -1;
    }
    vector<Allocation> allocations = GetAllocation(scheduling_algorithm);
    if (allocations.size() < requests.size()) {
        cout << "Test failed: GetAllocation error." << endl;
        return -1;
    }
    int analyze_status = Analyze(allocations, scheduling_algorithm, testcase_file, result_file);
    if (analyze_status == -1) {
        cout << "Test failed: Analyze error." << endl;
        return -1;
    }
    cout << "Test finished. Result in " << result_file << endl;
    return 0;
}

int Tester::ReadTestcase(string testcase_file) {
    // Clear all the complex variables before reading.
    traffic_pattern_table.clear();
    utility.clear();
    requests.clear();
    claimed_usage.clear();
    actual_usage.clear();

    ifstream testcase(testcase_file);
    if (!testcase) {
        cout << "Open file " << testcase_file << " error." << endl;
        return -1;
    }

    // Start reading from testcase file.
    testcase >> num_channel;
    testcase >> rb_time >> rb_size >> rb_rate;

    testcase >> num_pattern;
    string type;
    int priority;
    double rate;
    double interval;
    double max_req_size;
    double price_rb;
    for (int i = 0; i < num_pattern; i++) {
        testcase >> type >> priority >> rate >> interval >> max_req_size >> price_rb;
        traffic_pattern_table[type] = Pattern(priority, rate, interval, max_req_size, price_rb);
    }

    testcase >> num_ue;
    int id;
    double utility_rate;
    for (int i = 0; i < num_ue; i++) {
        testcase >> id >> utility_rate;
        utility[id] = utility_rate;
    }

    testcase >> num_request;
    double time;
    double size;
    string claimed, actual;
    for (int i = 0; i < num_request; i++) {
        testcase >> time >> id >> claimed >> size >> actual;
        size = min(traffic_pattern_table[claimed].max_req_size, size);
        requests.push_back(Request(time, id, traffic_pattern_table[claimed].priority, traffic_pattern_table[claimed].rate, traffic_pattern_table[claimed].interval, size));
        claimed_usage.push_back(claimed);
        actual_usage.push_back(actual);
    }

    return 0;
}

vector<Allocation> Tester::GetAllocation(string scheduling_algorithm) {
    Scheduler* scheduler;
    // When a new scheduling algorithm is added, it must be included here.
    //
    // Example - to add a new class SchedulerNaive must add here:
    //  else if (scheduling_algorithm == "naive") scheduler = new SchedulerNaive(num_channel, rb_time, rb_size, rb_bandwidth);
    if (scheduling_algorithm == "null") scheduler = new SchedulerNull(num_channel, rb_time, rb_size, rb_bandwidth);
    else if (scheduling_algorithm == "fg") scheduler = new SchedulerFairGreedy(num_channel, rb_time, rb_size, rb_bandwidth);
    else scheduler = new Scheduler(num_channel, rb_time, rb_size, rb_bandwidth);

    vector<Allocation> allocations = scheduler->GetAllocation(requests, utility);
    delete scheduler;
    return allocations;
}

int Tester::Analyze(vector<Allocation>& allocations, string scheduling_algorithm, string testcase_file, string result_file) {
    ofstream result(result_file);
    if (!result) {
        cout << "Open file " << result_file << " error." << endl;
        return -1;
    }
    
    result << "Scheduling Algorthm: " << scheduling_algorithm << endl;
    result << "Testcase: " << testcase_file << endl;
    
    // To be continued

    return 0;
}