#include "Queue.hpp"

#include "Request/Request.hpp"

template <>
Queue<Request>::Queue() = default;

template <>
Request Queue<Request>::get() {
    Request data_to_return = data.front();
    data.pop_front();
    return data_to_return;
}

template <>
void Queue<Request>::add(const Request& element) {
    data.push_back(element);
}