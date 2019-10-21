
template<typename In1, typename In2, typename Out>
void zip(In1 begin1, In1 end1, In2 begin2, In2 end2, Out result){
    auto it1 = begin1;
    auto it2 = begin2;
    while(it1 != end1 && it2 != end2){
        result++ = std::make_pair(*it1++, *it2++);
    }
}

template<typename T, typename U>
std::vector<std::pair<T, U>> zip(std::vector<T> const& range1, std::vector<U>const& range2){
    std::vector<std::pair<T, U>>result{};
    zip(range1.begin(), range1.end(), range2.begin(), range2.end(), std::back_inserter(result));
    return result;
}


int main(int argc, char const *argv[]){
    std::vector<int> v1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> v2{ 1, 1, 3, 5, 8, 13, 21 };
    auto result = zip(v1, v2);
    for (auto const & p : result){
        std::cout << '{' << p.first << ',' << p.second << '}' << std::endl;
    }
    return 0;
}
