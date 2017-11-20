#ifndef _PATTERN_H
#define _PATTERN_H

struct Pattern {
    int priority;
    double bandwidth;
    double delay;
    double max_req_size;
    double price_RB;

    Pattern(int _priority, double _bandwidth, double _delay, double _max_req_size, double _price_RB):
        priority(_priority), bandwidth(_bandwidth), delay(_delay), max_req_size(_max_req_size), price_RB(_price_RB) {}
};

#endif