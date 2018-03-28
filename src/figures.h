#pragma once
#include <cstdlib>
#include <vector>
#include <cmath>

class Figure {
public:
	virtual double length() = 0;
};

class Segment : public Figure
{
public:
	Segment(double x, double y) : x_(x), y_(y) {};
private:
	double x_, y_;
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

class Polyline : public Figure
{
public:
	Polyline(std::vector<std::pair<double, double>> pairs) : pairs_(pairs) {};
private:
	std::vector<std::pair<double, double>> pairs_;
};
