#ifndef _REQUEST_H
#define _REQUEST_H

struct Request {
    double time;
    int id;
    int priority;
    double bandwidth;
    double delay;
    double size;

    Request(double _time, int _id, int _priority, double _bandwidth, double _delay, double _size):
        time(_time), id(_id), priority(_priority), bandwidth(_bandwidth), delay(_delay), size(_size) {} 
};

#endif