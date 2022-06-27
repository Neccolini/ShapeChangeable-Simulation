#!/bin/bash
mkdir build && cd build
sudo apt-get update
sudo apt-get install cmake libgtest-dev
pushd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp lib *.a /usr/lib/
popd
sudo cmake ..
exit 0