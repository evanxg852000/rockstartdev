#define CATCH_CONFIG_MAIN 
#include "catch2.hpp"

#include "core.hpp"


TEST_CASE( "Additions are computed", "[add]" ) {
    REQUIRE( add(1, 3) == 4 );
    REQUIRE( add(2, 5) == 7 );
    REQUIRE( add(5, -2) == 3 );
}