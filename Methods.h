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

std::vector<point> EulerMethod(const double x_start, const double y_start, double step, double stop);

std::vector<double> RungeKutta2_1(const double x_start, const double y_start, double step); // RungeKutta second order type 1

std::vector<double> RungeKutta2_2(const double x_start, const double y_start, double step);// RungeKutta second order type 2