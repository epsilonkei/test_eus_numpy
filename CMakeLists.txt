cmake_minimum_required (VERSION 2.6)
project (TestEusNumpy)

set(BOOST_NUMPY_ROOT /usr/local)

### C++11
add_compile_options(-std=c++11)

### pkgconfig (for pkg_check_modules)
find_package(PkgConfig REQUIRED)

### Python includes
pkg_check_modules(PYTHON python REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

### Boost includes
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

### Boost Numpy includes
include_directories(${BOOST_NUMPY_ROOT}/include)
link_directories(${BOOST_NUMPY_ROOT}/lib64)

### Eigen
include_directories(/usr/include/eigen3)

### Build
add_library(TestEusNumpy SHARED call_pyfunc.cpp)
set_target_properties(TestEusNumpy PROPERTIES SUFFIX ".so")
target_link_libraries(TestEusNumpy boost_numpy boost_python ${PYTHON_LIBRARIES})

### Build
add_executable(test_pyfunc_in_cpp test_pyfunc_in_cpp.cpp)
target_link_libraries(test_pyfunc_in_cpp boost_numpy boost_python ${PYTHON_LIBRARIES})
