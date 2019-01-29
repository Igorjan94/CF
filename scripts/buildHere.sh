#!/usr/bin/env bash

mkdir -p out
cd out

if ls ../*.pro 1> /dev/null 2>&1; then
    qmake .. && make;
else
    if ls ../CMakeLists.txt 1> /dev/null 2>&1; then
        cmake .. && make;
    else
        echo "No .pro and CMakeLists.txt is found, nothing to do here"
    fi
fi

