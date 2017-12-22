#ifndef _REQUEST_H
#define _REQUEST_H

struct Request
{
    // 0 for request, 1 for retransmission
    int req_type_;
    // 0 for free service, 1 for high-priority service
    int service_type_;
    // request size
    double size_;

    Request(int req_type=0, int service_type=0, double size=0): req_type_(req_type), service_type_(service_type), size_(size) {}
};

#endif