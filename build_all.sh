#!/bin/bash
config=${1:-"Release"}
cmake ./ -DCMAKE_BUILD_TYPE=$config
make -j3
make test -j3
