#ifndef _PATTERN_H
#define _PATTERN_H

struct Pattern {
    int priority;
    double bandwidth;
    double delay;
    double max_req_size;
    double price_RB;

    Pattern(int _priority = 0, double _bandwidth = 0, double _delay = 0, double _max_req_size = 0, double _price_RB = 0):
        priority(_priority), bandwidth(_bandwidth), delay(_delay), max_req_size(_max_req_size), price_RB(_price_RB) {}
};

#endif