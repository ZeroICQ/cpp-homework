#include <cmath>
#include <vector>
#include <algorithm>
#include "figures.h"

//Figure
//const double Figure::EPS = 0.00001;

//Point
double Point::distance(const Point &other) const
{
    return sqrt(
            pow(x() - other.x(), 2)
            + pow(y() - other.y(), 2));
}

bool Point::is_in_box(const Point &corner1, const Point &corner2) const
{
    double left = fmin(corner1.x(), corner2.x()) - EPS;
    double top = fmax(corner1.y(), corner2.y()) + EPS;

    double right = fmax(corner1.x(), corner2.x()) + EPS;
    double bot = fmin(corner1.y(), corner2.y()) - EPS;

    return left < x() && x() < right && bot < y() && y() < top;
}

double Point::length() const
{
    return 0;
}

bool Point::operator==(const Point &rhs) const
{
    return fabs(this->x() - rhs.x()) < EPS && fabs(this->y() - rhs.y()) < EPS;
}

//Segment
double Segment::length() const
{
    return start_.distance(end_);
}

std::vector<Point> Segment::intersect(const Segment &other) const
{
    //http://algolist.ru/maths/geom/intersect/lineline2d.php
    std::vector<Point> result;

    double x1 = start().x();       double y1 = start().y();
    double x2 = end().x();         double y2 = end().y();
    double x3 = other.start().x(); double y3 = other.start().y();
    double x4 = other.end().x();   double y4 = other.end().y();

    double d = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);

    double u_a = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / d;
    double u_b = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / d;

    if (0 <= u_a  && u_a <= 1 && 0 <= u_b && u_b <= 1) {
        double intersect_x = x1 + u_a * (x2 - x1);
        double intersect_y = y1 + u_a * (y2 - y1);
        result.emplace_back(intersect_x, intersect_y);
    }

    return result;
}

std::vector<Point> Segment::intersect(const Circle &other) const
{
    //http://e-maxx.ru/algo/circle_line_intersection
    std::vector<Point> intersection_points;
    Point start_f(start().x() - other.center().x(), start().y() - other.center().y());
    Point end_f(end().x() - other.center().x(), end().y() - other.center().y());

    double A = start_f.y() - end_f.y();
    double B = end_f.x() - start_f.x();
    double C = start_f.x() * end_f.y() - end_f.x() * start_f.y();

    double x0 = -(A * C) / (A * A + B * B);
    double y0 = -(B * C) / (A * A + B * B);

    double  r = other.radius();

    Point intersection_point(x0, y0);

    if (fabs( C * C - r * r * (A * A + B * B)) < EPS) {
        intersection_points.emplace_back(x0 + other.center().x(),
                            y0 + other.center().y());

    } else if (C * C < r * r * (A * A + B * B) + EPS) {
        double d = r * r - C * C / (A * A + B * B);
        double mult = sqrt(d / (A * A + B * B));

        double ax = x0 + B * mult + other.center().x();
        double bx = x0 - B * mult + other.center().x();

        double ay = y0 - A * mult + other.center().y();
        double by = y0 + A * mult + other.center().y();

        intersection_points.emplace_back(ax, ay);
        intersection_points.emplace_back(bx, by);
    }

    std::vector<Point> result;
    //TODO: fix
    //ASK: better way?
    for(const auto &point : intersection_points) {
        if (point.is_in_box(start(), end())) {
            result.push_back(point);
        }
    }

    return result;
}

std::vector<Point> Segment::intersect(const Polyline &other) const
{
    std::vector<Point> result;
    std::vector<Segment> segments(other.segments());

    for (const auto &segment : segments) {
        std::vector<Point> intersect_points = intersect(segment);
        result.insert(result.end(), intersect_points.begin(), intersect_points.end());
    }

    return result;
}

std::vector<Point> Segment::intersect(const Figure &other) const {

    return other.intersect(*this);
}

//Circle
double Circle::length() const
{
    return 2 * M_PI * radius_;
}

std::vector<Point> Circle::intersect(const Segment &other) const
{
    return other.intersect(*this);
}

std::vector<Point> Circle::intersect(const Circle &other) const
{
    //http://www.litunovskiy.com/gamedev/intersection_of_two_circles/
    std::vector<Point> result;
    double distance = center().distance(other.center());

    bool nesting = fabs(other.radius() - radius()) > distance;
    bool is_intersect = distance <= other.radius() + radius();

    if (!nesting && is_intersect) {
        double b =(pow(this->radius_, 2) - pow(other.radius(), 2) + pow(distance, 2)) / (2 * distance);
        double a = distance - b;

        double x0 = other.center().x() + a / distance * (center().x() - other.center().x());
        double y0 = other.center().y() + a / distance * (center().y() - other.center().y());

        if (distance == other.radius() + radius()) {
            result.emplace_back(x0, y0);
        } else {
            double h = sqrt(pow(other.radius(), 2) - pow(a, 2));
            double x3 = x0 + (center().y() - other.center().y()) * h / distance;
            double y3 = y0 - (center().x() - other.center().x()) * h / distance;
            double x4 = x0 - (center().y() - other.center().y()) * h / distance;
            double y4 = y0 + (center().x() - other.center().x()) * h / distance;
            result.emplace_back(x3, y3);
            result.emplace_back(x4, y4);
        }
    }

    return result;
}

std::vector<Point> Circle::intersect(const Polyline &other) const
{
    std::vector<Point> result;
    std::vector<Segment> segments(other.segments());

    for (const auto &segment : segments) {
        std::vector<Point> intersect_points = intersect(segment);
        result.insert(result.end(), intersect_points.begin(), intersect_points.end());
    }

    return result;
}

std::vector<Point> Circle::intersect(const Figure &other) const
{
    return other.intersect(*this);
}

//Polyline
double Polyline::length() const
{
    double total_length = 0;
    for (int i = 1; i < (int) points_.size(); i++) {
        total_length += points_[i - 1].distance(points_[i]);
    }
    return total_length;
}

std::vector<Segment> Polyline::segments() const
{
    std::vector<Point> segment_points(points());
    std::vector<Segment> result;

    result.reserve(points().size());

    for (ulong i = 1; i < segment_points.size(); i++) {
        result.emplace_back(segment_points[i-1], segment_points[i]);
    }

    return result;
}

std::vector<Point> Polyline::intersect(const Segment &other) const
{
    return other.intersect(*this);
}

std::vector<Point> Polyline::intersect(const Circle &other) const
{
    return other.intersect(*this);
}

std::vector<Point> Polyline::intersect(const Polyline &other) const
{
    std::vector<Point> result;
    for (const auto &segment : segments()) {
        std::vector<Point> intersect_points = segment.intersect(other);
        result.insert(result.end(), intersect_points.begin(), intersect_points.end());
    }
    return result;
}

std::vector<Point> Polyline::intersect(const Figure &other) const
{
    return other.intersect(*this);
}
