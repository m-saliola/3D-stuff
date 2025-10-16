#!/bin/bash
DIR="build/"
[ ! -d "$DIR" ] && mkdir build
cd build
cmake ..
cmake --build .
cd ..