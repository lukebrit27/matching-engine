#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "Engine.hpp"
#include "decode.hpp"

namespace py = pybind11;

PYBIND11_MODULE(matching_engine, m) {
    py::class_<Engine>(m, "Engine")
        .def(pybind11::init())
        .def("start", &Engine::start)
        .def("submitOrder", &Engine::submitOrder)
        .def("addEventListener", &Engine::addEventListener);
    // m.def("decodeFile", &decode::file);
}