#!/bin/zsh
cd ./cpp
cmake .
make
./project2
cd ..
cd ./py
python graphs.py
cd ..
exit
