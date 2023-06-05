#!/usr/bin/bash

shopt -s globstar

OLD="\(#include <alpha\)\/\([^'lang'].*>\)"
NEW="\1\/lang\/\2"

for FILE in ./include/**/*.h; do
    sed -i "s+${OLD}+${NEW}+g" include/**/*.h
done

for FILE in ./src/**/*.cpp; do
    sed -i "s+${OLD}+${NEW}+g" include/**/*.h
done

