#pragma once


#include <vector>

struct point
{
public:
	double x;
	double U;
	point(const double xs, const double Us)
	{
		x = xs;
		U = Us;
	}
};

double func(const double x, const double V);  //rhs

point PointEulerMethod(const double x_start, const double y_start, double step); // one step for Euler Method

point PointRungeKutta2_1(const double x_start, const double y_start, double step);// one step for RungeKutta2_1

point PointRungeKutta2_2(const double x_start, const double y_start, double step);// one step for RungeKutta2_2

std::vector<point> EulerMethod(const double x_start, const double y_start, double step, double stop);

std::vector<point> RungeKutta2_1(const double x_start, const double y_start, double step, double stop); // RungeKutta second order type 1

std::vector<point> RungeKutta2_2(const double x_start, const double y_start, double step, double stop);// RungeKutta second order type 2
