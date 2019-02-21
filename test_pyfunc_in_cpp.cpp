// -*- mode: C++; coding: utf-8-unix; -*-

/**
 * @file  call_pyfunc.cpp
 * @brief
 */

#include <cstdlib> // setenv
#define BOOST_PYTHON_STATIC_LIB
#define BOOST_NUMPY_STATIC_LIB
#include "boost/numpy.hpp"
#include <stdexcept>
#include <algorithm>
#include <Eigen/Dense>
#include <Eigen/Geometry>

#define BEGIN_PYAPI try
#define END_PYAPI catch (const py::error_already_set&) { PyErr_Print(); }

namespace py = boost::python;
namespace np = boost::numpy;

py::object nplib, np_add123;

void init_py() {
  // Allow Python to load modules from PYTHONPATH directory.
  setenv("PYTHONPATH", "/home/kangaroo/work/test_eus_numpy", 1);
  // Initialize for Boost.Python and Boost.Numpy
  Py_Initialize();
  np::initialize();

  BEGIN_PYAPI {
    // import Python module
    nplib = py::import("nplib").attr("__dict__");
    np_add123 = nplib["add123"];
  } END_PYAPI;
}

Eigen::Vector3d add123(Eigen::Vector3d eg_arr) {
  Eigen::Vector3d eg_ret;
  np::ndarray np_arr = np::zeros(py::make_tuple(3), np::dtype::get_builtin<double>());
  np::ndarray np_ret = np::zeros(py::make_tuple(3), np::dtype::get_builtin<double>());
  Eigen::Map<Eigen::Vector3d>(reinterpret_cast<double*>(np_arr.get_data()), 3) = eg_arr;
  BEGIN_PYAPI {
    np_ret = py::extract<np::ndarray>(np_add123(np_arr));
  } END_PYAPI;
  eg_ret = Eigen::Map<Eigen::Vector3d>(reinterpret_cast<double*>(np_ret.get_data()), 3);
  return eg_ret;
}

int main(int argc, char **argv) {
  init_py();
  Eigen::Vector3d in;
  in << 1,1,1;
  std::cerr << "Input vector: " << in.transpose() << std::endl;
  Eigen::Vector3d out = add123(in);
  std::cerr << "Output vector: " << out.transpose() << std::endl;
}
