#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

#include "core.hpp"

TEST_CASE("exo 4", "[add]"){
    REQUIRE(identity<int>(20) == 20);
    REQUIRE(identity<int>(30) == 30);
}

TEST_CASE( "Test ...", "[template]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

