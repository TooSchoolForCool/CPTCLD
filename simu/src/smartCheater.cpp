#include "smartCheater.h"

smartCheater::smartCheater()
{
    this->required_size_ = 500;
    this->step_size_ = 50;
    this->restart_threshold_ = this->required_size_ * 0.8;

    this->max_smart_cheating_iter_ = 10;
    this->smart_cheating_iter_ = this->max_smart_cheating_iter_;
    this->smart_cheating_size_ = 50;

    this->status_ = 0;
    this->remained_capacity_ = this->required_size_;
    this->util_rate_ = 0.8;
}

smartCheater::~smartCheater()
{
    // nop
}

Request smartCheater::generateRequest()
{
    if(this->smart_cheating_iter_-- > 0)
    {
        printf("%-10s %d\t%d\t%lf\n", "[Request]", 0, 0, this->smart_cheating_size_);
        return Request(0, 0, 50);
    }
    else
    {
        printf("%-10s %d\t%d\t%lf\n", "[Request]", this->status_, 1, this->remained_capacity_);
        return Request(this->status_, 1, this->remained_capacity_);
    }
}

void smartCheater::addAllocation(double alloc)
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
        if(this->smart_cheating_iter_ >= 0)
            return;

        if(this->remained_capacity_ > this->restart_threshold_)
        {
            this->remained_capacity_ -= this->step_size_;
            this->status_ = 1;
        }
        else
        {
            this->status_ = 0;
            this->remained_capacity_ = this->required_size_;
            this->smart_cheating_iter_ = this->max_smart_cheating_iter_;
        }
    }
}
