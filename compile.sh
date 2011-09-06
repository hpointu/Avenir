#!/bin/sh

mkdir build
cd build
cmake ..
make
cp Avenir ..
cd ..
rm -rf build
