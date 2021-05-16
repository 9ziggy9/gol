#!/bin/sh

git submodule update --init
echo "FindSDL2.cmake submodules cloned."
mkdir build && cd build
cmake --build .. --target clean
make || { echo 'Installation failed.' ; exit 1; }
cd .. 
ln -s build/conway conway
echo "Installation complete."
echo "Run ./conway from here or add to your PATH."
