# test_eus_numpy

## Install Boost Numpy [Referrence](https://www.iandprogram.net/entry/2015/12/17/124747)
```
sudo apt-get update
sudo apt-get install python-dev python-numpy 
sudo apt-get install libboost-dev
sudo apt-get install libboost-python-dev
sudo apt-get install libboost-system-dev
sudo apt-get install build-essential python-setuptools libatlas-dev libatlas3gf-base

git clone https://github.com/ndarray/Boost.NumPy
cd Boost.NumPy
cmake .
make
make install

# Pathを通す
echo export CPLUS_INCLUDE_PATH=/usr/include/python2.7 >> ~/.bashrc
echo export PATH=$PATH:$CPLUS_INCLUDE_PATH >> ~/.bashrc
source ~/.bashrc
```
## Hotfix:
You need to change ```PYTHONPATH``` settings in cpp file to folder, where has ```nplib.py``` file

## Compile and test
### Compile
```
mkdir build
cd build
cmake ..
make
```

### Test
```
# Test call numpy func from cpp
./test_pyfunc_in_cpp 
# Test call numpy func from Euslisp
roseus test_eus_np.l
test_eusnp::add123
```
