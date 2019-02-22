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
#include <dlfcn.h>

#define BEGIN_PYAPI try
#define END_PYAPI catch (const py::error_already_set&) { PyErr_Print(); }

namespace py = boost::python;
namespace np = boost::numpy;

namespace test_eus_numpy {
  // np::ndarray arr = np::zeros(py::make_tuple(3), np::dtype::get_builtin<double>());
  // Eigen::Vector3d arr_map = Eigen::Map<Eigen::Vector3d>(reinterpret_cast<double*>(arr.get_data()), 3);
  py::object nplib, np_add123;

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

  // void set_arr(double* _arr) {
  //   test_eus_numpy::arr_map = Eigen::Map<Eigen::Vector3d>(_arr, 3);
  // }

  // void add123(double* _arr) {
  //   BEGIN_PYAPI {
  //     test_eus_numpy::arr = py::extract<np::ndarray>(test_eus_numpy::np_add123(test_eus_numpy::arr));
  //   } END_PYAPI;
  // }

  // void get_arr(double* _arr) {
  //   Eigen::Map<Eigen::Vector3d>(_arr, 3) = test_eus_numpy::arr_map;
  // }

  void _add123(double* _arr, double* _ret) {
    Eigen::Vector3d eg_arr = Eigen::Map<Eigen::Vector3d>(_arr, 3), eg_ret;
    np::ndarray np_arr = np::zeros(py::make_tuple(3), np::dtype::get_builtin<double>());
    np::ndarray np_ret = np::zeros(py::make_tuple(3), np::dtype::get_builtin<double>());
    Eigen::Map<Eigen::Vector3d>(reinterpret_cast<double*>(np_arr.get_data()), 3) = eg_arr;
    BEGIN_PYAPI {
      np_ret = py::extract<np::ndarray>(test_eus_numpy::np_add123(np_arr));
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

}

extern "C" {
  int test_eusnp_init_py() {test_eus_numpy::init_py(); return 0; }
  // int test_eusnp_set_arr(double* _arr) {test_eus_numpy::set_arr(_arr); return 0; }
  // int test_eusnp_get_arr(double* _arr) {test_eus_numpy::get_arr(_arr); return 0; }
  // int test_eusnp_add123() {test_eus_numpy::add123(); return 0; }
  // int test_eusnp_add123(double* _arr, double* _ret) {test_eus_numpy::add123(_arr, _ret); return 0; }
  int test_eusnp_add123(double* _arr, double* _ret) {
    Eigen::Vector3d arr = Eigen::Map<Eigen::Vector3d>(_arr, 3);
    Eigen::Map<Eigen::Vector3d>(_ret, 3) = test_eus_numpy::add123(arr);
    return 0; }
};

int main(int argc, char **argv) {
  test_eusnp_init_py();
  double arr[3] = {1,1,1};
  double ret[3];
  std::cout << "input is " << arr[0] << ", " << arr[1] << ", " << arr[2] << std::endl;
  test_eusnp_add123(arr, ret);
  std::cout << "output is " << ret[0] << ", " << ret[1] << ", " << ret[2] << std::endl;
  // Eigen::Vector3d in;
  // in << 1,1,1;
  // std::cerr << "Input vector: " << in.transpose() << std::endl;
  // Eigen::Vector3d out = add123(in);
  // std::cerr << "Output vector: " << out.transpose() << std::endl;
}
