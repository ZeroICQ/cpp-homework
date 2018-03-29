#include <cmath>
#include <vector>
#include <algorithm>
#include "figures.h"

//Figure
//const double Figure::EPS = 0.00001;

//Point
double Point::distance(const Point &other) const {
    return sqrt(
            pow(x() - other.x(), 2)
            + pow(y() - other.y(), 2)
    );
}

bool Point::isInBox(const Point &corner1, const Point &corner2) const {
    double left = fmin(corner1.x(), corner2.x()) - EPS;
    double top = fmax(corner1.y(), corner2.y()) + EPS;

    double right = fmax(corner1.x(), corner2.x()) + EPS;
    double bot = fmin(corner1.y(), corner2.y()) - EPS;

    return left < x() && x() < right && bot < y() && y() < top;
}

double Point::length() const {
    return 0;
}

bool Point::operator==(const Point &rhs) const {
    return fabs(this->x() - rhs.x()) < EPS && fabs(this->y() - rhs.y()) < EPS;
}

//Segment
double Segment::length() const {
    return start_.distance(end_);
}

std::vector<Point> Segment::intersect(const Segment &other) const {
    //http://algolist.ru/maths/geom/intersect/lineline2d.php
    double x1, y1, x2, y2, x3, y3, x4, y4, d;
    std::vector<Point> result;

    x1 = start().x();       y1 = start().y();
    x2 = end().x();         y2 = end().y();
    x3 = other.start().x(); y3 = other.start().y();
    x4 = other.end().x();   y4 = other.end().y();

    d = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);

    double uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / d;
    double uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / d;

    if (0 <= uA  && uA <= 1 && 0 <= uB && uB <= 1) {
        double intersectX = x1 + uA * (x2 - x1);
        double intersectY = y1 + uA * (y2 - y1);
        result.emplace_back(intersectX, intersectY);
    }

    return result;
}

std::vector<Point> Segment::intersect(const Circle &other) const {
    //http://e-maxx.ru/algo/circle_line_intersection
    std::vector<Point> interPoints;
    Point startF(start().x() - other.center().x(), start().y() - other.center().y());
    Point endF(end().x() - other.center().x(), end().y() - other.center().y());

    double A = startF.y() - endF.y();
    double B = endF.x() - startF.x();
    double C = startF.x() * endF.y() - endF.x() * startF.y();

    double x0 = -(A * C) / (A * A + B * B);
    double y0 = -(B * C) / (A * A + B * B);

    double  r = other.radius();

    Point intersectionPoint(x0, y0);

    if (fabs( C * C - r * r * (A * A + B * B)) < EPS) {
        interPoints.emplace_back(x0 + other.center().x(),
                            y0 + other.center().y());

    } else if (C * C < r * r * (A * A + B * B) + EPS) {
        double d = r * r - C * C / (A * A + B * B);
        double mult = sqrt(d / (A * A + B * B));

        double ax = x0 + B * mult + other.center().x();
        double bx = x0 - B * mult + other.center().x();
        double ay = y0 - A * mult + other.center().y();
        double by = y0 + A * mult + other.center().y();

        interPoints.emplace_back(ax, ay);
        interPoints.emplace_back(bx, by);
    }

    std::vector<Point> result;
    //ASK: better way?
    for(const auto &point : interPoints) {
        if (point.isInBox(start(), end())) {
            result.push_back(point);
        }
    }

    return result;
}

std::vector<Point> Segment::intersect(const Polyline &other) const {
    std::vector<Point> result;
    std::vector<Segment> segments(other.segments());

    for (const auto &segment : segments) {
        std::vector<Point> segmentIntrscts = intersect(segment);
        result.insert(result.end(), segmentIntrscts.begin(), segmentIntrscts.end());
    }

    return result;
}

std::vector<Point> Segment::intersect(const Figure &other) const {
    return other.intersect(*this);
}

//Circle
double Circle::length() const {
    return 2 * M_PI * radius_;
}

std::vector<Point> Circle::intersect(const Segment &other) const {
    return other.intersect(*this);
}

std::vector<Point> Circle::intersect(const Circle &other) const {
    //http://www.litunovskiy.com/gamedev/intersection_of_two_circles/
    std::vector<Point> result;
    double distance = center().distance(other.center());

    bool nesting = fabs(other.radius() - radius()) > distance;
    bool isIntersect = distance <= other.radius() + radius();

    if (!nesting && isIntersect) {
        double b =(pow(this->radius_, 2) - pow(other.radius(), 2) + pow(distance, 2)) / (2 * distance);
        double a = distance - b;

        double x0 = other.center().x() + a / distance * (center().x() - other.center().x());
        double y0 = other.center().y() + a / distance * (center().y() - other.center().y());

        if (distance == other.radius() + radius())
            result.emplace_back(x0, y0);
        else {
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

std::vector<Point> Circle::intersect(const Polyline &other) const {
    std::vector<Point> result;
    std::vector<Segment> segments(other.segments());

    for (const auto &segment : segments) {
        std::vector<Point> segmentIntrscts = intersect(segment);
        result.insert(result.end(), segmentIntrscts.begin(), segmentIntrscts.end());
    }

    return result;
}

std::vector<Point> Circle::intersect(const Figure &other) const {
    return other.intersect(*this);
}

//Polyline
double Polyline::length() const {
    double totalLength = 0;
    for (int i = 1; i < (int) points_.size(); i++) {
        totalLength += points_[i - 1].distance(points_[i]);
    }
    return totalLength;
}

std::vector<Segment> Polyline::segments() const {
    std::vector<Point> tmpPoints(points());

    std::vector<Segment> result;

    result.reserve(points().size());

    for (ulong i = 1; i < tmpPoints.size(); i++) {
        result.emplace_back(tmpPoints[i-1], tmpPoints[i]);
    }

    return std::vector<Segment>();
}

std::vector<Point> Polyline::intersect(const Segment &other) const {
    return other.intersect(*this);
}

std::vector<Point> Polyline::intersect(const Circle &other) const {
    return other.intersect(*this);
}

std::vector<Point> Polyline::intersect(const Polyline &other) const {
    return other.intersect(*this);
}

std::vector<Point> Polyline::intersect(const Figure &other) const {
    return other.intersect(*this);
}
