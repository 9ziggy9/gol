Conway's Game of Life implemented with SDL2 in C

To install make sure you have requisite SDL2 libraries. My inclusion of gfxPrimitives is unnecessary and should probably be removed but most package managers include it in their standard repos; it's typically named SDL2_gfx.

git clone https://github.com/9ziggy9/gol.git

cd gol

make

./conway

Space will run/pause the time evolution and allow you to populate the grid. Escape to exit.
