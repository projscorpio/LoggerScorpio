#!/bin/sh

sudo apt-get install libspdlog-dev
mkdir build && cd build/ && cmake .. && sudo make install