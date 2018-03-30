#include <vector>
#include "catch.hpp"
#include "figures.h"

TEST_CASE("Test Point", "[figure][point]") {
    Point testPoint(10, 10);

    SECTION("Get length") {
        REQUIRE(testPoint.length() == Approx(0));
    }

    SECTION("Get x") {
        REQUIRE(testPoint.x() == 10);
    }

    SECTION("Get y") {
        REQUIRE(testPoint.y() == 10);
    }
}

TEST_CASE("Test Segment", "[figure][segment]") {
    Segment testSegment(10, 10, 100, 10);

    SECTION("Get length") {
        REQUIRE(testSegment.length() == Approx(90));
    }
}

TEST_CASE("Test Circle", "[figure][segment]") {
    Circle testCircle(10, 10, 2);

    SECTION("Get length") {
        REQUIRE(testCircle.length() == Approx(12.566370614359172));
    }
}

TEST_CASE("Test Polyline", "[figure][segment]") {
    std::vector<Point> points;

    points.emplace_back(0, 0);
    points.emplace_back(0, 5);
    points.emplace_back(10, 5);

    Polyline testPolyline(points);

    SECTION("Get length") {
        REQUIRE(testPolyline.length() == Approx(15));
    }
}

TEST_CASE("Intersect Segments") {
    SECTION("Intersect with perpendicular segment") {
        Segment testSegment(10, 10, 100, 10);
        Segment otherSegment(20, 100, 20, 0);

        auto intrsct = testSegment.intersect(otherSegment);
        auto intrsctR = otherSegment.intersect(testSegment);

        REQUIRE(intrsct.size() == 1);
        REQUIRE(intrsct[0].x() == Approx(20));
        REQUIRE(intrsct[0].y() == Approx(10));

        REQUIRE(intrsctR.size() == 1);
        REQUIRE(intrsctR[0].x() == Approx(20));
        REQUIRE(intrsctR[0].y() == Approx(10));
    }

    SECTION("Intersecting segment") {
        Segment testSegment(0, 5, 5, 0);
        Segment otherSegment(0, 3, 8, 3);

        auto intrsct = testSegment.intersect(otherSegment);

        REQUIRE(intrsct.size() == 1);
        REQUIRE(intrsct[0].x() == Approx(2));
        REQUIRE(intrsct[0].y() == Approx(3));
    }

    SECTION("Not intersecting segments") {
        Segment testSegment(0, 5, 5, 0);
        Segment otherSegment(100, 22, 100, 33);

        auto intrsct = testSegment.intersect(otherSegment);
        auto intrsctR = otherSegment.intersect(testSegment);

        REQUIRE(intrsct.empty());
        REQUIRE(intrsctR.empty());
    }

    SECTION("Segments with common start point") {
        Segment testSegment(0, 0, 4, 4);
        Segment otherSegment(0, 0, 0, 2);

        auto intrsct = testSegment.intersect(otherSegment);
        auto intrsctR = otherSegment.intersect(testSegment);

        REQUIRE(intrsct.size() == 1);
        REQUIRE(intrsct[0].x() == Approx(0));
        REQUIRE(intrsct[0].y() == Approx(0));

        REQUIRE(intrsctR.size() == 1);
        REQUIRE(intrsctR[0].x() == Approx(0));
        REQUIRE(intrsctR[0].y() == Approx(0));
    }

    SECTION("Equal segments") {
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

        REQUIRE(intrsct.empty());
        REQUIRE(intrsctR.empty());
    }

    SECTION("Segment same line, one common point") {
        Segment testSegment(0, 0, 5, 5);
        Segment otherSegment(5, 5, 10, 10);

        auto intrsct = testSegment.intersect(otherSegment);
        auto intrsctR = otherSegment.intersect(testSegment);

        REQUIRE(intrsct.empty());
        REQUIRE(intrsctR.empty());
    }

    SECTION("Segment same line, intersecting") {
        Segment testSegment(0, 0, 5, 5);
        Segment otherSegment(3, 3, 10, 10);

        auto intrsct = testSegment.intersect(otherSegment);
        auto intrsctR = otherSegment.intersect(testSegment);

        REQUIRE(intrsct.empty());
        REQUIRE(intrsctR.empty());
    }

    SECTION("Very close not intersecting lines") {
        Segment testSegment(0, 0, 4, 4);
        Segment otherSegment(2, 0, 4, 3.7);

        auto intrsct = testSegment.intersect(otherSegment);
        auto intrsctR = otherSegment.intersect(testSegment);

        REQUIRE(intrsct.empty());
        REQUIRE(intrsctR.empty());
    }

    SECTION("Very close not intersecting lines 2") {
        Segment testSegment(0, 0, 4, 4);
        Segment otherSegment(3.8, 4.7, 4.5, 3.4);

        auto intrsct = testSegment.intersect(otherSegment);
        auto intrsctR = otherSegment.intersect(testSegment);

        REQUIRE(intrsct.empty());
        REQUIRE(intrsctR.empty());
    }
}

TEST_CASE("Intersect circle and segment", "[figure][segment][circle]") {
    SECTION("Doesn't intersect") {
        Segment testSegment(10, 4.2, 0, 2.2);
        Circle testCircle(0, 0, 2);

        auto intrsct = testSegment.intersect(testCircle);
        auto intrsctR = testCircle.intersect(testSegment);

        REQUIRE(intrsct.empty());
        REQUIRE(intrsctR.empty());
    }

    SECTION("Close. but doesn't intersect") {
        Segment testSegment(3.49334, 0.90655, 0, 2.2);
        Circle testCircle(0, 0, 2);

        auto intrsct = testSegment.intersect(testCircle);
        auto intrsctR = testCircle.intersect(testSegment);

        REQUIRE(intrsct.empty());
        REQUIRE(intrsctR.empty());
    }

    SECTION("Tangent") {
        Segment testSegment(3, 2, -1.8, 2);
        Circle testCircle(0, 0, 2);


        auto intrsct = testSegment.intersect(testCircle);
        auto intrsctR = testCircle.intersect(testSegment);

        REQUIRE(intrsct.size() == 1);
        REQUIRE(intrsct[0].x() == Approx(0));
        REQUIRE(intrsct[0].y() == Approx(2));

        REQUIRE(intrsctR.size() == 1);
        REQUIRE(intrsctR[0].x() == Approx(0));
        REQUIRE(intrsctR[0].y() == Approx(2));
    }

    SECTION("Segment inside circle") {
        Segment testSegment(-1, 1, 1, -1);
        Circle testCircle(0, 0, 2);


        auto intrsct = testSegment.intersect(testCircle);
        auto intrsctR = testCircle.intersect(testSegment);

        REQUIRE(intrsct.empty());
        REQUIRE(intrsctR.empty());
    }

    SECTION("Intersect") {
        Segment testSegment(-5, 0, 10, 0);
        Circle testCircle(0, 0, 2);

        auto intrsct = testSegment.intersect(testCircle);
        auto intrsctR = testCircle.intersect(testSegment);

        REQUIRE(intrsct.size() == 2);
        REQUIRE(std::find(intrsct.begin(), intrsct.end(), Point(-2, 0)) != intrsct.end());
        REQUIRE(std::find(intrsct.begin(), intrsct.end(), Point(2, 0)) != intrsct.end());

        REQUIRE(intrsctR.size() == 2);
        REQUIRE(std::find(intrsctR.begin(), intrsctR.end(), Point(-2, 0)) != intrsctR.end());
        REQUIRE(std::find(intrsctR.begin(), intrsctR.end(), Point(2, 0)) != intrsctR.end());
    }

    SECTION("Intersect") {
        Segment testSegment(-1, 1, -3, -1);
        Circle testCircle(0, 0, 2);

        auto intrsct = testSegment.intersect(testCircle);
        auto intrsctR = testCircle.intersect(testSegment);

        REQUIRE(intrsct.size() == 1);
        REQUIRE(intrsct[0].x() == Approx(-2));
        REQUIRE(intrsct[0].y() == Approx(0));

        REQUIRE(intrsctR.size() == 1);
        REQUIRE(intrsctR[0].x() == Approx(-2));
        REQUIRE(intrsctR[0].y() == Approx(0));
    }

}

TEST_CASE("Intersect circles", "[figure][circle]") {
    SECTION("Circle inside circle") {
        Circle outerCircle(0, 0, 2.2);
        Circle innerCircle(0, 0, 1.2);

        auto intrsct = innerCircle.intersect(outerCircle);
        auto intrsctR = outerCircle.intersect(innerCircle);

        REQUIRE(intrsct.empty());
        REQUIRE(intrsctR.empty());
    }

    SECTION("Not intersecting") {
        Circle circleA(0, 0, 2.2);
        Circle circleB(10, 10, 1.2);

        auto intrsct = circleB.intersect(circleA);
        auto intrsctR = circleA.intersect(circleB);

        REQUIRE(intrsct.empty());
        REQUIRE(intrsctR.empty());
    }

    SECTION("Tangent") {
        Circle circleA(0, 0, 2);
        Circle circleB(3, 0, 1);

        auto intrsct = circleB.intersect(circleA);
        auto intrsctR = circleA.intersect(circleB);

        REQUIRE(intrsct.size() == 1);
        REQUIRE(intrsct[0].x() == Approx(2));
        REQUIRE(intrsct[0].y() == Approx(0));

        REQUIRE(intrsctR.size() == 1);
        REQUIRE(intrsctR[0].x() == Approx(2));
        REQUIRE(intrsctR[0].y() == Approx(0));
    }

    SECTION("Intersect") {
        Circle circleA(0, 0, 2);
        Circle circleB(0, 1, 2.2);


        auto intrsct = circleA.intersect(circleB);
        auto intrsctR = circleB.intersect(circleA);

        REQUIRE(intrsct.size() == 2);
        REQUIRE(std::find(intrsct.begin(), intrsct.end(), Point(-1.99839935, 0.0799935)) != intrsct.end());
        REQUIRE(std::find(intrsct.begin(), intrsct.end(), Point(1.9983993594874, 0.0799999999999)) != intrsct.end());

        REQUIRE(intrsctR.size() == 2);
        REQUIRE(std::find(intrsctR.begin(), intrsctR.end(), Point(-1.99839935, 0.0799935)) != intrsctR.end());
        REQUIRE(std::find(intrsctR.begin(), intrsctR.end(), Point(1.99839935, 0.079999999)) != intrsctR.end());
    }

}

TEST_CASE("Intersect polyline and segment", "[figure][polyline][segment") {
    SECTION("Intersect") {
        Segment testSegment(0, 2, 7, 2);
        std::vector<Point> polyPoints;

        polyPoints.emplace_back(1, 3);
        polyPoints.emplace_back(4, 3);
        polyPoints.emplace_back(4, 1);
        polyPoints.emplace_back(6, 1);
        polyPoints.emplace_back(6, 3);

        Polyline testPoly(polyPoints);

        auto intrsct = testSegment.intersect(testPoly);
        auto intrsctR = testPoly.intersect(testSegment);

        REQUIRE(intrsct.size() == 2);
        REQUIRE(std::find(intrsct.begin(), intrsct.end(), Point(4, 2)) != intrsct.end());
        REQUIRE(std::find(intrsct.begin(), intrsct.end(), Point(6, 2)) != intrsct.end());

        REQUIRE(intrsctR.size() == 2);
        REQUIRE(std::find(intrsctR.begin(), intrsctR.end(), Point(4, 2)) != intrsctR.end());
        REQUIRE(std::find(intrsctR.begin(), intrsctR.end(), Point(6, 2)) != intrsctR.end());
    }

    SECTION("No intersect") {
        Segment testSegment(5, 5, 5, 2);
        std::vector<Point> polyPoints;

        polyPoints.emplace_back(1, 3);
        polyPoints.emplace_back(4, 3);
        polyPoints.emplace_back(4, 1);
        polyPoints.emplace_back(6, 1);
        polyPoints.emplace_back(6, 3);

        Polyline testPoly(polyPoints);

        auto intrsct = testSegment.intersect(testPoly);
        auto intrsctR = testPoly.intersect(testSegment);

        REQUIRE(intrsct.empty());
        REQUIRE(intrsctR.empty());
    }
}

TEST_CASE("Intersect circle and polyline", "[figure][polyline][circle]") {
    SECTION("Circle inside polygon") {
        Circle testCircle(0, 0, 2);
        std::vector<Point> polyPoints;
        polyPoints.emplace_back(0, 4);
        polyPoints.emplace_back(7, 1.8);
        polyPoints.emplace_back(5.6, -4.2);
        polyPoints.emplace_back(-4, -4);
        polyPoints.emplace_back(-6, 0);
        polyPoints.emplace_back(0, 4);

        Polyline testPoly(polyPoints);

        auto intrsct = testCircle.intersect(testPoly);
        auto intrsctR = testPoly.intersect(testCircle);

        REQUIRE(intrsct.empty());
        REQUIRE(intrsctR.empty());
    }

    SECTION("Intersects") {
        Circle testCircle(0, 0, 3);
        std::vector<Point> polyPoints;
        polyPoints.emplace_back(-4, 0);
        polyPoints.emplace_back(0, 0);
        polyPoints.emplace_back(0, -1);
        polyPoints.emplace_back(1, 0);
        polyPoints.emplace_back(4, 0);
        polyPoints.emplace_back(4, 4);
        polyPoints.emplace_back(0, 4);
        polyPoints.emplace_back(0, 2);

        Polyline testPoly(polyPoints);
//
        auto intrsct = testCircle.intersect(testPoly);
        auto intrsctR = testPoly.intersect(testCircle);

        REQUIRE(intrsct.size() == 3);
        REQUIRE(std::find(intrsct.begin(), intrsct.end(), Point(-3, 0)) != intrsct.end());
        REQUIRE(std::find(intrsct.begin(), intrsct.end(), Point(3, 0)) != intrsct.end());
        REQUIRE(std::find(intrsct.begin(), intrsct.end(), Point(0, 3)) != intrsct.end());

        REQUIRE(intrsctR.size() == 3);
        REQUIRE(std::find(intrsctR.begin(), intrsctR.end(), Point(-3, 0)) != intrsctR.end());
        REQUIRE(std::find(intrsctR.begin(), intrsctR.end(), Point(3, 0)) != intrsctR.end());
        REQUIRE(std::find(intrsctR.begin(), intrsctR.end(), Point(0, 3)) != intrsctR.end());
    }
}

