
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


class Logger {
    fs::path logPath;
    std::ofstream logFile;

public:
    Logger(){
        // https://github.com/mariusbancila/stduuid
        // auto name = uuids::to_string(uuids::uuid_random_generator{}());
        auto name = std::string{"01y38148sgdfj"};
        //logPath = fs::temp_directory_path() / (name + ".tmp");
        logPath = fs::path{"./"+name+".temp"};
        logFile.open(logPath.c_str(), std::ios::out | std::ios::trunc);
    }

    ~Logger() noexcept {
        try{
            if(logFile.is_open())
                logFile.close();
            if(!logPath.empty())
                fs::remove(logPath);
        } catch(...) { }
    }

    void persist(const fs::path& path){
        logFile.close();
        fs::rename(logPath, path);
        logPath.clear();
    }

    Logger& operator<<(std::string_view message){
        logFile << message.data() << "\n";
        return *this;
    }

};


int main(int argc, char const *argv[]){
    Logger log;
    try {
        log << "this is a line" << "and this is another one";
        throw std::runtime_error("error");
    } catch (...) {
        log.persist(R"(lastlog.txt)");
    }
    return 0;
}
