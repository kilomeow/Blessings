#!/usr/bin/bash

mkdir -p build
cd build
cmake ../ -DCMAKE_CXX_COMPILER=gcc -DCMAKE_INSTALL_PREFIX=$HOME/.prefix/usr
make work
cp work ../
cd ../

