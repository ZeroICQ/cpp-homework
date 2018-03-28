#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "figures.h"
#include <vector>

TEST_CASE("Test Point", "[figure][point]") {
    double x = 10, y = 10;

    Point testPoint(x, y);

    SECTION("Get length") {
        REQUIRE(testPoint.length() == 0);
    }

    SECTION("Get x") {
        REQUIRE(testPoint.getX() == x);
    }

    SECTION("Get y") {
        REQUIRE(testPoint.getY() == y);
    }
}

TEST_CASE("Test Segment", "[figure][segment]") {
    double x1 = 10,  y1 = 10;
    double x2 = 100, y2 = 10;

    Segment testSegment(x1, y1, x2, y2);

    SECTION("Get length") {
        REQUIRE(testSegment.length() == 90);
    }
}

TEST_CASE("Test Circle", "[figure][segment]") {
    double x = 10, y = 10, radius = 2;
    Circle testCircle(x, y, radius);

    SECTION("Get length") {
        REQUIRE(testCircle.length() == 12.566370614359172);
    }
}

TEST_CASE("Test Polyline", "[figure][segment]") {
    std::vector<std::pair<double, double>> points{{0, 0}, {0, 5}, {10, 5}};
    Polyline testPolyline(points);

    SECTION("Get length") {
        REQUIRE(testPolyline.length() == 152);
    }
}