#!/usr/bin/bash

shopt -s globstar

OLD="\(#include <alpha\)\/\(.*>\)"
NEW="\1\/lang\/\2"

sed -i "s+${OLD}+${NEW}+" include/alpha/lang/**/*.h

sed -i "s+${OLD}+${NEW}+" src/alpha/lang/**/*.cpp
sed -i "s+${OLD}+${NEW}+" src/alpha/lang/**/*.y
sed -i "s+${OLD}+${NEW}+" src/alpha/lang/**/*.l
