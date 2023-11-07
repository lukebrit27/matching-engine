#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "Engine.hpp"

PYBIND11_MODULE(matching_engine, m) {
    pybind11::class_<Engine>(m, "Engine")
        .def(pybind11::init())
        .def("start", &Engine::start)
        .def("submitOrder", &Engine::submitOrder);
}