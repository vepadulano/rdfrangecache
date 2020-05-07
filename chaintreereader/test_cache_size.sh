#! /usr/bin/bash

for filename in *.cpp; do
    rm -rf cache/*;
    name="${filename%.*}";
    g++ -g -std=c++17 -o ${name} ${filename} `root-config --cflags --glibs`;
    echo ${name}:;
    ./${name};
    echo Cache size:;
    du -h cache;
    rm -rf cache/*;
done