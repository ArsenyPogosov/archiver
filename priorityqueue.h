#pragma once

template <typename T, typename comp = std::less<T>>
class PriorityQueue {
private:
    std::vector<T> content_;
    void MoveUp(size_t i);
    void MoveDown(size_t i);

public:
    T Top();
    void Pop();
    void Push(const T& to_push);

    size_t Size();
    bool Empty();
};

#include "priorityqueue.tcc"