#include <vector>
#include "catch.hpp"
#include "figures.h"
#include "misc.h"

TEST_CASE("Test Point", "[figure][point]")
{
    Point point(10, 10);

    SECTION("Get length")
    {
        REQUIRE(point.length() == Approx(0));
    }

    SECTION("Get x")
    {
        REQUIRE(point.x() == 10);
    }

    SECTION("Get y")
    {
        REQUIRE(point.y() == 10);
    }
}

TEST_CASE("Test Segment", "[figure][segment]")
{
    Segment segment(10, 10, 100, 10);

    SECTION("Get length")
    {
        REQUIRE(segment.length() == Approx(90));
    }
}

TEST_CASE("Test Circle", "[figure][segment]")
{
    Circle circle(10, 10, 2);

    SECTION("Get length")
    {
        REQUIRE(circle.length() == Approx(12.566370614359172));
    }
}

TEST_CASE("Test Polyline", "[figure][segment]")
{
    std::vector<Point> points;

    points.emplace_back(0, 0);
    points.emplace_back(0, 5);
    points.emplace_back(10, 5);

    Polyline polylineline(points);

    SECTION("Get length")
    {
        REQUIRE(polylineline.length() == Approx(15));
    }
}

TEST_CASE("Intersect Segments")
{
    SECTION("Intersect with perpendicular segment")
    {
        Segment segment(10, 10, 100, 10);
        Segment other_segment(20, 100, 20, 0);

        auto intersections = segment.intersect(other_segment);
        auto reverse_intersections = other_segment.intersect(segment);

        REQUIRE(intersections.size() == 1);
        REQUIRE(intersections[0].x() == Approx(20));
        REQUIRE(intersections[0].y() == Approx(10));

        REQUIRE(reverse_intersections.size() == 1);
        REQUIRE(reverse_intersections[0].x() == Approx(20));
        REQUIRE(reverse_intersections[0].y() == Approx(10));
    }

    SECTION("Intersecting segment")
    {
        Segment segment(0, 5, 5, 0);
        Segment other_segment(0, 3, 8, 3);

        auto intersections = segment.intersect(other_segment);

        REQUIRE(intersections.size() == 1);
        REQUIRE(intersections[0].x() == Approx(2));
        REQUIRE(intersections[0].y() == Approx(3));
    }

    SECTION("Not intersecting segments")
    {
        Segment segment(0, 5, 5, 0);
        Segment other_segment(100, 22, 100, 33);

        auto intersections = segment.intersect(other_segment);
        auto reverse_intersections = other_segment.intersect(segment);

        REQUIRE(intersections.empty());
        REQUIRE(reverse_intersections.empty());
    }

    SECTION("Segments with common start point")
    {
        Segment segment(0, 0, 4, 4);
        Segment other_segment(0, 0, 0, 2);

        auto intersections = segment.intersect(other_segment);
        auto reverse_intersections = other_segment.intersect(segment);

        REQUIRE(intersections.size() == 1);
        REQUIRE(intersections[0].x() == Approx(0));
        REQUIRE(intersections[0].y() == Approx(0));

        REQUIRE(reverse_intersections.size() == 1);
        REQUIRE(reverse_intersections[0].x() == Approx(0));
        REQUIRE(reverse_intersections[0].y() == Approx(0));
    }

    SECTION("Equal segments")
    {
        Segment segment(0, 0, 4, 4);
        Segment other_segment(0, 0, 4, 4);

        auto intersections = segment.intersect(other_segment);
        auto reverse_intersections = other_segment.intersect(segment);

        REQUIRE(intersections.empty());
        REQUIRE(reverse_intersections.empty());
    }

    SECTION("Segment same line, no intersect")
    {
        Segment segment(0, 0, 5, 5);
        Segment other_segment(6, 6, 10, 10);

        auto intersections = segment.intersect(other_segment);
        auto reverse_intersections = other_segment.intersect(segment);

        REQUIRE(intersections.empty());
        REQUIRE(reverse_intersections.empty());
    }

    SECTION("Segment same line, one common point")
    {
        Segment segment(0, 0, 5, 5);
        Segment other_segment(5, 5, 10, 10);

        auto intersections = segment.intersect(other_segment);
        auto reverse_intersections = other_segment.intersect(segment);

        REQUIRE(intersections.empty());
        REQUIRE(reverse_intersections.empty());
    }

    SECTION("Segment same line, intersecting")
    {
        Segment segment(0, 0, 5, 5);
        Segment other_segment(3, 3, 10, 10);

        auto intersections = segment.intersect(other_segment);
        auto reverse_intersections = other_segment.intersect(segment);

        REQUIRE(intersections.empty());
        REQUIRE(reverse_intersections.empty());
    }

    SECTION("Very close not intersecting lines")
    {
        Segment segment(0, 0, 4, 4);
        Segment other_segment(2, 0, 4, 3.7);

        auto intersections = segment.intersect(other_segment);
        auto reverse_intersections = other_segment.intersect(segment);

        REQUIRE(intersections.empty());
        REQUIRE(reverse_intersections.empty());
    }

    SECTION("Very close not intersecting lines 2")
    {
        Segment segment(0, 0, 4, 4);
        Segment other_segment(3.8, 4.7, 4.5, 3.4);

        auto intersections = segment.intersect(other_segment);
        auto reverse_intersections = other_segment.intersect(segment);

        REQUIRE(intersections.empty());
        REQUIRE(reverse_intersections.empty());
    }
}

TEST_CASE("Intersect circle and segment", "[figure][segment][circle]")
{
    SECTION("Doesn't intersect")
    {
        Segment segment(10, 4.2, 0, 2.2);
        Circle circle(0, 0, 2);

        auto intersections = segment.intersect(circle);
        auto reverse_intersections = circle.intersect(segment);

        REQUIRE(intersections.empty());
        REQUIRE(reverse_intersections.empty());
    }

    SECTION("Close. but doesn't intersect")
    {
        Segment segment(3.49334, 0.90655, 0, 2.2);
        Circle circle(0, 0, 2);

        auto intersections = segment.intersect(circle);
        auto reverse_intersections = circle.intersect(segment);

        REQUIRE(intersections.empty());
        REQUIRE(reverse_intersections.empty());
    }

    SECTION("Tangent")
    {
        Segment segment(3, 2, -1.8, 2);
        Circle circle(0, 0, 2);

        auto intersections = segment.intersect(circle);
        auto reverse_intersections = circle.intersect(segment);

        REQUIRE(intersections.size() == 1);
        REQUIRE(intersections[0].x() == Approx(0));
        REQUIRE(intersections[0].y() == Approx(2));

        REQUIRE(reverse_intersections.size() == 1);
        REQUIRE(reverse_intersections[0].x() == Approx(0));
        REQUIRE(reverse_intersections[0].y() == Approx(2));
    }

    SECTION("Segment inside circle")
    {
        Segment segment(-1, 1, 1, -1);
        Circle circle(0, 0, 2);

        auto intersections = segment.intersect(circle);
        auto reverse_intersections = circle.intersect(segment);

        REQUIRE(intersections.empty());
        REQUIRE(reverse_intersections.empty());
    }

    SECTION("Intersects")
    {
        Segment segment(-5, 0, 10, 0);
        Circle circle(0, 0, 2);

        auto intersections = segment.intersect(circle);
        auto reverse_intersections = circle.intersect(segment);

        REQUIRE(intersections.size() == 2);
        REQUIRE(misc::contains_point(intersections, Point(-2, 0)));
        REQUIRE(misc::contains_point(intersections, Point(2, 0)));

        REQUIRE(reverse_intersections.size() == 2);
        REQUIRE(misc::contains_point(reverse_intersections, Point(-2, 0)));
        REQUIRE(misc::contains_point(reverse_intersections, Point(2, 0)));
    }

    SECTION("Intersect")
    {
        Segment segment(-1, 1, -3, -1);
        Circle circle(0, 0, 2);

        auto intersections = segment.intersect(circle);
        auto reverse_intersections = circle.intersect(segment);

        REQUIRE(intersections.size() == 1);
        REQUIRE(intersections[0].x() == Approx(-2));
        REQUIRE(intersections[0].y() == Approx(0));

        REQUIRE(reverse_intersections.size() == 1);
        REQUIRE(reverse_intersections[0].x() == Approx(-2));
        REQUIRE(reverse_intersections[0].y() == Approx(0));
    }

}

TEST_CASE("Intersect circles", "[figure][circle]")
{
    SECTION("Circle inside circle")
    {
        Circle outer_circle(0, 0, 2.2);
        Circle inner_circle(0, 0, 1.2);

        auto intersections = inner_circle.intersect(outer_circle);
        auto reverse_intersections = outer_circle.intersect(inner_circle);

        REQUIRE(intersections.empty());
        REQUIRE(reverse_intersections.empty());
    }

    SECTION("Not intersecting")
    {
        Circle circle(0, 0, 2.2);
        Circle other_circle(10, 10, 1.2);

        auto intersections = other_circle.intersect(circle);
        auto reverse_intersections = circle.intersect(other_circle);

        REQUIRE(intersections.empty());
        REQUIRE(reverse_intersections.empty());
    }

    SECTION("Tangent")
    {
        Circle circle(0, 0, 2);
        Circle other_circle(3, 0, 1);

        auto intersections = other_circle.intersect(circle);
        auto reverse_intersections = circle.intersect(other_circle);

        REQUIRE(intersections.size() == 1);
        REQUIRE(intersections[0].x() == Approx(2));
        REQUIRE(intersections[0].y() == Approx(0));

        REQUIRE(reverse_intersections.size() == 1);
        REQUIRE(reverse_intersections[0].x() == Approx(2));
        REQUIRE(reverse_intersections[0].y() == Approx(0));
    }

    SECTION("Intersect")
    {
        Circle circle(0, 0, 2);
        Circle other_circle(0, 1, 2.2);

        auto intersections = circle.intersect(other_circle);
        auto reverse_intersections = other_circle.intersect(circle);

        REQUIRE(intersections.size() == 2);
        REQUIRE(misc::contains_point(intersections, Point(-1.99839935, 0.0799935)));
        REQUIRE(misc::contains_point(intersections, Point(1.9983993594874, 0.0799999999999)));

        REQUIRE(reverse_intersections.size() == 2);
        REQUIRE(misc::contains_point(intersections, Point(-1.99839935, 0.0799935)));
        REQUIRE(misc::contains_point(intersections, Point(1.99839935, 0.079999999)));
    }
}

TEST_CASE("Intersect polyline and segment", "[figure][polyline][segment")
{
    SECTION("Intersect")
    {
        std::vector<Point> polyline_points;
        polyline_points.emplace_back(1, 3);
        polyline_points.emplace_back(4, 3);
        polyline_points.emplace_back(4, 1);
        polyline_points.emplace_back(6, 1);
        polyline_points.emplace_back(6, 3);

        Polyline polyline(polyline_points);
        Segment segment(0, 2, 7, 2);

        auto intersections = segment.intersect(polyline);
        auto reverse_intersections = polyline.intersect(segment);

        REQUIRE(intersections.size() == 2);
        REQUIRE(misc::contains_point(intersections, Point(4, 2)));
        REQUIRE(misc::contains_point(intersections, Point(6, 2)));

        REQUIRE(reverse_intersections.size() == 2);
        REQUIRE(misc::contains_point(reverse_intersections, Point(4, 2)));
        REQUIRE(misc::contains_point(reverse_intersections, Point(6, 2)));
    }

    SECTION("No intersect")
    {
        std::vector<Point> polyline_points;
        polyline_points.emplace_back(1, 3);
        polyline_points.emplace_back(4, 3);
        polyline_points.emplace_back(4, 1);
        polyline_points.emplace_back(6, 1);
        polyline_points.emplace_back(6, 3);

        Polyline polyline(polyline_points);
        Segment segment(5, 5, 5, 2);

        auto intersections = segment.intersect(polyline);
        auto reverse_intersections = polyline.intersect(segment);

        REQUIRE(intersections.empty());
        REQUIRE(reverse_intersections.empty());
    }
}

TEST_CASE("Intersect circle and polyline", "[figure][polyline][circle]")
{
    SECTION("Circle inside polyline")
    {
        std::vector<Point> polyline_points;
        polyline_points.emplace_back(0, 4);
        polyline_points.emplace_back(7, 1.8);
        polyline_points.emplace_back(5.6, -4.2);
        polyline_points.emplace_back(-4, -4);
        polyline_points.emplace_back(-6, 0);
        polyline_points.emplace_back(0, 4);

        Polyline polyline(polyline_points);
        Circle circle(0, 0, 2);

        auto intersections = circle.intersect(polyline);
        auto reverse_intersections = polyline.intersect(circle);

        REQUIRE(intersections.empty());
        REQUIRE(reverse_intersections.empty());
    }

    SECTION("Intersects")
    {
        std::vector<Point> polyline_points;
        polyline_points.emplace_back(-4, 0);
        polyline_points.emplace_back(0, 0);
        polyline_points.emplace_back(0, -1);
        polyline_points.emplace_back(1, 0);
        polyline_points.emplace_back(4, 0);
        polyline_points.emplace_back(4, 4);
        polyline_points.emplace_back(0, 4);
        polyline_points.emplace_back(0, 2);

        Polyline polyline(polyline_points);
        Circle circle(0, 0, 3);

        auto intersections = circle.intersect(polyline);
        auto reverse_intersections = polyline.intersect(circle);

        REQUIRE(intersections.size() == 3);
        REQUIRE(misc::contains_point(intersections, Point(-3, 0)));
        REQUIRE(misc::contains_point(intersections, Point(3, 0)));
        REQUIRE(misc::contains_point(intersections, Point(0, 3)));

        REQUIRE(reverse_intersections.size() == 3);
        REQUIRE(misc::contains_point(reverse_intersections, Point(-3, 0)));
        REQUIRE(misc::contains_point(reverse_intersections, Point(3, 0)));
        REQUIRE(misc::contains_point(reverse_intersections, Point(0, 3)));
    }

    SECTION("Polyline inside circle")
    {
        std::vector<Point> polyline_points;
        polyline_points.emplace_back(-9.9, 0);
        polyline_points.emplace_back(-6, -5);
        polyline_points.emplace_back(7.5, 6);
        polyline_points.emplace_back(-4, 9);

        Polyline polyline(polyline_points);
        Circle circle(0, 0, 10);

        auto intersections = circle.intersect(polyline);
        auto reverse_intersections = polyline.intersect(circle);

        REQUIRE(intersections.empty());
        REQUIRE(reverse_intersections.empty());
    }

    SECTION("No intersection")
    {
        std::vector<Point> polyline_points;
        polyline_points.emplace_back(11, 11);
        polyline_points.emplace_back(1000, 12);
        polyline_points.emplace_back(22, 33);
        polyline_points.emplace_back(45, 111);

        Polyline polyline(polyline_points);
        Circle circle(0, 0, 10);

        auto intersections = circle.intersect(polyline);
        auto reverse_intersections = polyline.intersect(circle);

        REQUIRE(intersections.empty());
        REQUIRE(reverse_intersections.empty());
    }
}

TEST_CASE("Intersect polylines", "[figures][polyline]")
{
    SECTION("Parallel")
    {
        std::vector<Point> polyline_points;
        polyline_points.emplace_back(0, 10);
        polyline_points.emplace_back(8, 10);
        polyline_points.emplace_back(8, 0);
        polyline_points.emplace_back(10, -2);

        Polyline polyline(polyline_points);

        std::vector<Point> other_polyline_points;
        other_polyline_points.emplace_back(0, 9);
        other_polyline_points.emplace_back(7, 9);
        other_polyline_points.emplace_back(7, 0);
        other_polyline_points.emplace_back(9, -2);

        Polyline other_polyline(other_polyline_points);

        auto intersections = polyline.intersect(other_polyline);
        auto reverse_intersections = other_polyline.intersect(polyline);

        REQUIRE(intersections.empty());
        REQUIRE(reverse_intersections.empty());
    }

    SECTION("Intersects")
    {
        std::vector<Point> polyline_points;
        polyline_points.emplace_back(0, 10);
        polyline_points.emplace_back(8, 10);
        polyline_points.emplace_back(8, 0);
        polyline_points.emplace_back(10, -2);

        Polyline polyline(polyline_points);

        std::vector<Point> other_polyline_points;
        other_polyline_points.emplace_back(0, 9);
        other_polyline_points.emplace_back(10, 9);
        other_polyline_points.emplace_back(6, 1);


        Polyline other_polyline(other_polyline_points);

        auto intersections = polyline.intersect(other_polyline);
        auto reverse_intersections = other_polyline.intersect(polyline);

        REQUIRE(intersections.size() == 2);
        REQUIRE(misc::contains_point(intersections, Point(8, 9)));
        REQUIRE(misc::contains_point(intersections, Point(8, 5)));

        REQUIRE(reverse_intersections.size() == 2);
        REQUIRE(misc::contains_point(reverse_intersections, Point(8, 9)));
        REQUIRE(misc::contains_point(reverse_intersections, Point(8, 5)));
    }
}
