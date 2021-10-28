#include "Methods.h"

std::vector<point> EulerMethod(const double x_start, const double U_start, double step, double stop)
{
	std::vector<point> points;
	double x = x_start;
	double U = U_start;
	point currPoint(x_start, U_start);
	points.push_back(currPoint);
	for (x; x <= stop; x += step)
	{
		U = U + U * func(x, U);
		currPoint.x = x;
		currPoint.U = U;
		points.push_back(currPoint);
	}
	return points;
}

std::vector<point> RungeKutta2_1(const double x_start, const double U_start, double step, double stop)
{
	std::vector<point> points;
	double x = x_start;
	double U = U_start;
	point currPoint(x_start, U_start);
	points.push_back(currPoint);
	for (x; x <= stop; x += step)
	{
		U = U + step / 2 * (func(x, U) + func(x + step, U + step * func(x, U)));
		currPoint.x = x;
		currPoint.U = U;
		points.push_back(currPoint);
	}
	return points;
}

std::vector<point> RungeKutta2_2(const double x_start, const double U_start, double step, double stop)
{
	std::vector<point> points;
	double x = x_start;
	double V = U_start;
	point currPoint(x_start, U_start);
	points.push_back(currPoint);
	for (x; x <= stop; x += step)
	{
		V = V + step * func(x + step / 2, V + step / 2 * func(x, V));
		currPoint.x = x;
		currPoint.U = V;
		points.push_back(currPoint);
	}
	return points;
}

double func(const double x, const double V)
{
	return 0.0;
}
