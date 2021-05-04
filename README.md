Conway's Game of Life implemented with SDL2 in C

To install make sure you have requisite SDL2 libraries, make and clang (if you prefer gcc simply amend the CC line of Makefile).

git clone https://github.com/9ziggy9/gol.git

cd gol

make

./conway

Space will run/pause the time evolution and allow you to populate the grid. Escape to exit. Window should be resizable now. Please report any bugs and I'll try to fix them immediately.

Tested on Void, Manjaro, FreeBSD and DragonflyBSD (with gcc). BSD make seems to work.

For more advanced usage see ./conway -h

NOTE:

Currently there is a bug in the size of cell option. 9 pixels and below is throwing seg faults.

Also getting seg faults for window sizes which become sufficiently large; this should just be related to macro definitions of COL and ROW_NUM.
