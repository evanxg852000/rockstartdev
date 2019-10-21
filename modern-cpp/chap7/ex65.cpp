#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <exception>
#include <fstream>
#include <thread>
#include <map>
#include <random>

#include <iostream>
#include <iomanip>

class Logger{
protected:
    std::mutex mtx;
    Logger(){}

public:
    static Logger& instance(){
        static Logger lg{};
        return lg;
    }

    Logger(Logger const& other) = delete;
    Logger& operator=(Logger const& other) = delete;

    void log(std::string_view message){
        std::lock_guard<std::mutex>lock(mtx);
        std::cout << "LOG: " << message << std::endl;
    }

};


int main(int argc, char const *argv[]){
    std::vector<std::thread> modules;
    for(int id = 1; id <= 5; ++id) {
        modules.emplace_back([id](){
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<> ud(100, 1000);
            Logger::instance().log("module " + std::to_string(id) + " started");
            std::this_thread::sleep_for(std::chrono::milliseconds(ud(mt)));
            Logger::instance().log( "module " + std::to_string(id) + " finished");
        }); 
    }

    for(auto & m : modules) m.join();

    return 0;
}
