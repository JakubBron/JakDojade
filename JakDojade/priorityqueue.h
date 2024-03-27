#pragma once
#include "Vector.h"
#include "constants.hpp"
#include <utility>

#define QUEUE_IS_EMPTY -40

template<typename T>
class PriorityQueue {
private:
    Vector<T> heap_;

public:
    PriorityQueue() {}

    bool empty() const {
        return heap_.size() <= 0;
    }

    unsigned int size() const {
        return heap_.size();
    }

    const T& top() const {
        if (heap_.size() <= 0) 
        {
            throw QUEUE_IS_EMPTY;
        }
        return heap_[0];
    }

    void push(T&& value) {
        heap_.push_back(std::move(value));

        unsigned int index = heap_.size() - 1;
        while (index > 0) 
        {
            unsigned int parent_index = (index - 1) / 2;
            if (heap_[parent_index] < heap_[index]) 
            {
                std::swap(heap_[parent_index], heap_[index]);
                index = parent_index;
            }
            else 
            {
                break;
            }
        }
    }

    void pop() {
        if (heap_.size() <= 0) 
        {
            throw QUEUE_IS_EMPTY;
        }

        heap_[0] = heap_[heap_.size()-1];
        heap_.resize(heap_.size()-1);

        unsigned int index = 0;
        while (index < heap_.size()) 
        {
            unsigned int left_child_index = 2 * index + 1;
            unsigned int right_child_index = 2 * index + 2;

            unsigned int largest_child_index = index;
            if (left_child_index < heap_.size() && heap_[largest_child_index] < heap_[left_child_index]) 
            {
                largest_child_index = left_child_index;
            }
            if (right_child_index < heap_.size() && heap_[largest_child_index] < heap_[right_child_index]) 
            {
                largest_child_index = right_child_index;
            }

            if (largest_child_index == index) 
            {
                break;
            }

            std::swap(heap_[index], heap_[largest_child_index]);
            index = largest_child_index;
        }
    }
};