#!/bin/sh
cd ./cmake-build-debug
cmake ..
make
./autodock_vina_extractor
cd ../
