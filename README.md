# Conway's Game of Life implemented in C and SDL2

### You MUST install the SDL2 library and cmake before going any further.

## Automated Installation via cmake (Linux possibly Mac)
* git clone https://github.com/9ziggy9/gol.git
* cd gol
* ./install.sh
* ./conway

Note that if install.sh is not marked executable by default you mut run chmod +x install.sh.


## Manual Installation via cmake (Linux possibly Mac)
#### To install manually make sure you have requisite SDL2 libraries and cmake. You MUST use the recursive flag to pull in the FindSDL2.cmake submodules. (Or git submodule update --init after the fact).

* git clone --recursive https://github.com/9ziggy9/gol.git
* cd gol
* mkdir build
* cd build
* cmake .. && make install
* cd ..
* ./conway

Note that by default, the binary is targeted at the originating folder. The build folder can be discarded; rm -rf build

## Installation via Makefile (for FreeBSD/Dragonfly especially)
#### It's the damndest thing but I cannot figure out why my original makefile works here yet the cmake build does not. No matter, I've added a branch so that installation via the traditional Makefile is possible. Dragonfly/gcc users remember to change CC flag of Makefile to gcc.

* git clone -b make_ver https://github.com/9ziggy9/gol.git
* cd gol
* make
* ./conway

## Notes
Space will run/pause the time evolution and allow you to populate the grid. Escape to exit. Backspace will clear the screen. Window should be resizable now. Please report any bugs and I'll try to fix them immediately.

For more advanced usage such as changing cell size and rate of time evolution see ./conway -h:

Usage: conway [-t ticks] [-c cell_size] 

-t      Set number of ticks in microseconds.
        Enter extremely low values at own peril.
        Recommended to stay in 30000-100000 range.
        Defaults to 50000.


 -c     Set cell size to small, medium or large.
        Defaults to small.


The inclusion of the FindSDL2.cmake modules should make this port to just about anything. If you have an issue on your system, please let me know.
