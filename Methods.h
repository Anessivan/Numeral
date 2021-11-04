#pragma once




#include <vector>
#include <cmath>


double func(const double x, const double V);  //rhs

/*double PointEulerMethod(const double x_start, const double y_start, double step); // one step for Euler Method

double PointRungeKutta2_1(const double x_start, const double y_start, double step);// one step for RungeKutta2_1

double PointRungeKutta2_2(const double x_start, const double y_start, double step);// one step for RungeKutta2_2

double PointRungeKutta4(const double x_start, const double y_start, double step);// one step for RungeKutta4

std::vector<double> EulerMethod(const double x_start, const double y_start, double step, double stop);

std::vector<double> RungeKutta2_1(const double x_start, const double y_start, double step, double stop); // RungeKutta second order type 1

std::vector<double> RungeKutta2_2(const double x_start, const double y_start, double step, double stop);// RungeKutta second order type 2*/

double pointRungeKutta4(const double x_start, const double y_start, double step);// one step for RungeKutta4

std::vector<std::vector<double>> RungeKutta4(const double x_start, const double U_start, const double step_start, const double control);

double est(double x, double U, double step);

