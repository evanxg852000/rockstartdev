#include "core.hpp"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

unsigned char hexchar_to_int(char const ch){
    if (ch >= '0' && ch <= '9') 
        return ch - '0';
    if (ch >= 'A' && ch <= 'F') 
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    throw std::invalid_argument("Invalid hex character!");
}

std::vector<unsigned char> hexstr_to_bytes(std::string_view str) {
    std::vector<unsigned char> rst{};
    for(size_t i = 0; i < str.size(); i += 2){
        rst.push_back(
            (hexchar_to_int(str[i]) << 4) | hexchar_to_int(str[i+1])
        );
    }
    return rst;
}


bool validate_license_plate_format(std::string_view str){
    std::regex rx(R"([A-Z]{3}-[A-Z]{2} \d{3,4})");
    return std::regex_match(str.data(), rx);
}


std::vector<std::string> extract_license_plate_numbers(std::string const & str){
    std::regex rx(R"(([A-Z]{3}-[A-Z]{2} \d{3,4})*)");
    std::smatch match;
    std::vector<std::string> rst;
    for(auto i = std::sregex_iterator(std::cbegin(str), std::cend(str), rx); i != std::sregex_iterator(); ++i) {
        if((*i)[1].matched){
            rst.push_back(i->str());
        }
    }
    return  rst;
}

std::optional<url_parts> parse_uri(std::string uri){
    std::regex rx(R"(^(\w+):\/\/([\w.-]+)(:(\d+))?([\w\/\.]+)?(\?([\w=&]*)(#?(\w+))?)?$)");
    auto matches = std::smatch{};
    if(std::regex_match(uri, matches, rx)){
        if(matches[1].matched && matches[2].matched){
            url_parts parts;
            parts.protocol = matches[1].str();
            parts.domain = matches[2].str();
            if(matches[4].matched)
                parts.port = std::stoi(matches[4]);
            if (matches[5].matched)
               parts.path = matches[5];
            if (matches[7].matched)
               parts.query = matches[7];
            if (matches[9].matched)
               parts.fragment = matches[9];
            return parts;
        }
    }
    return std::nullopt;
}

std::string transform_date(std::string_view text){
    auto rx = std::regex{ R"((\d{1,2})(\.|-|/)(\d{1,2})(\.|-|/)(\d{4}))" };
    return std::regex_replace(text.data(), rx, R"($5-$3-$1)");
}
    