#!/bin/bash
#Fermath Project: compile.sh
#This script compiles Fermath and fermath_database
echo 'Compiling fermath_gfx 64 bits'
g++ main.cpp -o fermath_gfx64 -O2 -Wall `pkg-config --libs --cflags gtk+-2.0`
echo 'Compiling fermath_gfx 32 bits'
g++ main.cpp -o fermath_gfx32 -O2 -m32 -Wall `pkg-config --libs --cflags gtk+-2.0`
echo 'Compiling fermath_database 32 bits'
g++ fermath_database.cpp -o fermath_database32 -O2 -m32 -Wall
echo 'Compiling fermath_database 64 bits'
g++ fermath_database.cpp -o fermath_database64 -O2 -Wall
