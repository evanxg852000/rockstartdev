/*
#define CATCH_CONFIG_MAIN
#include "./catch.hpp"

TEST_CASE("exo 4", "[add]"){
    REQUIRE(identity<int>(20) == 20);
    REQUIRE(identity<int>(30) == 30);
}

#include "./core.hpp"
*/

#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <exception>
#include <fstream>

#include <iostream>
#include <iomanip>


namespace fs = std::filesystem;

void remove_empty_lines(fs::path filePath){
    std::ifstream inFile{filePath.native(), std::ios::in};
    if(!inFile.is_open())
        throw std::runtime_error("cannot open input file");

    auto tempPath = fs::path{"./temp.txt"};
    std::ofstream outFile{tempPath.native(), std::ios::out | std::ios::trunc};
    if(!outFile.is_open())
        throw std::runtime_error("cannot create temporary file");

    std::string line;
    while(std::getline(inFile, line)){
        if(line.length() > 0 && line.find_first_not_of(' ') != line.npos){
            outFile << line << '\n';
        }
    }
    inFile.close();
    outFile.close();

    fs::remove(filePath);
    fs::rename(tempPath, filePath);
}


int main(int argc, char const *argv[]){
    remove_empty_lines(fs::path{"./test.txt"});
    return 0;
}
