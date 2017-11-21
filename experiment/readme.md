# CPTCLD Experiment

## Compile

### Using Makefile
Get into experiment folder, and try following command:

```bash
$ make
```

Once compiling process is done and successful, you will see a prompt as following:

```bash
> launch has been succesfully compiled
```

More `make` commands please read Makefiles.

### Manually compile with g++
```bash
> g++ -std=c++11 -I ./include main.cpp ./src/tester.cpp ./src/scheduler.cpp ./src/[customized scheduler]* -o [target file]
```

e.g.
```bash
> g++ -std=c++11 -I ./include main.cpp ./src/tester.cpp ./src/scheduler.cpp ./src/scheduler_null.cpp -o test.exe
```

## Run

- 0 arg
  ```bash
  > ./launch
  ```

- 1 arg
  ```bash
  > ./launch [scheduling algorithm]
  ```

- 2 args
  ```bash
  > ./launch [scheduling algorithm]  [testcase]
  ```

- 3 args
  ```bash
  > ./launch [scheduling algorithm]  [testcase]  [testresult]
  ```

## Add a new scheduler algorithm
e.g., add a new scheduler algorithm: naive:

1. Add the header file "scheduler_naive.h" to ./include/, containing the declaration of class SchedulerNaive.
    ```c++
    // scheduler_naive.h
    #ifndef _SCHEDULER_NAIVE_H
    #define _SCHEDULER_NAIVE_H

    #include "scheduler.h"

    // The SchedulerNaive class derives from Scheduler.
    // It implements the naive scheduling algorithm that returns naive allocation for every request.
    //
    // Example:
    //  Scheduler* scheduler = new SchedulerNaive();
    //  vector<Allocation> allocations = scheduler->GetAllocation(requests, utility_rate);
    //  delete scheduler;
    class SchedulerNaive: public Scheduler {
    public:
        SchedulerNaive(int _num_channel, double _rb_time, double _rb_size, double _rb_bandwidth);

        // Returns the allocation vector which contains naive allocations for every request in requests.
        vector<Allocation> GetAllocation(vector<Request>& requests, unordered_map<int, double>& utility_rate);
    };

    #endif
    ```

2. Add the source file "scheduler_naive.cpp" to ./src/, containing the definition of class SchedulerNaive.
    ```c++
    // scheduler_naive.cpp
    #include "scheduler_naive.h"

    SchedulerNaive::SchedulerNaive(int _num_channel, double _rb_time, double _rb_size, double _rb_bandwidth):
        Scheduler(_num_channel, _rb_time, _rb_size, _rb_bandwidth) {}

    vector<Allocation> SchedulerNaive::GetAllocation(vector<Request>& requests, unordered_map<int, double>& utility_rate) {
        // Perform the naive scheduling algorithm.
    }
    ```

3. Include "scheduler_naive.h" at the head of ./include/tester.h.
    ```c++
    ...
    #include "scheduler_naive.h"
    ...
    ```


4. Add choice for SchedulerNaive in the Tester::GetAllocation() function.
    ```c++
    vector<Allocation> Tester::GetAllocation(string scheduling_algorithm) {
        Scheduler* scheduler;
        // When a new scheduling algorithm is added, it must be included here.
        //
        // Example - to add a new class SchedulerNaive must add here:
        //  else if (scheduling_algorithm == "naive") scheduler = new SchedulerNaive(num_channel, rb_time, rb_size, rb_bandwidth);
        if (scheduling_algorithm == "null") scheduler = new SchedulerNull(num_channel, rb_time, rb_size, rb_bandwidth);
        else if (scheduling_algorithm == "naive") scheduler = new SchedulerNaive(num_channel, rb_time, rb_size, rb_bandwidth);
        else scheduler = new Scheduler(num_channel, rb_time, rb_size, rb_bandwidth);

        vector<Allocation> allocations = scheduler->GetAllocation(requests, utility_rate);
        delete scheduler;
        return allocations;
    }
    ```

5. Compile with scheduler_naive.cpp

    Manually compile with g++
    ```bash
    > g++ -std=c++11 -I ./include main.cpp ./src/tester.cpp ./src/scheduler.cpp ./src/scheduler_null.cpp ./src/scheduler_naive.cpp -o [target file]
    ```
    Or

    Modify Makefile **(to be continued)**
