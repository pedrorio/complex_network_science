#!/bin/zsh

cd ./cpp
cmake .
make
./project2
cd ..
cd py 
./graphs.py
cd ..
exit

# cmake ./cpp/
# make -C cpp
# cpp/project2 
# | py/graphs.py
# exit
 