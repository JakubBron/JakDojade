#pragma once

#include <functional>
#include "Vector.h"
#include <utility>

template <typename ValueType>
class UnorderedMap {
private:
    struct Pair {
        Vector<char> first;
        ValueType second;
    };

    Vector<Vector< Pair > > data;
    size_t size;
    size_t capacity;
    const int PRIME = 31;
    const int DEFAULT_CAPACITY = 10'007;
    const double MAX_LOAD_FACTOR = 0.7;

public:
    UnorderedMap() {
        size = 0;
        capacity = DEFAULT_CAPACITY;
        data.resize(capacity);
    }

    ValueType& operator[](const Vector<char>& key) 
    {
        size_t index = hashKey(key);
        for (size_t i = 0; i < data[index].size(); ++i) 
        {
            if (data[index][i].first == key) 
            {
                return data[index][i].second;
            }
        }
        Pair newPair = { key.copy(), ValueType() };
        data[index].push_back(std::move(newPair));
        ++size;
        return data[index][data[index].size() - 1].second;
    }

    size_t getSize() const {
        return size;
    }

private:
    size_t hashKey(const Vector<char>& key) const {
        size_t hash = 2137;
        for (int i = 0; i < key.size(); i++)
        {
            hash ^= key[i];
            hash *= PRIME;
        }
        return hash % capacity;
    }

    double loadFactor() const {
        return static_cast<double>(size) / capacity;
    }

    void resize() {
        capacity *= 2;
        Vector<Vector< Pair > > newData(capacity);
        for (size_t i = 0; i < data.size(); i++) 
        {
            for (size_t j = 0; j < data[i].size(); j++) 
            {
                size_t index = hashKey(data[i][j].first);
                newData[index].push_back( std::move(data[i][j]) );
            }
        }
        std::swap(data, newData);
    }
};