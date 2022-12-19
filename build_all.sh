#! /bin/bash

rm -rf build
mkdir build
cd build
cmake ..
make
# valgrind --leak-check=full ./apis_mt76xx
./apis_mt76xx
