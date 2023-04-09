#!/usr/bin/env sh
set -e
build_dir="${1:-build}"
cd data
python3 build.py
cd ..
mkdir -p $build_dir
cd $build_dir
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -j$(nproc)
