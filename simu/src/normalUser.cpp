#include "normalUser.h"
#include <cstdio>
#include <iostream>

using namespace std;

normalUser::normalUser()
{
    this->required_size_ = 100;

    this->status_ = 0;
    this->remained_capacity_ = this->required_size_;
    this->util_rate_ = 0.9;

    srand((unsigned)time(NULL));
}

normalUser::~normalUser()
{
    // nop
}

Request normalUser::generateRequest()
{
    printf("%-10s %d\t%d\t%lf\n", "[Request]", this->status_, 1, this->remained_capacity_);
    return Request(this->status_, 1, this->remained_capacity_);
}

void normalUser::addAllocation(double alloc)
{
    if(alloc == 0)
    {
        this->status_ = 0;
    }
    else
    {
        double rand_seed = rand() / double(RAND_MAX);
        if(rand_seed > this->util_rate_)
            alloc *= this->util_rate_;

        this->remained_capacity_ -= alloc;

        if(this->remained_capacity_ > 0)
            this->status_ = 1;
        else
        {
            this->status_ = 0;
            this->remained_capacity_ = this->required_size_;
        }
    }
}