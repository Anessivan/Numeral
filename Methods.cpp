
#define _USE_MATH_DEFINES

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


#include <cmath>
#include <vector>




double func(const double x, const double V, const double sigma, const double a) // rhs
{
	return (((((-0.6 * sigma * sqrt(2 * 9.8)) / tan(0.5 * a)) / tan(0.5 * a)) / M_PI) / pow(V, 3 / 2));
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

std::vector<std::vector<double>> RungeKutta4(const double x_start, const double U_start, const double step_start, const double control, const double x_end, const double eps, const double sigma, const double a)
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
    number.push_back(0.0);
    xData.push_back(x_start);
    stepData.push_back(step);
    estimationData.push_back(0.0);
    halfData.push_back(0.0);
    doubleData.push_back(0.0);

    int i = 1;
    int doubleCount = 0;
    int halfCount = 0;
    double S;



    for(double x = x_start; (x < x_end) && currPoint > 0; x += step)
    {


        currPoint = pointRungeKutta4(x, points[i - 1], step, sigma, a);
        S = est(x, points[i - 1], step, sigma, a) * 16.0;

        if (S > control)
        {
            x -= step;
            step /= 2.0;
            halfCount++;
            halfData.push_back(halfCount);

        }
       else
       {
            stepData.push_back(step);
            double halfPoint = pointRungeKutta4(x, points[i - 1], step / 2.0, sigma, a);
            halfPoint = pointRungeKutta4(x + step / 2.0, halfPoint, step / 2.0, sigma, a);




            if(S <= (control / 32.0))
            {
                step *= 2.0;
                doubleCount++;
            }



            while((x + step > x_end) && (x < x_end - eps) && eps)
            {
                step = step / 2.0;
                halfCount++;
            }

            xData.push_back(x + step);
            points.push_back(currPoint);
            number.push_back(i);
            pointsGood.push_back(halfPoint);
            estimationData.push_back(S);
            halfData.push_back(halfCount);
            doubleData.push_back(doubleCount);

            i++;
        }


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










