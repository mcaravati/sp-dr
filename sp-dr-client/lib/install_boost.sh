#!/usr/bin/env bash

PYTHON_HEADERS_PATH="/usr/include/python3.11/"

if [[ ! -d boost ]]; then
    echo "[*] Downloading boost 1.82.0..."
    wget https://boostorg.jfrog.io/artifactory/main/release/1.82.0/source/boost_1_82_0.tar.gz
    CHECKSUM=$(sha256sum boost_1_82_0.tar.gz | cut -d' ' -f1)

    if [[ ${CHECKSUM} != "66a469b6e608a51f8347236f4912e27dc5c60c60d7d53ae9bfe4683316c6f04c" ]]; then
        >&2 echo "[-] ERROR: Wrong checksum"
        exit 1 
    fi

    echo "[*] Decompressing archive..."
    tar xf boost_1_82_0.tar.gz && rm boost_1_82_0.tar.gz
    mv boost_* boost
fi

cd boost

echo "[*] Building boost...."
./bootstrap.sh --with-python=$(python --version | cut -d' ' -f2)
mkdir -p ../boost_build
CPLUS_INCLUDE_PATH="$CPLUS_INCLUDE_PATH:$PYTHON_HEADERS_PATH" ./b2 --build-dir=../boost_build
