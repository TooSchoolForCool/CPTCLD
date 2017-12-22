#ifndef _NORMAL_USER_H
#define _NORMAL_USER_H

#include "userAgent.h"

class normalUser: public userAgent
{
public:
    normalUser();
    ~normalUser();

public:
    Request generateRequest();
    void addAllocation(double alloc);

private:
    double required_size_;
};

#endif