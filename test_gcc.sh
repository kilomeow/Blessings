#!/usr/bin/bash

mkdir -p build
cd build
cmake ../ -DCMAKE_CXX_COMPILER=gcc
make work
cp work ../
cd ../

