#ifndef _PATTERN_H
#define _PATTERN_H

// The Pattern struct stores the properties of a traffic pattern.
//
// Example - create a pattern:
//  Pattern pattern(priority, rate, interval, max_req_size, price_rb);
struct Pattern {
    int priority;
    double rate;
    double interval;
    double max_req_size;
    double price_rb;

    Pattern(int _priority = 0, double _rate = 0, double _interval = 0, double _max_req_size = 0, double _price_rb = 0):
        priority(_priority), rate(_rate), interval(_interval), max_req_size(_max_req_size), price_rb(_price_rb) {}
};

#endif