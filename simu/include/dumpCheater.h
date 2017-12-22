#ifndef _DUMP_CHEATER_H
#define _DUMP_CHEATER_H

#include "userAgent.h"
#include <cstdio>

class dumpCheater: public userAgent
{
public:
    dumpCheater();
    ~dumpCheater();

public:
    Request generateRequest();
    void addAllocation(double alloc);

private:
    double required_size_;
    double step_size_;
    double restart_threshold_;
};

#endif