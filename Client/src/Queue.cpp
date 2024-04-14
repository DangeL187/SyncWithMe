#include "Queue.hpp"

#include "Request/Request.hpp"

template <>
Queue<Request>::Queue() = default;
template <>
Queue<std::string>::Queue() = default;

template <>
void Queue<Request>::add(const Request& element) {
    _data.push_back(element);
}
template <>
void Queue<std::string>::add(const std::string& element) {
    _data.push_back(element);
}

template <>
bool Queue<Request>::isEmpty() {
    return (_data.empty());
}
template <>
bool Queue<std::string>::isEmpty() {
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
std::string Queue<std::string>::get() {
    try {
        std::string data_to_return = _data.front();
        _data.pop_front();
        return data_to_return;
    } catch (std::exception& e) {
        throw std::runtime_error(e.what());
    }
}

