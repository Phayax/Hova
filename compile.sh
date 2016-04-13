#!/bin/bash
clang++-3.6 -o hova -std=c++11 -O3 -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio main.cpp game.cpp ship.cpp && ./hova
