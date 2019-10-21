#include <utility>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>

unsigned int Factorial( unsigned int number );

unsigned long long sum_of_nat_div_by35(int limit);

unsigned int gcd(unsigned int a, unsigned int b);
unsigned int gcd2(unsigned int a, unsigned int b);

int lcm(int const a, int const b);

bool is_prime(int const num);
unsigned int largest_prime(unsigned int const limit);

std::vector<std::pair<int, int>> get_sexy_primes(int const limit);

std::string to_roman(unsigned int value);

bool validate_isbn_10(std::string_view isbn);