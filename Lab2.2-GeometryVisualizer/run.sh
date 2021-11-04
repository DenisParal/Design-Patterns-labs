#!/bin/sh
cd build
rm -rf ./*
cmake ..
make
c++ CMakeFiles/main.dir/src/window.cpp.o  -g -o main  -Wl,-rpath,/home/dparanic/Study/Design-Patterns-labs/Lab2.2-GeometryVisualizer/build libGeometryVisualizer.so /lib/x86_64-linux-gnu/libpthread.so.0 -lsfml-graphics -lsfml-window -lsfml-system
./main