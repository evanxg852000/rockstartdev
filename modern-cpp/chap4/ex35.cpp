#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <filesystem>
#include <exception>
#include <fstream>

#include <iostream>
#include <iomanip>

namespace fs = std::filesystem;

using ull = unsigned long long;

ull get_directory_size(fs::path const& dir, bool const follows_symlinks = false) {
    auto dirWalker = fs::recursive_directory_iterator(dir, 
        follows_symlinks? fs::directory_options::follow_directory_symlink : fs::directory_options::none);

    return std::accumulate(fs::begin(dirWalker), fs::end(dirWalker), 0ull, [](ull const total, fs::directory_entry const& entry){
        return total + (fs::is_regular_file(entry) ? fs::file_size(entry.path()) : 0);
    });
}


int main(int argc, char const *argv[]){
    std::cout << "Size: " << get_directory_size("./") << std::endl;
    return 0;
}
