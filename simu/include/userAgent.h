#ifndef _USER_AGENT_H
#define _USER_AGENT_H

#include "request.h"

class userAgent
{
public:
    userAgent();
    virtual ~userAgent();

public:
    virtual Request generateRequest() = 0;
    virtual void addAllocation(double alloc) = 0;

protected:
    // 0 for request, 1 for retransmission
    int status_;

    double remained_capacity_;

    double util_rate_;
};

#endif