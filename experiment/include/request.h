#ifndef _REQUEST_H
#define _REQUEST_H

// The Request struct stores the properties of a request.
//
// Example - creat a request:
//  Request request(time, id , priority, rate, interval, size);
struct Request {
    // Properties of a request
    double time;
    int id;
    int priority;
    double rate;
    double interval;
    double size;

    Request(double _time = 0, int _id = 0, int _priority = 0, double _rate = 0, double _interval = 0, double _size = 0):
        time(_time), id(_id), priority(_priority), rate(_rate), interval(_interval), size(_size) {} 
};

#endif