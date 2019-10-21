#ifndef CORE_H
#define CORE_H

#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <experimental/filesystem>

#include <iostream>
#include <iomanip>

template<typename T>
T identity(T in){
    return in;
}

uint number_fo_digit(const uint x);

void print_pascal_triangle(int const n);

enum class ProcStatus{
    suspended,
    running
};

enum class Platforms{
    p32bit,
    p64bit
};

struct ProcInfo{
    int id;
    std::string name;
    ProcStatus status;
    std::string account;
    size_t memory;
    Platforms platform;
};

std::string to_string(const ProcStatus& status);

std::string to_string(const Platforms platform);

void print_processes(std::vector<ProcInfo> processes);



#endif