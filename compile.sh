#!/bin/bash
mkdir -p build;
cd build;

cmake -D CMAKE_FIND_DEBUG_MODE=ON ..;

make -j4;
cd ..;
