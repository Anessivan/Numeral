
#define _USE_MATH_DEFINES

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


#include <cmath>
#include <vector>




double func(const double x, const double V, const double sigma, const double a) // rhs
{
    if(V == 0)
        return 0.0;
	double res = - 0.6 * sigma * sqrt(2 * 9.8) / tan(0.5 * a) / tan(0.5 * a) / M_PI / sqrt(powf(V, 3));
    return res;
}



double pointRungeKutta4(const double x, const double y, double step, double sigma, double a)// one step for RungeKutta4
{
    double k1 = func(x, y, sigma, a);
    double k2 = func(x + step / 2.0, y + step / 2.0 * k1, sigma, a);
    double k3 = func(x + step / 2.0, y + step / 2.0 * k2, sigma, a);
    double k4 = func(x + step, y + step * k3, sigma, a);
    double V = y + step / 6.0 * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
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

std::vector<std::vector<double>> RungeKutta4(const double x_start, const double U_start, const double step_start, const double control, const double x_end, const double eps, const double sigma, const double a, const int n)
{
    std::vector<double> points;
    std::vector<double> number;
    std::vector<double> xData;
    std::vector<double> stepData;
    std::vector<double> pointsGood;
    std::vector<double> estimationData;
    std::vector<double> halfData;
    std::vector<double> doubleData;

    double eps_n = eps;
    double step = step_start;
    double currPoint =  U_start;
	points.push_back(currPoint);
    pointsGood.push_back(0.0);
    number.push_back(0.0);
    xData.push_back(x_start);
    stepData.push_back(0.0);
    estimationData.push_back(0.0);
    halfData.push_back(0.0);
    doubleData.push_back(0.0);

    int i = 1;
    int doubleCount = 0;
    int halfCount = 0;
    double S;
    //double x_last = 0;

    if(eps_n == 0)
        eps_n = 2 * step;



    for(double x = x_start; (x < x_end) && currPoint > 0; x += step)
    {
        currPoint = pointRungeKutta4(x, points[i - 1], step, sigma, a);
        double currX = x + step;
        S = est(x, points[i - 1], step, sigma, a);

        if (S > control)
        {
            x -= step;
            step /= 2.0;
            halfCount++;
            halfData.push_back(halfCount);
            continue;
        }
       //else
       //{
        stepData.push_back(step);
        double halfPoint = pointRungeKutta4(x, points[i - 1], step / 2.0, sigma, a);
        halfPoint = pointRungeKutta4(x + step / 2.0, halfPoint, step / 2.0, sigma, a);

        if (currPoint < 0.0)
            break;

        xData.push_back(x);
        points.push_back(currPoint);
        number.push_back(i - 1);
        pointsGood.push_back(halfPoint);
        estimationData.push_back(S * 16.0);

        if(S <= (control / 32.0) && (i != 1))
        {
            step *= 2.0;
            doubleCount++;
        }


        //double prevPoint = points[i - 1];
        if((currX + step > x_end) && (currX < x_end - eps_n) || (currPoint <  step))
        {
            step = eps_n / 2.0;
            halfCount = halfData[i - 1];
            doubleCount = doubleData[i - 1];
        }

        
           
            
        halfData.push_back(halfCount);
        doubleData.push_back(doubleCount);

        i++;
        if((i == n) && n)
            break;
        if(currPoint == 0)
            break;
        //}
        //x_last = x;

    }

   // xData.push_back(x_last);

    std::vector<std::vector<double>> res;
    res.push_back(number);
    res.push_back(stepData);
    res.push_back(xData);
    res.push_back(points);
    res.push_back(pointsGood);
    res.push_back(estimationData);
    res.push_back(halfData);
    res.push_back(doubleData);
    for (int i = 0; i < res.size(); i++)
        res[i].erase(res[i].begin() + 1);
    return res;
}










