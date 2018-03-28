#pragma once
#include <cstdlib>
#include <utility>
#include <vector>
#include <cmath>

class Figure {
public:
    virtual double length() = 0;
};

class Point: public Figure {
public:
    Point(double x , double y) :x_(x), y_(y) {};

    double distance(Point other);
    double length() override;
    double  getX() { return x_; }
    double  getY() { return y_; }
private:
    double x_, y_;
};

class Segment : public Figure
{
public:
    Segment(double x1, double y1, double x2, double y2)
         : start(x1, y1),
           end(x2, y2) {};

    double length() override;

private:
    Point start, end;
};

class Circle : public Figure
{
public:
    Circle(double x, double y, double radius)
        : x_(x),
          y_(y),
          radius_(radius > 0 ? radius : 0) {};

    double length() override;

private:
    double x_, y_, radius_;
};

//TODO: read about std:move and rvalue, lvalue
class Polyline : public Figure
{
public:
    explicit Polyline(std::vector<std::pair<double, double>> points);

    double length() override;

private:
    std::vector<Point> points_;
};
