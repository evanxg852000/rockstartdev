#include "core.hpp"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

unsigned long long sum_of_nat_div_by35(int limit){
    unsigned long long sum = 0;

    for(int i=0; i < limit; i++) {
        if( i%15 == 0)
            sum += i;
    }
    return sum;
}

unsigned int gcd(unsigned int a, unsigned int b){
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

unsigned int gcd2(unsigned int a, unsigned int b){
    while(b != 0) {
        auto temp = a;
        a =  b;
        b = temp % b;
    }
    return a;
}

int lcm(int const a, int const b) {
    int h = gcd(a, b);
    return h? a * (b/h) : 0;
}


bool is_prime(int const num){
    bool r = true;
    for(auto i =2; i <= num / 2; i++){
        if(num % i == 0){
            r =  false;
            break;
        }
    }
    return r;
}

unsigned int largest_prime(unsigned int const limit){
    for( auto i = limit; i > 1; i--){
        if(is_prime(i)) 
            return i;
    }
    return 2;
}

std::vector<std::pair<int, int>> get_sexy_primes(int const limit){
    auto result = std::vector<std::pair<int, int>>{};
    for(auto i = 2; i <= limit; i++) {
        if(is_prime(i) && is_prime(i+6)) {
            result.push_back(std::make_pair(i, i+6));
        }
    }
    return result;
}


std::string to_roman(unsigned int value){
    std::vector<std::pair<int, std::string>> roman{
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };
    
    std::stringstream ss;
    for(auto const &kvp : roman){
        while(value >= kvp.first){
            ss << kvp.second;
            value -= kvp.first; 
        }
    }
    return ss.str();
}


bool validate_isbn_10(std::string_view isbn){
    auto valid = false;
    if( isbn.size() == 10 &&
        std::count_if(std::begin(isbn), std::end(isbn), ::isdigit) == 10){
        
        auto r = 10;
        auto sum = std::accumulate( std::begin(isbn), std::end(isbn), 0,
            [&r](int const total, char const c) {
                return total + r-- * (c - '0');
            });
        valid = !(sum % 11);
    }
    return valid;
}