#ifndef _PATTERN_H
#define _PATTERN_H

// The Pattern struct stores the properties of a traffic pattern.
//
// Example - create a pattern:
//  Pattern pattern(priority, bandwidth, delay, max_req_size, price_rb);
struct Pattern {
    int priority;
    double bandwidth;
    double delay;
    double max_req_size;
    double price_rb;

    Pattern(int _priority = 0, double _bandwidth = 0, double _delay = 0, double _max_req_size = 0, double _price_rb = 0):
        priority(_priority), bandwidth(_bandwidth), delay(_delay), max_req_size(_max_req_size), price_rb(_price_rb) {}
};

#endif