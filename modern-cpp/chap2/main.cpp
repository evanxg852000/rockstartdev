#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

#include "core.hpp"



TEST_CASE( "Test IPv4", "[IPv4]" ) {
    REQUIRE( (IPv4{"127.0.0.1"}).toString() == "127.0.0.1");
    REQUIRE( (IPv4{"123.1.162.100"}).toString() == "123.1.162.100");

    auto v = (IPv4{"127.0.0.0"}).to_range(IPv4{"127.0.0.10"});
    REQUIRE( v.size() == 11);
    for(auto ip : v) {
        INFO("-> " << ip.toString());
    }
}

TEST_CASE("Variadic template", "[min]") {
    CHECK(minimum(5,4,2, 3) == 2);
    CHECK( minimumc(std::greater<>(),5, 4, 2, 3) == 5 );
    std::vector<int> v;
    push_back(v, 1, 2, 3, 4);
    CHECK(v.size() == 4);
}