
bool starts_with(std::string_view str, std::string_view prefix){
    return str.find(prefix) == 0;
}

void normalize_phone_numbers(std::vector<std::string>& numbers, std::string const& countryCode) {
    std::transform(numbers.cbegin(), numbers.cend(), numbers.begin(),
        [countryCode](std::string const& number){
            std::string result;
            if(number.size() > 0){
                if(number[0] == '0')
                    result = "+" + countryCode + number.substr(1);
                else if(starts_with(number, countryCode))
                    result = "+" + number;
                else if( starts_with(number, "+"+countryCode))
                    result = number;
                else
                    result = "+" + countryCode + number;
            }
            result.erase(
                std::remove_if(result.begin(), result.end(),
                    [](char ch) { return std::isspace(ch); }),
                result.end()
            );
            return result;
        }
    );
}




int main(int argc, char const *argv[]){
    std::vector<std::string> numbers{
        "07555 123456",
        "07555123456",
        "+44 7555 123456",
        "44 7555 123456",
        "7555 123456"
    };
    normalize_phone_numbers(numbers, "44");

    for (auto const & number : numbers){
        std::cout << number << std::endl;
    }

    return 0;
}