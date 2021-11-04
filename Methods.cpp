



#include "Methods.h"
#include <cmath>

/*double PointEulerMethod(const double x, const double y, double step) // one step for Euler Method
{
    double V = y + step * func(x, y);
    double res =  V;
    return res;
}

double PointRungeKutta2_1(const double x, const double y, double step) // one step for RungeKutta2_1
{
    double V = y + step / 2 * (func(x, y) + func(x + step, y + step * func(x, y)));
    double res =  V;
    return res;
}

double PointRungeKutta2_2(const double x, const double y, double step)// one step for RungeKutta2_2
{
    double V = y + step * func(x + step / 2, y + step / 2 * func(x, y));
    double res = V;
    return res;
}



std::vector<double> EulerMethod(const double x_start, const double U_start, double step, double stop)
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
}*/

double est(double x, double U, double step)
{
    double currPoint = pointRungeKutta4(x, U, step);
    double halfPoint = pointRungeKutta4(x, U, step / 2);
    halfPoint = pointRungeKutta4(x, halfPoint, step / 2);
    double res = fabs(halfPoint - currPoint) / 15.0;
    return res;
}

double pointRungeKutta4(const double x, const double y, double step)// one step for RungeKutta4
{
    double k1, k2, k3 ,k4;
    k1 = func(x, y);
    k2 = func(x + step / 2, y + step / 2 * k1);
    k3 = func(x + step / 2, y + step / 2 * k2);
    k4 = func(x + step, y + step * k3);
    double V = y + step / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
    return V;
}

std::vector<std::vector<double>> RungeKutta4(const double x_start, const double U_start, const double step_start, const double control, const double x_end)
{
    std::vector<double> points;
    std::vector<double> number;
    std::vector<double> xData;
    std::vector<double> stepData;
    std::vector<double> pointsGood;
    std::vector<double> estimationData;
    std::vector<double> halfData;
    std::vector<double> doubleData;


    double step = step_start;
    double currPoint =  U_start;
	points.push_back(currPoint);
    xData.push_back(x_start);
    int i = 1;
    int doubleCount = 0;
    int halfCount = 0;
    double S;

    for(double x = x_start; x < x_end; x += step)
    {
        currPoint = pointRungeKutta4(x, points[i - 1], step);
        S = est(x, points[i - 1], step);

        if (S > control)
        {
            x -= step;
            step /= 2.0;
            halfCount++;
            i--;
            continue;
        }

        stepData.push_back(step);
        double halfPoint = pointRungeKutta4(x, points[i - 1], step / 2);
        halfPoint = pointRungeKutta4(x, halfPoint, step / 2);

        if(fabs(S) <= (control / 32.0))
        {
             step *= 2;
             doubleCount++;
        }

        points.push_back(currPoint);
        number.push_back(i);
        pointsGood.push_back(halfPoint);
        estimationData.push_back(S);
        halfData.push_back(halfCount);
        doubleData.push_back(doubleCount);
        xData.push_back(x);

        i++;


    }

    std::vector<std::vector<double>> res;
    res.push_back(number);
    res.push_back(stepData);
    res.push_back(xData);
    res.push_back(points);
    res.push_back(pointsGood);
    res.push_back(estimationData);
    res.push_back(halfData);
    res.push_back(doubleData);
    return res;
}


double func(const double x, const double V) // rhs
{
	return 0.0;
}







