#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "pybind11/numpy.h"
#include "Engine.hpp"
#include "decode.hpp"

namespace py = pybind11;

py::dict convertTableToPythonDict(const decode::Table& table) {
    py::dict pyTable;

    for (const auto& [key, value] : table) {
        // Extracting the data from the variant
        std::visit([&pyTable, &key](const auto& column) {
            using T = std::decay_t<decltype(column.data[0])>;
            pyTable[py::str(key)] = py::cast(column.data);
        }, value);
    }

    return pyTable;
}

py::list file_py(const std::string& file_name, unsigned int last_n_lines = 0){
    decode::Data res = decode::file(file_name, last_n_lines);
    // Create an empty list
    py::list result_list;
    // Append dictionaries to the list
    result_list.append(convertTableToPythonDict(res.orders.data));
    result_list.append(convertTableToPythonDict(res.trades.data));
    return result_list;
}

PYBIND11_MODULE(matching_engine, m) {
    py::class_<Engine>(m, "Engine")
        .def(pybind11::init())
        .def("start", &Engine::start)
        .def("submitOrder", &Engine::submitOrder)
        .def("addEventListener", &Engine::addEventListener);
    m.def("decodeFile", &file_py);
}