#!/bin/bash

sudo apt update
sudo apt install build-essential
[ ! -d "./dep/" ] && mkdir dep
cd dep
git clone https://github.com/gabime/spdlog.git
cd spdlog && mkdir build && cd build
cmake .. && make -j4
sudo make install
sudo ldconfig
cd ../../../