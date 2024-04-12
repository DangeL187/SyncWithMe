#ifndef CODEWITHME_QUEUE_HPP
#define CODEWITHME_QUEUE_HPP

#include <deque>

template <typename T>
class Queue {
public:
    Queue();
    void add(const T& element);
    T get();
private:
    std::deque<T> data;
};

#endif //CODEWITHME_QUEUE_HPP
