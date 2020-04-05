#include <iostream>

#include <array>
#include <queue>
#include <algorithm>

#include "rang/rang.hpp"

using namespace std;

int main(int argc, char const *argv[]){
    // cout << rang::fg::blue << "Plain old text" << endl
    //      << rang::style::bold << "Rang styled text!!" << endl
    //      << rang::style::reset << endl;

    std::array<int, 4> arr = {1, 2, 3, 4};
    try{
        cout << "arr[3]" << arr.at(3);
        cout << "arr[4]" << arr.at(4);
    } catch(const std::out_of_range& ex){
        cout << ex.what();
    }


    return 0;
}
