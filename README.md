Conway's Game of Life implemented with SDL2 in C

To install make sure you have requisite SDL2 libraries and cmake.

git clone https://github.com/9ziggy9/gol.git

cd gol

cd build

cmake .. && make

./conway

Space will run/pause the time evolution and allow you to populate the grid. Escape to exit. Window should be resizable now. Please report any bugs and I'll try to fix them immediately.

For more advanced usage see ./conway -h

The inclusion of the FindSDL2.cmake modules should make this port to just about anything. If you have an issue on your system, please let me know.
