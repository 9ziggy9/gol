Conway's Game of Life implemented in C by use of SDL2


# H1 Manual Installation
To install manually make sure you have requisite SDL2 libraries and cmake. You MUST use the recursive flag to pull in the FindSDL2.cmake submodules. (Or git submodule update --init after the fact).

git clone --recursive https://github.com/9ziggy9/gol.git
cd gol
mkdir build
cd build
cmake .. && make install
cd ..
./conway

Note that by default, the binary is targeted at the originating folder.

Space will run/pause the time evolution and allow you to populate the grid. Escape to exit. Window should be resizable now. Please report any bugs and I'll try to fix them immediately.

For more advanced usage see ./conway -h

The inclusion of the FindSDL2.cmake modules should make this port to just about anything. If you have an issue on your system, please let me know.
