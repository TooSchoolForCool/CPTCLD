#ifndef _SMART_CHEATER_H
#define _SMART_CHEATER_H

#include "userAgent.h"
#include <cstdio>

class smartCheater: public userAgent
{
public:
    smartCheater();
    ~smartCheater();

public:
    Request generateRequest();
    void addAllocation(double alloc);

private:
    double required_size_;
    double step_size_;
    double restart_threshold_;

    int max_smart_cheating_iter_;
    int smart_cheating_iter_;
    double smart_cheating_size_;
};

#endif
