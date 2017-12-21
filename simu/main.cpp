#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib> 
#include <ctime> 

using namespace std;

#define MAX_FREE_SIZE   30.0
#define MAX_HP_SERVICE  500.0

int main()
{
    double utilization_rate = 0.5;
    double current_balance = 0;
    double actual_usage = 0;

    // q for request, r for retransmission
    char q_or_r;

    // 0 for free service, 1 for high-priority service
    int service_type;

    // requested quantitiy
    double size;

    // record previous request condition
    char prev_pr = 'r';
    double prev_type, prev_size;

    // random generator seed
    srand((unsigned)time(NULL));

    while( ~scanf("%c %d %lf\n", &q_or_r, &service_type, &size) )
    {
        // increase utilization_rate if previous request succeed.
        if(q_or_r == 'q' && prev_pr == 'q')
            utilization_rate = min(1.0, utilization_rate + prev_size / 1000);

        if(service_type == 0)
        {
            size = min(size, MAX_FREE_SIZE);
        }
        else
        {
            size = min(size, MAX_HP_SERVICE);
        }

        if(q_or_r == 'q')
        {
            double rand_seed = rand() / double(RAND_MAX);

            if(rand_seed > utilization_rate)
                size = 0;

            if(service_type == 1)
                current_balance += size;

            actual_usage += size;
        }
        else
        {
            double current_util_rate = (prev_size - size) / prev_size;
            // large panelty for cheating
            // In normal circumstance, current_util_rate is always greater than 0
            if(current_util_rate < 0)
                current_util_rate = 0;

            double rand_seed = rand() / double(RAND_MAX);

            if(rand_seed > utilization_rate)
                size = 0;

            actual_usage += size;

            utilization_rate = max(0.00001, utilization_rate - 0.1 * (1 - current_util_rate));
        }

        // cout << q_or_r << " " << service_type << " " << size << endl;
        printf("%.2lf %.2lf %.5lf\n", actual_usage, current_balance / 100, utilization_rate);

        prev_size = size;
        prev_type = service_type;
        prev_pr = q_or_r;
    }

    cout << "-1 -1 -1" << endl;

    return 0;
}