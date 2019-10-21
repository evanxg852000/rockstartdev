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
#include <map>

#include <iostream>
#include <iomanip>

#include <cassert>
#include <cstdlib>
#include <ctime>


template<typename RandomAccessIterator, typename F>
void ptransform(RandomAccessIterator begin, RandomAccessIterator end, F&& f){
    auto size = std::distance(begin, end);
    if(size <= 10'000){
        std::transform(begin, end, begin, std::forward<F>(f));
    } else {
        std::vector<std::thread> threads;
        int thread_count = std::thread::hardware_concurrency();
        auto first = begin;
        auto last = first;
        size = size / thread_count;
        for(int i=0; i< thread_count; i++){
            first = last;
            if(i=thread_count-1) 
                last = end;
            else
                std::advance(last,size);
            
            threads.emplace_back([first, last, &f](){
                std::transform(first, last, first, std::forward<F>(f));
            });
        }
        for(auto& t : threads) t.join();
    }
}

template<typename T, typename F>
std::vector<T> palter(std::vector<T> data, F&& f){
    ptransform(data.begin(), data.end(), std::forward<F>(f));
    return data;
}


int main(int argc, char const *argv[]){
    srand(time(NULL));
    std::vector<int> data(1'000'000);
    std::generate(data.begin(), data.end(), [](){
        return rand()% 100 + 1;
    });
    auto result = palter(data, [](int const e) {return e * e; });
    
    std::copy(result.begin(), result.begin() + 10, std::ostream_iterator<int>(std::cout, " "));
    return 0;
}
