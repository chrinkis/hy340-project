#!/usr/bin/bash

shopt -s globstar

OLD="\(#include <alpha\)\/\(.*>\)"
NEW="\1\/lang\/\2"

sed -i "s+${OLD}+${NEW}+" include/**/*.h

sed -i "s+${OLD}+${NEW}+" src/**/*.cpp
sed -i "s+${OLD}+${NEW}+" src/**/*.y
sed -i "s+${OLD}+${NEW}+" src/**/*.l
