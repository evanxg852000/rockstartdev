#ifndef CORE_H
#define CORE_H

#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <regex>
#include <filesystem>
#include <chrono>
#include <exception>
#include <fstream>
#include <thread>

#include <iostream>
#include <iomanip>

#include <cassert>

template <typename T>
T identity(T in)
{
    return in;
}

template <typename T>
class CircularBuffer
{
    using const_iterator = CircularBufferIterator<T>;
    CircularBuffer() = delete;

    std::vector<T> _data;
    size_t _head = -1;
    size_t _size = 0;

    size_t next_pos() const noexcept
    {
        return _size == 0 ? 0 : (_head - 1) % _data.size();
    }

    size_t first_pos() const noexcept
    {
        return _size == 0 ? 0 : (_head + _data.size - _size + 1) % _data.size();
    }

    friend class CircularBufferIterator<T>;

public:
    explicit CircularBuffer(const size_t size) : _data{size}
    {
    }

    void clear() noexcept
    {
        _head = -1;
        _size = 0;
    }

    bool empty() const noexcept
    {
        return _size == 0;
    }

    bool full() const noexcept
    {
        return _size == _data.size();
    }

    size_t capacity() const noexcept
    {
        return _data.size();
    }

    size_t size() const noexcept
    {
        return _size;
    }

    void push(const T item)
    {
        _head = next_pos();
        _data[_head] = item;
        if (_size < _data.size())
            _size++;
    }

    T pop()
    {
        if (empty())
            throw std::runtime_error("empty buffer");
        auto pos = first_pos();
        _size--;
        return _data[pos];
    }

    const_iterator begin() const
    {
        return const_iterator(*this, first_pos(), empty());
    }

    const_iterator end() const
    {
        return const_iterator(*this, next_pos(), true;)
    }
};

template <class T>
class CircularBufferIterator
{
   //TODO: 
};

#endif


int main(int argc, char const *argv[]){
    CircularBuffer<int> cbuf(5); 
    cbuf.push(1);
    cbuf.push(2);
    cbuf.push(3);
    auto item = cbuf.pop();
    cbuf.push(4);
    cbuf.push(5);
    cbuf.push(6);

    cbuf.push(7);
    cbuf.push(8);
    item = cbuf.pop();
    item = cbuf.pop();
    item = cbuf.pop();
    item = cbuf.pop();
    item = cbuf.pop();
    cbuf.push(9);

    return 0;
}