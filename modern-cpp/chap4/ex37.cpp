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

#include <iostream>
#include <iomanip>

namespace fs = std::filesystem;
namespace ch = std::chrono;

template<typename Duration>
bool is_older_than(const fs::path& path, const Duration duration){
    auto ftimeduration = fs::last_write_time(path).time_since_epoch();
    auto nowduration = (ch::system_clock::now() - duration).time_since_epoch();
    return static_cast<Duration>(nowduration -ftimeduration).count() > 0 ;
}

template<typename Duration>
void remove_files_older_than(const fs::path& path, const Duration duration){
    try{
        if(!fs::exists(path)) return;
        if(is_older_than(path, duration)){
            fs::remove(path);
        } else if(fs::is_directory(path)) {
            for(auto const& entry : fs::directory_iterator(path)){
                remove_file_olders_than(entry.path(), duration);
            }
        }
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    
}

std::vector<fs::directory_entry> find_files(const fs::path& path, std::string_view regex) {
    std::vector<fs::directory_entry> result;
    std::regex rx{regex.data()};

    std::copy_if(
        fs::recursive_directory_iterator(path),
        fs::recursive_directory_iterator(),
        std::back_inserter(result),
        [&rx](const fs::directory_entry& entry) {
            return fs::is_regular_file(entry.path()) && 
                std::regex_match(entry.path().filename().string(), rx);
        }
    );
    return result;
}



int main(int argc, char const *argv[]){
    using namespace std::chrono_literals;
    remove_files_older_than("../", 1h + 10min);

    auto dir = fs::temp_directory_path();
    auto pattern = R"(wct[0-9a-zA-Z]{3}\.tmp)";
    auto result = find_files(dir, pattern);

    return 0;
}
