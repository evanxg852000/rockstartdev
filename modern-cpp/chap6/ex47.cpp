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
class DoubleBuffer {
   typedef T value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef T* pointer;

   std::vector<T> rdbuff;
   std::vector<T> wrbuff;
   mutable std::mutex mtx;

public:
    explicit DoubleBuffer(size_t const size): rdbuff(size), wrbuff(size){}

    size_t size() const noexcept { return rdbuff.size(); }

    void write(const T* const ptr, const size_t size){
        std::unique_lock<std::mutex> lock(mtx);
        auto length = std::min(size, wrbuff.size());
        std::copy(ptr, ptr + length, std::begin(wrbuff));
        wrbuff.swap(rdbuff);
    }

    template<class Output>
    void read(Output it) const {
        std::unique_lock<std::mutex> lock(mtx);
        std::copy(rdbuff.cbegin(), rdbuff.cend(), it);
    }

    pointer data() const {
        std::unique_lock<std::mutex>lock(mtx);
        return rdbuff.data();
    }

    reference operator[](const size_t pos){
        std::unique_lock<std::mutex>lock(mtx);
        return rdbuff[pos];
    }

    const_reference operator[](const size_t pos) const {
        std::unique_lock<std::mutex>lock(mtx);
        return rdbuff[pos];
    }

    void swap(DoubleBuffer other){
        std::swap(rdbuff, other.rdbuff);
        std::swap(wrbuff, other.wrbuff);
    }

};

#endif


//////// main.cpp

#include "./core.hpp"

template<typename T>
void printBuffer(const DoubleBuffer<T>& buff){
    buff.read(std::ostream_iterator<T>(std::cout, " "));
    std::cout<< std::endl;
}


int main(int argc, char const *argv[]){
    DoubleBuffer<int> buff(10);

    std::thread t([&buff](){
        for (int i = 1; i < 1000; i += 10) {
            int data[] = { i, i + 1, i + 2, i + 3, i + 4, i + 5, i + 6,i + 7,i + 8,i + 9 };
            buff.write(data, 10);
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(100ms);
        }
    });

    auto start = std::chrono::system_clock::now();
    do {
        printBuffer(buff);
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(150ms);
    } while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start).count() < 12);

    t.join();

    return 0;
}