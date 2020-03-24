#include <catch2/catch.hpp>

#include "../src/dynamic_array.hpp"

TEST_CASE("dynamic array", "[dynamic-array]"){
    dynamic_array<int> arr(5);
    arr.at(0) = 1;
    arr[1] = 2;
    REQUIRE(arr.at(1) == 2);
    REQUIRE(arr.size() == 5);

    REQUIRE_THROWS(arr.at(12));
}


