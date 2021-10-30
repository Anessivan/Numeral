#include "Methods.h"

point PointEulerMethod(const double x, const double y, double step) // one step for Euler Method
{
    double V = y + step * func(x, y);
    point res(x + step, V);
    return res;
}

point PointRungeKutta2_1(const double x, const double y, double step) // one step for RungeKutta2_1
{
    double V = y + step / 2 * (func(x, y) + func(x + step, y + step * func(x, y)));
    point res(x + step, V);
    return res;
}

point PointRungeKutta2_2(const double x, const double y, double step)// one step for RungeKutta2_2
{
    double V = y + step * func(x + step / 2, y + step / 2 * func(x, y));
    point res(x + step, V);
    return res;
}

std::vector<point> EulerMethod(const double x_start, const double U_start, double step, double stop)
{
	std::vector<point> points;
	double x = x_start;
	double U = U_start;
	point currPoint(x_start, U_start);
	points.push_back(currPoint);
    int i = 1;
	for (x; x <= stop; x += step)
	{
		currPoint = PointEulerMethod(x, points[i - 1].U, step);
		points.push_back(currPoint);
        i++;
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
    int i = 1;
	for (x; x <= stop; x += step)
	{
		currPoint = PointRungeKutta2_1(x, points[i - 1].U, step);
		points.push_back(currPoint);
        i++;
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
	int i = 1;
	for (x; x <= stop; x += step)
	{
		currPoint = PointRungeKutta2_2(x, points[i - 1].U, step);
		points.push_back(currPoint);
        i++;
	}
	return points;
}

double func(const double x, const double V)
{
	return 0.0;
}
