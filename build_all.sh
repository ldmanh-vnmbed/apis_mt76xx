#! /bin/bash

rm -rf build
mkdir build
cd build
cmake ..
make
./apis_mt76xx