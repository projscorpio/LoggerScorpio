#!/bin/bash

[ ! -d "./dep/" ] && mkdir dep
cd dep
git clone https://github.com/gabime/spdlog.git
cd spdlog
mkdir build
cd build
cmake .. -DSPDLOG_BUILD_SHARED=ON
make -j4
sudo make install
sudo ldconfig
cd ../../../