#!/bin/bash

echo "Compiling main.cpp"

g++ main.cpp -xc++ -std=c++20 -o main.out

if [ $? -eq 0 ]; then
    echo "Compilation successful"
else
    exit
fi

echo "*"
echo "Executing main.out"
echo "*"

./main.out
if [ $? -eq 0 ]; then
    rm ./main.out
else
    exit
fi
