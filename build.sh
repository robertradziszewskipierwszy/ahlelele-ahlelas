#!/bin/bash
set -e

echo "Building Ahlelele Ahlelas Compiler..."

mkdir -p build
cd build

cmake ..
cmake --build . -j$(nproc)

echo ""
echo "Build complete! Executable: build/ahlelele"
echo ""
echo "Try it out:"
echo "  ./build/ahlelele --in examples/hello_world.ahl --out hello.ahlx"
echo "  ./build/ahlelele --exec hello.ahlx"

