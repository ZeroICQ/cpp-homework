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
        REQUIRE(testPoint.x() == x);
    }

    SECTION("Get y") {
        REQUIRE(testPoint.y() == y);
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
    std::vector<Point> points;

    points.emplace_back(0, 0);
    points.emplace_back(0, 5);
    points.emplace_back(10, 5);

    Polyline testPolyline(points);

    SECTION("Get length") {
        REQUIRE(testPolyline.length() == 15);
    }
}

TEST_CASE("Intersect Segments") {
    Segment testSegment(10, 10, 100, 10);
    SECTION("Intersect with perpendicular segment") {
        Segment otherSegment(20, 100, 20, 0);
        auto intrsct = testSegment.intersect(otherSegment);
        auto intrsctR = otherSegment.intersect(testSegment);

        REQUIRE((intrsct[0].x() == intrsctR[0].x() && intrsctR[0].x() == 20));
        REQUIRE((intrsct[0].y() == intrsctR[0].y() && intrsctR[0].y() == 10));
    }

    SECTION("Intersect with nonperpendicular segment") {
        Segment testSegment(0, 5, 5, 0);
        Segment otherSegment(0, 3, 8, 3);
        auto intersection = testSegment.intersect(otherSegment);
        REQUIRE(intersection[0].x() == 2);
        REQUIRE(intersection[0].y() == 3);
    }

    SECTION("Segment no intersecton") {
        Segment testSegment(0, 5, 5, 0);
        Segment otherSegment(100, 22, 100, 33);
        auto intrsct = testSegment.intersect(otherSegment);
        auto intrsctR = otherSegment.intersect(testSegment);
        REQUIRE(intrsct.size() == 0);
        REQUIRE(intrsctR.size() == 0);
    }

    SECTION("Segment one point") {
        Segment testSegment(0, 0, 4, 4);
        Segment otherSegment(0, 0, 0, 2);

        auto intrsct = testSegment.intersect(otherSegment);
        auto intrsctR = otherSegment.intersect(testSegment);

        REQUIRE((intrsct[0].x() == intrsctR[0].x()  && intrsctR[0].x() == 0));
        REQUIRE((intrsct[0].y() == intrsctR[0].y()  && intrsctR[0].y() == 0));
    }

    SECTION("Segment same ") {
        Segment testSegment(0, 0, 4, 4);
        Segment otherSegment(0, 0, 4, 4);

        auto intrsct = testSegment.intersect(otherSegment);
        auto intrsctR = otherSegment.intersect(testSegment);

        REQUIRE(intrsct.empty());
        REQUIRE(intrsctR.empty());
    }

    SECTION("Segment same line, no intersect") {
        Segment testSegment(0, 0, 5, 5);
        Segment otherSegment(6, 6, 10, 10);

        auto intrsct = testSegment.intersect(otherSegment);
        auto intrsctR = otherSegment.intersect(testSegment);

        REQUIRE(intrsct.size() == 0);
        REQUIRE(intrsctR.size() == 0);
    }

    SECTION("Very close not intersecting lines") {
        Segment testSegment(0, 0, 4, 4);
        Segment otherSegment(2, 0, 4, 1.99999);

        auto intrsct = testSegment.intersect(otherSegment);
        auto intrsctR = otherSegment.intersect(testSegment);

        REQUIRE(intrsct.empty());
        REQUIRE(intrsctR.empty());
    }
}

TEST_CASE("Intersect polyline and segment", "[figure][segment][polyline]") {
    SECTION("Very close not intersecting lines") {
        std::vector<Point> polyPoints;

        //ASK: init vetctor
        //ASK: vert spaces
        polyPoints.emplace_back(6, 4);
        polyPoints.emplace_back(0, 1);
        polyPoints.emplace_back(5, 1);

        Polyline testPolyline(polyPoints);
        Segment testSegment(4, 5, 4, -1);

        auto intrsct = testPolyline.intersect(testSegment);
        auto intrsctR = testSegment.intersect(testPolyline);

        REQUIRE(std::find(intrsct.begin(), intrsct.end(), Point(4, 3)) != intrsct.end());
        REQUIRE(std::find(intrsct.begin(), intrsct.end(), Point(4, 1)) != intrsct.end());

        REQUIRE(std::find(intrsctR.begin(), intrsctR.end(), Point(4, 3)) != intrsctR.end());
        REQUIRE(std::find(intrsctR.begin(), intrsctR.end(), Point(4, 1)) != intrsctR.end());

        REQUIRE(intrsct.size() == 2);
        REQUIRE(intrsctR.size() == 2);
    }
}
