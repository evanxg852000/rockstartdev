// #define CATCH_CONFIG_MAIN
// #include "../catch.hpp"

// TEST_CASE("exo 4", "[add]"){
//     REQUIRE(identity<int>(20) == 20);
//     REQUIRE(identity<int>(30) == 30);
// }

#include "core.hpp"

int main() {
    std::cout << __cplusplus << std::endl;
    using namespace std::string_literals;
    std::vector<ProcInfo> processes{
        {512, "cmd.exe"s, ProcStatus::running, "SYSTEM"s, 148293, Platforms::p64bit },
        {1044, "chrome.exe"s, ProcStatus::running, "marius.bancila"s, 25180454, Platforms::p32bit},
        {7108, "explorer.exe"s, ProcStatus::running, "marius.bancila"s, 2952943, Platforms::p64bit },
        {10100, "chrome.exe"s, ProcStatus::running, "marius.bancila"s, 227756123, Platforms::p32bit},
        {22456, "skype.exe"s, ProcStatus::suspended, "marius.bancila"s, 16870123, Platforms::p64bit },
    };
    print_processes(processes);
}