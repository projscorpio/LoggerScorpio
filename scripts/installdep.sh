#!/bin/bash

[ ! -d "./dep/" ] && mkdir dep
cd dep
git clone https://github.com/gabime/spdlog.git
cd spdlog && mkdir build && cd build
cmake .. && make -j4
sudo make install
sudo ldconfig
cd ../../../