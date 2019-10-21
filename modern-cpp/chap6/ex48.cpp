template<typename T>
std::vector<std::pair<T, size_t>> find_most_frequent(const std::vector<T>& range) {
    std::map<T, size_t> counts;
    for(const auto& e: range)
        counts[e]++;
    
    auto maxelem = std::max_element(std::cbegin(counts), std::cend(counts),
    [](const auto& e1, const auto& e2 ) {
        return e1.second < e2.second;
    });

    std::vector<std::pair<T, size_t>> results;
    
    std::copy_if(std::begin(counts), std::end(counts),
        std::back_inserter(results),
        [maxelem](const auto& e){
            return e.second == maxelem->second;
        }
    );
    return results;
}


int main(int argc, char const *argv[]){
    auto range = std::vector<int>{1,1,3,5,8,13,3,5,8,8,5};
    auto result = find_most_frequent(range);
    for (auto const & e : result){
        std::cout << e.first << " : " << e.second << std::endl;
    }

    return 0;
}