
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>


#include "Methods.h"


PYBIND11_MODULE(rungekutta4, m)
{
    m.def("RungeKutta4", &RungeKutta4);
    m.def("pointRungeKutta4", &pointRungeKutta4);
    m.def("est", &est);
    m.def("func", &func);
};
