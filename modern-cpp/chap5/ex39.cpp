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

template<typename Time=std::chrono::microseconds,
         typename Clock=std::chrono::high_resolution_clock>
struct PerfTimer {

    template<typename F, typename... Args>
    static Time duration(F&& f, Args... args){
        auto start = Clock::now();
        std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
        auto end = Clock::now();
        return std::chrono::duration_cast<Time>(end - start);
    }

};

void f(){
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
}
void g(const int a, const int b){
    using namespace std::chrono_literals;
    auto i = a * b;
    std::this_thread::sleep_for(1s);
}




int main(int argc, char const *argv[]){

    auto t1 = PerfTimer<>::duration(f);
    auto t2 = PerfTimer<>::duration(g, 2,4);

    std::cout << "T1: " << t1.count() << std::endl;
    std::cout << "T2: " << t2.count() << std::endl;
    
    return 0;
}