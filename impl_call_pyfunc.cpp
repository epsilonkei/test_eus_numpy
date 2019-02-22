// -*- mode: C++; coding: utf-8-unix; -*-

/**
 * @file  impl_call_pyfunc.cpp
 * @brief
 */

#include <iostream>
#include "call_pyfunc.cpp"
#include <memory>

std::shared_ptr<test_eus_numpy> ten(new test_eus_numpy);

extern "C" {
  int test_eusnp_init_py() {ten->init_py(); return 0; }
  int test_eusnp_set_arr(double* _arr) {ten->set_arr(_arr); return 0; }
  int test_eusnp_get_arr(double* _arr) {ten->get_arr(_arr); return 0; }
  int test_eusnp_add123_() {ten->add123(); return 0; }
  // int test_eusnp_add123(double* _arr, double* _ret) {ten->add123(_arr, _ret); return 0; }
  int test_eusnp_add123(double* _arr, double* _ret) {
    Eigen::Vector3d arr = Eigen::Map<Eigen::Vector3d>(_arr, 3);
    Eigen::Map<Eigen::Vector3d>(_ret, 3) = ten->add123(arr);
    return 0; }
};

int main(int argc, char **argv) {
  std::cout << "Hoge" << std::endl;
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
