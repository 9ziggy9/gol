Conway's Game of Life implemented with SDL2 in C

To install make sure you have requisite SDL2 libraries, make and clang (if you prefer gcc simply amend the CC line of Makefile).

git clone https://github.com/9ziggy9/gol.git

cd gol

make

./conway [-t ticks] [-s window_scale] [-c cell_size]

Space will run/pause the time evolution and allow you to populate the grid. Escape to exit. Window should be resizable now. Please report any bugs and I'll try to fix them immediately.

Tested on Void, Manjaro, FreeBSD and DragonflyBSD (with gcc). BSD make seems to work.
