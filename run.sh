#!/bin/bash

g++ $1 -xc++ -std=c++20 -o a.out -Wall

if [ $? -eq 0 ]; then
    echo "Compilation successful"
    echo "*"
else
    exit
fi

./a.out

if [ $? -eq 0 ]; then
    rm ./a.out
else
    exit
fi
