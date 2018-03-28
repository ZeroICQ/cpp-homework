#include <cmath>
#include "figures.h"

//Point
double Point::distance(Point other) {
    return sqrt(
            pow(getX() - other.getX(), 2)
            + pow(getY() - other.getY(), 2)
    );
}

double Point::length() {
    return 0;
}

//Segment
double Segment::length() {
    return start.distance(end);
}

//Circle
double Circle::length()
{
    return 2 * M_PI * radius_;
}

//Polyline
double Polyline::length() {
    double sum = 0;
    for (ulong i = 1; i < points_.size(); i++) {
        sum += points_[i - 1].distance(points_[i]);
    }
    return sum;
}

//ASK: any better option?
Polyline::Polyline(std::vector<std::pair<double, double>> points) {
    points_.reserve(points.size());

    for (auto &point : points) {
        points_.emplace_back(point.first, point.second);
    }
}
