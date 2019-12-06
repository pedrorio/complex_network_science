#!/bin/zsh

cd ./cpp
cmake .
make
cd ..
./cpp/project2
exit