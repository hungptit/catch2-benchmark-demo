#!/bin/bash
os_type=$(uname)
case "$os_type" in
    "Darwin")
        {
            number_of_cores=$(sysctl -n hw.ncpu);
        } ;;
    "Linux")
        {
            number_of_cores=$(grep -c ^processor /proc/cpuinfo)
        } ;;
    *)
        {
            echo "Unsupported OS, exiting"
            exit
        } ;;
esac

# Configure the project
cmake ./ "$@"

# Build all libraries and tests
make -j"$number_of_cores"

# Run all tests
make test -j"$number_of_cores"
