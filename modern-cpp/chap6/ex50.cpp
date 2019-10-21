
bool starts_with(std::string_view str, std::string_view prefix){
    return str.find(prefix) == 0;
}

template<typename InputIt>
std::vector<std::string> filter_numbers(InputIt begin, InputIt end, std::string const& countryCode) {
    std::vector<std::string> results{};
    std::copy_if(begin, end, std::back_inserter(results),
        [countryCode](auto const& e){
            return starts_with(e, countryCode) || starts_with(e, "+" + countryCode);
        }
    );
    return results;
}

std::vector<std::string> filter_numbers(std::vector<std::string> const& numbers, std::string const& countryCode) {
    return filter_numbers(numbers.begin(), numbers.end(), countryCode);
}



int main(int argc, char const *argv[]){
    std::vector<std::string> numbers{
         "+40744909080",
         "44 7520 112233",
         "+44 7555 123456",
         "40 7200 123456",
         "7555 123456"
    };
    
    auto result = filter_numbers(numbers, "44");
    for (auto const & number : result){
        std::cout << number << std::endl;
    }

    return 0;
}
