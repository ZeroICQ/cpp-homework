#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "figures.h"

double getLength(double x, double y, double radius) {
    Circle myCircle(x, y, radius);
    return myCircle.length();
}

TEST_CASE( "length", "[length]" ) {
    REQUIRE( getLength(0, 0, 1)  == getLength(0, 0, 1) );
}