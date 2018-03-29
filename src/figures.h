#pragma once
#include <cstdlib>
#include <utility>
#include <vector>
#include <cmath>

class Point;
class Segment;
class Circle;
class Polyline;

class Figure {
public:
    virtual double length() const = 0;

    virtual std::vector<Point> intersect(const Figure &other) const = 0;
    virtual std::vector<Point> intersect(const Segment &other) const = 0;
    virtual std::vector<Point> intersect(const Circle &other) const = 0;
    virtual std::vector<Point> intersect(const Polyline &other) const = 0;

protected:
    //ASK: constexpr???
    static constexpr double EPS = 0.00001;
};


class Point {
public:
    Point(double x , double y) :x_(x), y_(y) {};
    //ASK: const Point has no effect in declaration
    double distance(const Point &other) const;
    double length() const;
    //ask need vertical space?
    double x() const { return x_; }
    double y() const { return y_; }

private:
    double x_, y_;
};


class Segment : public Figure
{
public:
    Segment(double x1, double y1, double x2, double y2)
         : start_(x1, y1), end_(x2, y2) {};

    Segment(Point start, Point end) : start_(start), end_(end) {};

    double length() const override;

    std::vector<Point> intersect(const Figure &other) const override;
    std::vector<Point> intersect(const Segment &other) const override;
    std::vector<Point> intersect(const Circle &other) const override;
    std::vector<Point> intersect(const Polyline &other) const override;

    //ASK: Point getStart() { return start_; };<-------------????(semicolon)
    Point start() const { return start_; }
    Point end() const { return end_; }
private:
    Point start_, end_;
};


class Circle : public Figure
{
public:
    Circle(double x, double y, double radius)
        : center_(x, y),
          radius_(radius > 0 ? radius : 0) {};

    std::vector<Point> intersect(const Figure &other) const override;
    std::vector<Point> intersect(const Segment &other) const override;
    std::vector<Point> intersect(const Circle &other) const override;
    std::vector<Point> intersect(const Polyline &other) const override;

    double length() const override;
    double radius() const { return radius_; }

    Point center() const { return center_; }

private:
    Point center_;
    double radius_;
};

////TODO: read about std:move and rvalue, lvalue
class Polyline : public Figure
{
public:
    //ASK: std::move()??
    explicit Polyline(std::vector<Point> points) : points_(std::move(points)) {};

    std::vector<Point> intersect(const Figure &other) const override;
    std::vector<Point> intersect(const Segment &other) const override;
    std::vector<Point> intersect(const Circle &other) const override;
    std::vector<Point> intersect(const Polyline &other) const override;

    double length() const override;
    std::vector<Point> points() const { return points_; }
    std::vector<Segment> segments() const;
private:
    std::vector<Point> points_;
};
