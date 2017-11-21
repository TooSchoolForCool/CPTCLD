#ifndef _REQUEST_H
#define _REQUEST_H

// The Request struct stores the properties of a request.
//
// Example - creat a request:
//  Request request(time, id , priority, bandwidth, delay, size);
struct Request {
    // Properties of a request
    double time;
    int id;
    int priority;
    double bandwidth;
    double delay;
    double size;

    Request(double _time = 0, int _id = 0, int _priority = 0, double _bandwidth = 0, double _delay = 0, double _size = 0):
        time(_time), id(_id), priority(_priority), bandwidth(_bandwidth), delay(_delay), size(_size) {} 
};

#endif