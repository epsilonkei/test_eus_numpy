// -*- mode: C++; coding: utf-8-unix; -*-

/**
 * @file  call_pyfunc.cpp
 * @brief
 */

#include <cstdlib> // setenv
#define BOOST_PYTHON_STATIC_LIB
#define BOOST_NUMPY_STATIC_LIB
#include <memory>
#include "boost/numpy.hpp"
#include <stdexcept>
#include <algorithm>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <dlfcn.h>

#define BEGIN_PYAPI try
#define END_PYAPI catch (const py::error_already_set&) { PyErr_Print(); }

namespace py = boost::python;
namespace np = boost::numpy;

class test_eus_numpy {
public:
  std::shared_ptr<np::ndarray> arr;
  Eigen::Vector3d arr_map;
  py::object nplib, np_add123;

  test_eus_numpy() {
    init_py();
    arr = std::make_shared<np::ndarray>(np::zeros(py::make_tuple(3), np::dtype::get_builtin<double>()));
    arr_map = Eigen::Map<Eigen::Vector3d>(reinterpret_cast<double*>(arr->get_data()), 3);
  }

  ~test_eus_numpy() {}

  void init_py() {
    // Allow Python to load modules from PYTHONPATH directory.
    std::cout << getenv("PYTHONPATH") << " --> ";
    setenv("PYTHONPATH", "/home/kangaroo/work/test_eus_numpy:/home/kangaroo/catkin_ws/simbicon_walk/devel/lib/python2.7/dist-packages:/home/kangaroo/catkin_ws/jaxon_tutorial/devel/lib/python2.7/dist-packages:/opt/ros/indigo/lib/python2.7/dist-packages", 1);
    std::cout << getenv("PYTHONPATH") << std::endl;
    dlopen("libpython2.7.so", RTLD_NOW | RTLD_GLOBAL);
    // Initialize for Boost.Python and Boost.Numpy
    Py_Initialize();
    np::initialize();

    BEGIN_PYAPI {
      // import Python module
      test_eus_numpy::nplib = py::import("nplib").attr("__dict__");
      test_eus_numpy::np_add123 = nplib["add123"];
    } END_PYAPI;
  }

  void set_arr(double* _arr) {
    arr_map = Eigen::Map<Eigen::Vector3d>(_arr, 3);
    Eigen::Map<Eigen::Vector3d>(reinterpret_cast<double*>(arr->get_data()), 3) = arr_map;
  }

  void add123() {
    BEGIN_PYAPI {
      *arr = py::extract<np::ndarray>(np_add123(*arr));
    } END_PYAPI;
  }

  void get_arr(double* _arr) {
    arr_map = Eigen::Map<Eigen::Vector3d>(reinterpret_cast<double*>(arr->get_data()), 3);
    Eigen::Map<Eigen::Vector3d>(_arr, 3) = arr_map;
  }

  void _add123(double* _arr, double* _ret) {
    Eigen::Vector3d eg_arr = Eigen::Map<Eigen::Vector3d>(_arr, 3), eg_ret;
    np::ndarray np_arr = np::zeros(py::make_tuple(3), np::dtype::get_builtin<double>());
    np::ndarray np_ret = np::zeros(py::make_tuple(3), np::dtype::get_builtin<double>());
    Eigen::Map<Eigen::Vector3d>(reinterpret_cast<double*>(np_arr.get_data()), 3) = eg_arr;
    BEGIN_PYAPI {
      np_ret = py::extract<np::ndarray>(np_add123(np_arr));
    } END_PYAPI;
    eg_ret = Eigen::Map<Eigen::Vector3d>(reinterpret_cast<double*>(np_ret.get_data()), 3);
    Eigen::Map<Eigen::Vector3d>(_ret, 3) = eg_ret;
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
    return eg_ret; }

};
