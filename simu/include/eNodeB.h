#ifndef _E_NODE_B_H
#define _E_NODE_B_H

#include "request.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib> 
#include <ctime> 

#define MAX_FREE_SIZE   30.0
#define MAX_HP_SERVICE  500.0
#define INCREASE_RATIO  1000

class eNodeB
{
public:
    eNodeB();

public:
    double dealRequest(Request request);

private:
    double util_rate_;
    double cur_balance_;
    double actual_usage_;

    int prev_req_type_;
    int prev_service_type_;
    double prev_size_;
};

#endif