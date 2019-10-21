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



template<class T, class Compare = std::less<typename std::vector<T>::value_type>>
class PriorityQueue{
    using value_type = typename std::vector<T>::value_type;
    using size_type = typename std::vector<T>::size_type;
    using reference = typename std::vector<T>::reference;
    using const_reference = typename std::vector<T>::const_reference;

    std::vector<T> data;
    Compare comparer;

public:
    bool empty() const noexcept {
        return data.empty();
    }

    size_type size() const noexcept {
        return data.size();
    }

    void push(const value_type& value){
        data.push_back(value);
        std::push_heap(std::begin(data), std::end(data), comparer);
    }

    void pop(){
        std::pop_heap(std::begin(data), std::end(data), comparer);
        data.pop_back();
    }

    const_reference top() const {
        return data.front();
    }

    void swap(PriorityQueue& other) noexcept{
        swap(data, other.data);
        swap(comparer, data.comparer);
    }

};

template<class T, class Compare>
void swap(PriorityQueue<T, Compare>& lhs, PriorityQueue<T, Compare>& rhs)
    noexcept(noexcept(lhs.swap(rhs))){
        lhs.swap(rhs);
}




int main(int argc, char const *argv[]){
    PriorityQueue<int> q;
    for (int i : {1, 5, 3, 1, 13, 21, 8}) {
        q.push(i); 
    }
    
    assert(!q.empty());
    assert(q.size() == 7);
    while (!q.empty()){
        std::cout << q.top() << ' ';
        q.pop(); 
    }

    return 0;
}

