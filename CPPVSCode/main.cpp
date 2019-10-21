#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <future>

using namespace std;


int main(int argc, char const *argv[]){
    using namespace literals::string_literals;
    auto future_t = async([]{ return "female"s; });

    cout << future_t.valid();
    

    return 0;
}

