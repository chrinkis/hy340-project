if [[ $1 = "-t" ]]; then
    echo "This may take a while. Please be patient..."
    CMAKE_ARGS="-Dskip_tests:BOOL=OFF"
fi

mkdir -p build &&
    cd build &&
    cmake ${CMAKE_ARGS} .. &&
    make all

if [ $? -ne 0 ]; then
    exit
fi

if [[ $2 = "-r" ]]; then
    cd test && ./tests
fi
