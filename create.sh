#!/usr/bin/env bash

mkdir $1

echo "# Creates a binary target
add_executable(main $1.cpp)
target_link_libraries(main \${OpenCV_LIBS})" > $1/CMakeLists.txt

cp basic/basic.cpp $1/$1.cpp

touch $1/readme.md

echo "# $1" > $1/readme.md