#include "eNodeB.h"

using namespace std;

eNodeB::eNodeB()
{
    util_rate_ = 0.5;
    cur_balance_ = 0.0;
    actual_usage_ = 0.0;

    prev_req_type_ = 1;
    prev_service_type_ = 0;
    prev_size_ = 0.0;

    srand((unsigned)time(NULL));
}

double eNodeB::dealRequest(Request request)
{
    int req_type = request.req_type_;
    int service_type = request.service_type_;
    double size = request.size_;

    // increase util_rate_ if previous request succeed.
    if(req_type == 0 && prev_req_type_ == 0)
        util_rate_ = min(1.0, util_rate_ + prev_size_ / INCREASE_RATIO);

    if(service_type == 0)
    {
        size = min(size, MAX_FREE_SIZE);
    }
    else
    {
        size = min(size, MAX_HP_SERVICE);
    }

    if(req_type == 0)
    {
        double rand_seed = rand() / double(RAND_MAX);

        if(rand_seed > util_rate_)
            size = 0;

        if(service_type == 1)
            cur_balance_ += size;

        actual_usage_ += size;
    }
    else
    {
        double current_util_rate = (prev_size_ - size) / prev_size_;
        // large panelty for cheating
        // In normal circumstance, current_util_rate is always greater than 0
        if(current_util_rate < 0)
            current_util_rate = 0;

        double rand_seed = rand() / double(RAND_MAX);

        if(rand_seed > util_rate_)
            size = 0;

        actual_usage_ += size;

        util_rate_ = max(0.00001, util_rate_ - 0.3 * (1 - current_util_rate));
    }

    printf("%-10s %.2lf\n", "[ALLOC]", size);
    printf("%-10s %.2lf\t%.2lf\t%.5lf\n", "[INFO]", actual_usage_, cur_balance_ / 100, util_rate_);

    if(size != 0)
        prev_size_ = size;
    prev_service_type_ = service_type;
    prev_req_type_ = req_type;

    return size;
}