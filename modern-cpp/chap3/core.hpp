#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <array>
#include <regex>
#include <optional>


unsigned int Factorial( unsigned int number );

template<class Iter>
std::string bytes_to_hexstr(Iter begin, Iter end, bool const uppercase = false){
    std::ostringstream oss;
    if(uppercase)
        oss.setf(std::ios_base::uppercase);
    
    for(; begin != end; ++begin)
        oss << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(*begin) ;
    
    return oss.str();
}

template<class C>
std::string bytes_to_hexstr(C const &c, bool const uppercase = false){
    return bytes_to_hexstr(std::cbegin(c), std::cend(c), uppercase);
}

unsigned char hexchar_to_int(char const ch);

std::vector<unsigned char> hexstr_to_bytes(std::string_view str);

template<class Elem>
using tstring = std::basic_string<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

template<class Elem>
using tstringstream = std::basic_stringstream<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

template<class Elem>
tstring<Elem> capitalize(tstring<Elem> const & text) {
    tstringstream<Elem> rst;
    bool new_word = true;

    for (auto const ch: text) {
        new_word = new_word || std::isspace(ch) || std::ispunct(ch);
        if(std::isalpha(ch)) {
            if(new_word) {
                rst << static_cast<Elem>(std::toupper(ch));
                new_word = false;
            } else {
                rst <<static_cast<Elem>(std::tolower(ch));
            }
        } else {
            rst << ch;
        }
    }
    return rst.str();
} 

template<class Iter>
std::string join_strings(Iter begin, Iter end, char const * const separtor) {
    std::ostringstream oss;
    std::copy( begin, end-1, 
        std::ostream_iterator<std::string>(oss, separtor));
    oss << * (end-1);
    return oss.str();
}

template<typename C>
std::string join_strings(C const & c, char const * const separator){
    if(c.size() == 0)
        return std::string{};

    return join_strings(std::begin(c), std::end(c), separator);
}

template<typename Elem>
inline std::vector<tstring<Elem>> split(tstring<Elem> text, Elem const delimiter) {
    auto sstr = tstringstream<Elem>{text};
    auto tokens = std::vector<tstring<Elem>>{};
    auto token = tstring<Elem>{};
    while(std::getline(sstr, token, delimiter)){
        if(!token.empty())
            tokens.push_back(token);
    }
    return tokens;
}

template<typename Elem>
inline std::vector<tstring<Elem>> split(tstring<Elem> text, tstring<Elem> const & delimiters){
    auto tokens = std::vector<tstring<Elem>>{};
    size_t pos, prev_pos = 0;
    while((pos = text.find_first_of(delimiters, prev_pos)) != std::string::npos){
        if(pos > prev_pos)
            tokens.push_back(text.substr(prev_pos, pos - prev_pos));
        prev_pos = pos + 1;
    }
    if (prev_pos< text.length())
        tokens.push_back(text.substr(prev_pos, std::string::npos));
    return tokens;
}

bool validate_license_plate_format(std::string_view);

std::vector<std::string> extract_license_plate_numbers(std::string const & str);

struct url_parts{
    std::string protocol;
    std::string domain;
    std::optional<int> port;
    std::optional<std::string> path;
    std::optional<std::string> query;
    std::optional<std::string> fragment;
};

std::optional<url_parts> parse_uri(std::string uri);

std::string transform_date(std::string_view text);
