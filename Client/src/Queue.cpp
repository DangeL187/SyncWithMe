#include "Queue.hpp"

#include "Request/Request.hpp"
#include "Response/Response.hpp"

template <>
Queue<Request>::Queue() = default;
template <>
Queue<Response>::Queue() = default;

template <>
void Queue<Request>::add(const Request& element) {
    _data.push_back(element);
}
template <>
void Queue<Response>::add(const Response& element) {
    _data.push_back(element);
}

template <>
bool Queue<Request>::isEmpty() {
    return (_data.empty());
}
template <>
bool Queue<Response>::isEmpty() {
    return (_data.empty());
}

template <>
Request Queue<Request>::get() {
    try {
        Request data_to_return = _data.front();
        _data.pop_front();
        return data_to_return;
    } catch (std::exception& e) {
        throw std::runtime_error(e.what());
    }
}
template <>
Response Queue<Response>::get() {
    try {
        Response data_to_return = _data.front();
        _data.pop_front();
        return data_to_return;
    } catch (std::exception& e) {
        throw std::runtime_error(e.what());
    }
}

