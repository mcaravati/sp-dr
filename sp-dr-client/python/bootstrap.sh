#!/usr/bin/env bash

ORIGIN_DIR=$(pwd)

build_library() {
    cd ../lib
    make clean
    make python
    cp libspdr.so ../python/
    make clean

    cd ${ORIGIN_DIR}
}

run_test() {
    LIBRARY_LOCATION=$(pwd)
    cd test
    PYTHONPATH=${LIBRARY_LOCATION} python main.py
    rm ../libspdr.so
}

case "$1" in
    build)
        build_library
    ;;

    test)
        build_library
        run_test
    ;;
esac