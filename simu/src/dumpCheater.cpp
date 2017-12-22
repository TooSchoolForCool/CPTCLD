#include "dumpCheater.h"

dumpCheater::dumpCheater()
{
    this->required_size_ = 500;
    this->step_size_ = 50;
    this->restart_threshold_ = this->required_size_ * 0.3;

    this->status_ = 0;
    this->remained_capacity_ = this->required_size_;
    this->util_rate_ = 0.8;
}

dumpCheater::~dumpCheater()
{
    // nop
}

Request dumpCheater::generateRequest()
{
    printf("%-10s %d\t%d\t%lf\n", "[Request]", this->status_, 1, this->remained_capacity_);
    return Request(this->status_, 1, this->remained_capacity_);
}

void dumpCheater::addAllocation(double alloc)
{
    if(alloc == 0)
    {
        if(this->remained_capacity_ == this->required_size_)
            this->status_ = 0;
        else
            this->status_ = 1;
    }
    else
    {
        if(this->remained_capacity_ > this->restart_threshold_)
        {
            this->remained_capacity_ -= this->step_size_;
            this->status_ = 1;
        }
        else
        {
            this->status_ = 0;
            this->remained_capacity_ = this->required_size_;
        }
    }
}