
#define _USE_MATH_DEFINES



#include <cmath>
#include <vector>



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

double func(const double x, const double V, const double sigma, const double a) // rhs
{
	return -0.6 * sigma * sqrt(2 * 9.8) / tan(0.5 * a) / M_PI / pow(V, 3 / 2);
}

double pointRungeKutta4(const double x, const double y, double step, double sigma, double a)// one step for RungeKutta4
{
    double k1, k2, k3 ,k4;
    k1 = func(x, y, sigma, a);
    k2 = func(x + step / 2, y + step / 2 * k1, sigma, a);
    k3 = func(x + step / 2, y + step / 2 * k2, sigma, a);
    k4 = func(x + step, y + step * k3, sigma, a);
    double V = y + step / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
    return V;
}

double est(double x, double U, double step, double sigma, double a)
{
    double currPoint = pointRungeKutta4(x, U, step, sigma, a);
    double halfPoint = pointRungeKutta4(x, U, step / 2.0, sigma, a);
    halfPoint = pointRungeKutta4(x + step / 2.0, halfPoint, step / 2.0, sigma, a);
    double res = fabs(halfPoint - currPoint) / 15.0;
    return res;
}

std::vector<std::vector<double>> RungeKutta4(const double x_start, const double U_start, const double step_start, const double control, const double x_end, const double sigma, const double a)
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
    pointsGood.push_back(currPoint);
    xData.push_back(x_start);
    number.push_back(0.0);
    stepData.push_back(step);
    estimationData.push_back(0.0);
    halfData.push_back(0.0);
    doubleData.push_back(0.0);

    int i = 1;
    int doubleCount = 0;
    int halfCount = 0;
    double S;



    for(double x = x_start; x < x_end; x += step)
    {
        currPoint = pointRungeKutta4(x, points[i - 1], step, sigma, a);
        S = est(x, points[i - 1], step, sigma, a);

        if (S > control)
        {
            x -= step;
            step /= 2.0;
            halfCount++;
            halfData.push_back(halfCount);
            i--;
            continue;
        }

        stepData.push_back(step);
        double halfPoint = pointRungeKutta4(x, points[i - 1], step / 2.0, sigma, a);
        halfPoint = pointRungeKutta4(x + step / 2.0, halfPoint, step / 2.0, sigma, a);

        if(S <= (control / 32.0))
        {
             step *= 2.0;
             doubleCount++;
        }

        points.push_back(currPoint);
        number.push_back(i);
        pointsGood.push_back(halfPoint);
        estimationData.push_back(S);

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










