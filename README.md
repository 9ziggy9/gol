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

Unfortunately it appears I have given too much freedom in way of command line options and poor choices of -c -t can throw seg faults or even crash systems. For this reason I will be changing to a choice of 3 sane value for each.
