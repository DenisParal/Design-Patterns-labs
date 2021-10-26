#!/bin/sh
cd build
rm -rf ./*
cmake ..
make
c++ CMakeFiles/main.dir/src/window.cpp.o  -o main  -Wl,-rpath,/home/dparanic/Study/Design-Patterns-labs/Lab2.2-GeometryVisualizer/build libGeometryVisualizer.so -lsfml-graphics -lsfml-window -lsfml-system
./main