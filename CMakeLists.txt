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
set(LIBS ${PYTHON_LIBRARIES} boost_python boost_program_options boost_numpy -rdynamic -ldl)

### Build
add_library(TestEusNumpy SHARED impl_call_pyfunc.cpp)
set_target_properties(TestEusNumpy PROPERTIES SUFFIX ".so")
target_link_libraries(TestEusNumpy ${LIBS})

### Build
add_executable(call_pyfunc impl_call_pyfunc.cpp)
target_link_libraries(call_pyfunc ${LIBS})
