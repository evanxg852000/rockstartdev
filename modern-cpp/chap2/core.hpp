#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <iostream>

// 15, 16
class IPv4 {
std::array<unsigned char, 4> data;

public:
    constexpr IPv4(): data{{0}}{ };

    IPv4(std::string str) {
        //std::cout<< "evan " << str;
        std::string ss{""};
        int idx = 0;
        for(auto i=0; i< str.size(); i++){
            if( str.at(i) == '.'){
                data[idx] = static_cast<unsigned char>(std::stoi(ss));
                ss = "";
                idx++;
            } else {
                ss += str.at(i);
            }
        }
        data[idx] = static_cast<unsigned char>(std::stoi(ss));
    }

    explicit constexpr IPv4(unsigned long a): data {
        static_cast<u_char>((a >> 24) & 0xFF),
        static_cast<u_char>((a >> 16) & 0xFF),
        static_cast<u_char>((a >> 8) & 0xFF),
        static_cast<u_char>( a & 0xFF),
    }{};

    std::string toString(){
        std::stringstream ss;
        ss << static_cast<int>(data[0]) << "."
           << static_cast<int>(data[1]) << "."
           << static_cast<int>(data[2]) << "."
           << static_cast<int>(data[3]);
        return ss.str();
    }

    constexpr u_long to_ulong() const {
        return (
            static_cast<u_long>(data[0] << 24)
            | static_cast<u_long>(data[1] << 16)
            | static_cast<u_long>(data[2] << 8)
            | static_cast<u_long>(data[3])
        );
    }

    std::vector<IPv4> to_range(IPv4 const end) const {
        std::vector<IPv4> v;
        auto i = this->to_ulong();
        auto e = end.to_ulong();
        if(e <= i) 
            return v;

        while(i <= e){
            v.push_back(IPv4{i});
            i++;
        } 
        return std::move(v);
    }

    virtual ~IPv4(){};

};

// 17
template<class T, size_t R, size_t C>
class Array2D {
    typedef T value_type;
    typedef value_type* iterator;
    typedef value_type const* const_iterator;
    
    std::vector<T> arr;

public:
    Array2D() : arr{R * C} {}
    explicit Array2D(std::initializer_list<T> l) : arr{l} {}
    constexpr T * data() noexcept { return arr.data(); }
    constexpr T const * data() const noexcept { return arr.dats(); }

    constexpr T & at(size_t const r, size_t const c) {
        return arr.at(r * C + c);
    }

    constexpr T const & at(size_t const r, size_t const c) const {
        return arr.at(r * C + c);
    }

    constexpr T & operator() (size_t const r, size_t const c) {
        return arr[r * C + c];
    }

    constexpr T const & operator() (size_t const r, size_t const c) const {
        return arr[r * C + c];
    }

    constexpr bool empty() const noexcept { return R == 0 || C == 0; }

    constexpr size_t size(int const rank) const {
        if (rank == 1) 
            return R;
        else if (rank == 2) 
            return C;
        else 
            throw std::out_of_range("Rank is out of range!");
    }

    void fill (T const & value){
        std::fill(std::begin(arr), std::end(arr), value);
    }

    void swap(Array2D & other) noexcept { arr.swap(other.arr); }

    const_iterator begin() const { return arr.data();}
    const_iterator end() const { return arr.data() + arr.size();}
    iterator begin() { return arr.data(); }
    iterator end() { return arr.data + arr.size(); }

};


// 18
template<typename T>
T minimum(const T a, const T b) { return a < b ? a : b; }

template<typename T1, typename... T>
T1 minimum(T1 a, T ... args){
    return minimum(a , minimum(args...));
}

template<typename Compare, typename T>
T minimumc(Compare comp, T const a, T const b){
    return comp(a, b)? a : b;
}

template<typename Compare, typename T1, typename... T>
T1 minimumc(Compare comp, T1 a, T... args){
    return minimumc(comp, a, minimumc(comp, args...));
}

// 19
template<typename C, typename... Args>
void push_back(C& c, Args&&... args){
    (c.push_back(args), ...);
}

// 20

template<typename C, typename T>
bool contains(C const & c, T const & value) {
    return std::end(c) ! = stf::find(std::begin(c), std::end(c), value);
}

template<typename C, typename... T>
bool contains_any(C const& c, T &&... value){
    return (... || contains(c, value));
}

template<typename C, typename... T>
bool contains_all(C const & c, T &&... value){
    return (... || contains(c, value));
}

template<typename C, typename... T>
bool contains_none(C const& c, T &&... value){
    return ! contains_any(c, std::forward<T>(value)...);
}

