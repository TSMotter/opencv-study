#!/usr/bin/env bash

mkdir $1

echo "# Creates a binary target
add_executable(main $1.cpp)" > $1/CMakeLists.txt

cp helloworld/helloworld.cpp $1/$1.cpp

touch $1/readme.md

echo "# $1" > $1/readme.md