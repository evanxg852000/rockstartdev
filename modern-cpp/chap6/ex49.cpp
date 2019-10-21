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

std::map<char, double> analyze_text(std::string_view text) {
    std::map<char, double> frequencies;
    for(char ch='a'; ch <= 'z'; ch++)
        frequencies[ch] = 0;

    for(auto ch : text){
        if(std::isalpha(ch))
            frequencies[std::tolower(ch)]++;
    }

    auto total = std::accumulate(std::begin(frequencies), std::end(frequencies),
        0ull,
        [](auto sum, auto const& kvp){
            return sum + static_cast<unsigned long long>(kvp.second);
        }
    );
    
    std::for_each(std::begin(frequencies), std::end(frequencies),
        [total](auto& kvp){
            kvp.second = (kvp.second * 100.0) / total;
        }
    );  
    return frequencies;
}


int main(int argc, char const *argv[]){
    auto result = analyze_text(R"(Lorem ipsum dolor sit amet, consectetur
         adipiscing elit, sed do eiusmod tempor incididunt ut labore et
         dolore magna aliqua.)");
      for (auto const & kvp : result) {
            std::cout << kvp.first << " : "
                << std::fixed
                << std::setw(5) << std::setfill(' ')
                << std::setprecision(2) << kvp.second << '%' <<std::endl;
      }

    return 0;
}
