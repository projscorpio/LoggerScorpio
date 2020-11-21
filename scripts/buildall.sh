#!/bin/bash

[ ! -d "./build/" ] && mkdir build
cd build/ && cmake .. && sudo make install
sudo ldconfig