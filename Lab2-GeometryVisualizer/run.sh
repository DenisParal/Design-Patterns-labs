#!/bin/sh
cd build
rm -rf ./*
cmake ..
make
c++ CMakeFiles/test1.dir/src/test.cpp.o  -o test1  -Wl,-rpath,/home/dparanic/Study/Design-Patterns-labs/Lab2-GeometryVisualizer/build libGeometryVisualizer.so -lsfml-graphics -lsfml-window -lsfml-system
./test1