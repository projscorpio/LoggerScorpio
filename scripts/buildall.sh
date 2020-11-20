#!/bin/bash

export CC=/usr/bin/gcc-9
export CXX=/usr/bin/g++-9
[ ! -d "./build/" ] && mkdir build
cd build/ && cmake .. && sudo make install
sudo ldconfig