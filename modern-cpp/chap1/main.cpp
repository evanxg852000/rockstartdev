#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "core.hpp"


TEST_CASE( "Test ...", "[template]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE("exo 1", "[sum_of_nat_div_by35]"){
    REQUIRE(sum_of_nat_div_by35(13) == 0);
    REQUIRE(sum_of_nat_div_by35(32) == 45);
}

TEST_CASE("exo 2", "[gcd, gcd2]"){
    REQUIRE(gcd(6, 4) == 2);
    REQUIRE(gcd2(6, 4) == 2);
    REQUIRE(gcd(21, 6) == 3);
    REQUIRE(gcd2(21, 6) == 3);
}

TEST_CASE("exo 3", "[lcm]"){
    REQUIRE(lcm(6, 4) == 12);
    REQUIRE(lcm(21, 6) == 42);
}

TEST_CASE("exo 4", "[largest_prime]"){
    REQUIRE(largest_prime(20) == 19);
    REQUIRE(largest_prime(30) == 29);
}

TEST_CASE("exo 5", "[get_sexy_primes]"){
    auto r = get_sexy_primes(30);
    REQUIRE(r.size() == 6);
    auto p = r.at(0);
    REQUIRE(p.first == 5);
    REQUIRE(p.second == 11);
}

TEST_CASE("exo 11",  "[to_roman]"){
    REQUIRE(to_roman(43) == "XLIII");
    REQUIRE(to_roman(123) == "CXXIII");
    REQUIRE(to_roman(1201) == "MCCI");
}

TEST_CASE("exo 12",  "[validate_isbn_10]"){
    REQUIRE(validate_isbn_10("013609181") == false);
    REQUIRE(validate_isbn_10("0136091812") == false);
    REQUIRE(validate_isbn_10("0136091814") == true);
}
