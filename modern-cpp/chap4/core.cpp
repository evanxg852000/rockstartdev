#include "core.hpp"

uint number_fo_digit(const uint x) {
    return x > 0 ? (int) log10((double) x) + 1 : 1;
}

void print_pascal_triangle(int const n) {
    for(int i=0; i < n; i++){
        auto x = 1;
        std::cout << std::string((n-i-1)*(n/2), ' ' );
        for(int j=0; j<=i; j++){
            auto y = x;
            x = x * (i-j) / (j+1);
            auto max_len = number_fo_digit(x) - 1;
            std::cout<< y << std::string(n-1-max_len-n%2, ' ');
        }
    }
}


std::string to_string(const ProcStatus& status) {
    return status == ProcStatus::suspended? "suspended" : "running";
}

std::string to_string(const Platforms platform) {
    return platform == Platforms::p32bit? "32-bit" : "64-bit";
}

void print_processes(std::vector<ProcInfo> processes) {
    std::sort(processes.begin(), processes.end(), [](ProcInfo const& p1, ProcInfo const& p2){
        return p1.name < p2.name;
    });

    for(auto const& pi: processes){
        std::cout << std::left << std::setw(25) << std::setfill(' ') << pi.name;
        std::cout << std::left << std::setw(8) << std::setfill(' ') << pi.id;
        std::cout << std::left << std::setw(12) << std::setfill(' ') << to_string(pi.status);
        std::cout << std::left << std::setw(15) << std::setfill(' ') << pi.account;
        std::cout << std::right << std::setw(10) << std::setfill(' ') << (int) (pi.memory/1024);
        std::cout << std::left << ' ' << to_string(pi.platform);
        std::cout << std::endl;
    }
}