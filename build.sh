#!/usr/bin/env sh
set -e
cd data
pip3 install -r requirements.txt
python3 build.py
cd ..
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -j$(nproc)
